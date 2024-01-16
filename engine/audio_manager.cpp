#include <cstdint>

#include "audio_manager.hpp"

AudioManager::AudioManager(const char *devname)
    : m_dev(devname), m_ctx(m_dev.get()), m_loaded_buffers(),
      m_openal_event(SDL_RegisterEvents(1)) {
  m_ctx.makeCurrent();
  // Initialise extensions
  // Must be done after the context is current
  m_direct_channels = openal::DirectChannelsExtension();
  m_events = openal::EventsExtension();
  if (m_events.isSupported()) {
    // Assign our onAlEvent member function to the callback
    using namespace std::placeholders;
    m_events.setCallback(
        std::bind(&AudioManager::onAlEvent, this, _1, _2, _3, _4));
    m_events.enableEvents(m_events.E_EVENT_TYPE_SOURCE_STATE_CHANGED_SOFT);
  } else {
    // Todo: Implement a fallback mechanism based on source polling for oneshot
    // garbage collection
    throw std::runtime_error("AL_SOFTX_events is unsupported, proceeding would "
                             "allow memory leaks to occur!");
  }
}

openal::Buffer &AudioManager::getBufferByPath(const char *path) {
  auto iter = m_loaded_buffers.find(path);
  if (iter != m_loaded_buffers.end()) {
    return iter->second;
  }
  // Load a new buffer from a file
  auto file = AudioFile::fromFile(path);
  openal::Buffer buf;
  file.fillBuffer(buf);
  // Insert the buffer into the loaded assets, and return a reference to it
  return m_loaded_buffers[path] = std::move(buf);
}

void AudioManager::playByPath(const char *path) {
  openal::Buffer &buf = getBufferByPath(path);
  openal::Source src;
  if (m_direct_channels.isSupported()) {
    // Non-positional oneshot, play directly, remix if supported
    m_direct_channels.remix(src);
  }
  src.setBuffer(buf);
  playOneshot(std::move(src));
}

void AudioManager::playOneshot(openal::Source &&src) {
  ALuint id = src.getID();
  src.play();
  m_oneshots[id] = std::move(src);
}

bool AudioManager::onEvent(SDL_Event &ev) {
  // We're only interested in audio events
  if (ev.type != m_openal_event) {
    return false;
  }

  if (ev.user.code == m_events.E_EVENT_TYPE_SOURCE_STATE_CHANGED_SOFT) {
    // data1 = source, data2 = state

    // Currently we only care about stopped states
    if ((uintptr_t)ev.user.data2 != AL_STOPPED) {
      return true;
    }

    auto iter = m_oneshots.find((ALuint)(uintptr_t)ev.user.data1);
    if (iter != m_oneshots.end()) {
      // Source is a finished oneshot, delete it
      m_oneshots.erase(iter);
    }
  }

  return true; // Consume event
}

void AudioManager::onAlEvent(ALenum event, ALuint object, ALuint param,
                             std::string_view message) {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Received OpenAL event: %.*s",
               (int)message.size(), message.data());
  SDL_Event ev;

  // Build the SDL event
  ev.type = m_openal_event;
  ev.user.code = event;
  ev.user.data1 = (void *)(uintptr_t)object;
  ev.user.data2 = (void *)(uintptr_t)param;

  int res = SDL_PushEvent(&ev);
  if (res < 0) {
    // Likely the queue is full
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not push OpenAL event: %s",
                SDL_GetError());
  }
}
