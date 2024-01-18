#ifndef BBENGINE_AUDIO_MANAGER_HPP
#define BBENGINE_AUDIO_MANAGER_HPP

#include <memory>
#include <unordered_map>

#include "al/buffer.hpp"
#include "al/context.hpp"
#include "al/device.hpp"
#include "al/extensions/direct_channels.hpp"
#include "al/extensions/events.hpp"
#include "al/source.hpp"
#include "audio_file.hpp"
#include "streaming_source.hpp"

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
  std::shared_ptr<openal::Source> playByPath(const char *path);

  /**
   * Play a oneshot source
   * Takes ownership of the passed source, and plays it until it finishes it.
   * The source will automatically be garbage collected when it finishes playing
   * @param source The source to turn into a oneshot
   */
  void playOneshot(std::shared_ptr<openal::Source> src);

  bool onEvent(SDL_Event &ev);

private:
  void onAlEvent(ALenum event, ALuint object, ALuint param,
                 std::string_view message);

private: // Member variables
  openal::Device m_dev;
  openal::Context m_ctx;
  std::unordered_map<std::string, openal::Buffer> m_loaded_buffers;
  std::unordered_map<ALuint, std::shared_ptr<openal::Source>> m_oneshots;
  std::unordered_map<ALuint, std::weak_ptr<StreamingSource>>
      m_streaming_sources;
  Uint32 m_openal_event;

public: // OpenAL extensions
  openal::DirectChannelsExtension m_direct_channels;
  openal::EventsExtension m_events;
};

#endif
