#include "audio_manager.hpp"

AudioManager::AudioManager(const char *devname)
    : m_dev(devname), m_ctx(m_dev.get()), m_loaded_buffers() {
  m_ctx.makeCurrent();
  E_DIRECT_CHANNELS_SOFT = alGetEnumValue("AL_DIRECT_CHANNELS_SOFT");
  E_REMIX_UNMATCHED_SOFT = alGetEnumValue("AL_REMIX_UNMATCHED_SOFT");
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
  if (E_DIRECT_CHANNELS_SOFT != AL_NONE) {
    // Non-positional oneshot, play directly, remix if supported
    auto val =
        E_REMIX_UNMATCHED_SOFT != AL_NONE ? E_REMIX_UNMATCHED_SOFT : AL_TRUE;
    src.set(E_DIRECT_CHANNELS_SOFT, val);
  }
  src.setBuffer(buf);
  src.play();
  m_oneshots[id] = std::move(src);
}
