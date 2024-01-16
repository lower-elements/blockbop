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
  }
}

openal::Buffer &AudioManager::getBufferByPath(const char *path) {
  auto iter = m_loaded_buffers.find(path);
  if (iter != m_loaded_buffers.end()) {
    return iter->second;
  }
  // Load a new buffer from a file
  auto file = AudioFile::fromFile(path);
  openal::Buffer buf = file.makeBuffer();
  // Insert the buffer into the loaded assets, and return a reference to it
  return m_loaded_buffers[path] = std::move(buf);
}

void AudioManager::playByPath(const char *path) {
  openal::Buffer &buf = getBufferByPath(path);
  openal::Source src;
  ALuint id = src.getID();
  if (m_direct_channels.isSupported()) {
    // Non-positional oneshot, play directly, remix if supported
    m_direct_channels.remix(src);
  }
  src.setBuffer(buf);
  src.play();
  m_oneshots[id] = std::move(src);
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
