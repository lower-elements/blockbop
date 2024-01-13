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
   * @param path Path to the audio file to load
   * @returns A reference to a buffer, which will be loaded if it was not loaded
   * already
   */
  openal::Buffer &getBufferByPath(const char *path);

  /**
   * Play a oneshot source
   * Retrieves the buffer by path, creates an internal source, and plays it. The
   * source will automatically be garbage collected when it finishes playing
   * @param path Path to the audio file to play
   */
  void playByPath(const char *path);

private: // Member variables
  openal::Device m_dev;
  openal::Context m_ctx;
  std::unordered_map<std::string, openal::Buffer> m_loaded_buffers;
  std::unordered_map<ALuint, openal::Source> m_oneshots;

public: // OpenAL extension functions / enums
  ALenum E_DIRECT_CHANNELS_SOFT;
  ALenum E_REMIX_UNMATCHED_SOFT;
};

#endif
