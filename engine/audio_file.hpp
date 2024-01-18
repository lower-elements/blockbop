#ifndef BBENGINE_AUDIO_FILE_HPP
#define BBENGINE_AUDIO_FILE_HPP

#include <cstdint>

#include <SDL2pp/RWops.hh>
#include <sndfile.h>

#include "al/buffer.hpp"

class AudioFile {
private: // Member methods
  AudioFile(SDL2pp::RWops &&ops, int mode = SFM_READ);

public:
  // Move constructors and assignment
  AudioFile(AudioFile &&);
  AudioFile &operator=(AudioFile &&);

  static AudioFile fromFile(const std::string &path, int mode = SFM_READ);

  // No copy
  AudioFile(const AudioFile &) = delete;
  AudioFile &operator=(const AudioFile &) = delete;

  ~AudioFile();

  sf_count_t numFrames() const { return m_info.frames; }
  int getSampleRate() const { return m_info.samplerate; }
  int numChannels() const { return m_info.channels; }
  int getFormat() const { return m_info.format; }
  int numSections() const { return m_info.sections; }
  bool isSeekable() const { return m_info.seekable != 0; }
  sf_count_t numSamples() const { return numFrames() * numChannels(); }

  sf_count_t read(void *ptr, sf_count_t bytes);
  sf_count_t read(std::int16_t *ptr, sf_count_t samples);
  sf_count_t read(std::int32_t *ptr, sf_count_t samples);
  sf_count_t read(float *ptr, sf_count_t samples);
  sf_count_t read(double *ptr, sf_count_t samples);

  sf_count_t seek(sf_count_t frames, int whence);

  /**
   * Fill a buffer with the entire audio file
   * @param buf OpenAL buffer to fill
   * @returns The number of samples read
   */
  sf_count_t fillBuffer(openal::Buffer &buf) {
    return fillBuffer(buf, numSamples());
  }
  /**
   * Fill a buffer with the specified number of samples of data from the audio
   * file
   * @param buf OpenAL buffer to fill
   * @returns The number of samples read
   */
  sf_count_t fillBuffer(openal::Buffer &buf, sf_count_t num_samples);

private: // Member variables
  SDL2pp::RWops m_ops;
  SNDFILE *m_sndfile;
  SF_INFO m_info;
};

#endif
