#ifndef BBENGINE_AUDIO_MANAGER_HPP
#define BBENGINE_AUDIO_MANAGER_HPP

#include <unordered_map>

#include "al/buffer.hpp"
#include "al/context.hpp"
#include "al/device.hpp"
#include "al/source.hpp"
#include "audio_file.hpp"

class AudioManager {
public: // Member functions
  AudioManager(const char *devname = nullptr);

  // No copy
  AudioManager(const AudioManager &) = delete;
  AudioManager &operator=(const AudioManager &) = delete;

  /**
   * Get a reference to a buffer
   * @returns A reference to a buffer, which will be loaded if it was not loaded
   * already
   */
  openal::Buffer &getBufferByPath(const char *path);

private: // Member variables
  openal::Device m_dev;
  openal::Context m_ctx;
  std::unordered_map<std::string, openal::Buffer> m_loaded_buffers;
};

#endif
