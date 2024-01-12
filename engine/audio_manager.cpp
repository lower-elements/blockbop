#include "audio_manager.hpp"

AudioManager::AudioManager(const char *devname)
    : m_dev(devname), m_ctx(m_dev.get()), m_loaded_buffers() {
  m_ctx.makeCurrent();
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
