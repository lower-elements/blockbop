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
   * lifetime of the source is managed by the AudioManager, but can be extended
   * by saving the returne value of this function.
   * @param path Path to the audio file to play
   * @returns A handle to the loaded source, which can be saved to extend the
   * lifetime of this source
   */
  std::shared_ptr<openal::Source> playByPath(const char *path);

  /**
   * stream a oneshot source
   * Plays a oneshot source by streaming the audio data from disk as it's
   * required, reducing memory usage for long files. The lifetime of the source
   * is managed by the AudioManager, but can be extended by saving the returne
   * value of this function.
   * @param path Path to the audio file to play
   * @returns A handle to the loaded source, which can be saved to extend the
   * lifetime of this source
   */
  std::shared_ptr<StreamingSource> streamByPath(const char *path);

  /**
   * Play a oneshot source
   * Takes a reference to the passed source, and plays it until it finishes it.
   * The AudioManager will ensure the source stays alive until it has finished
   * playing
   * @param source The source to turn into a oneshot
   */
  void playOneshot(std::shared_ptr<openal::Source> src);

  void streamSource(std::shared_ptr<StreamingSource> src);

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
