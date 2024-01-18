#ifndef BBENGINE_STREAMING_SOURCE_HPP
#define BBENGINE_STREAMING_SOURCE_HPP

#include <cstdint>

#include "al/source.hpp"
#include "audio_file.hpp"

class StreamingSource : public openal::Source {
public: // Associated constants
  static inline constexpr ALsizei NUM_BUFS = 3;

public: // Member methods
  StreamingSource(AudioFile &&stream, ALsizei buf_size = 16000);
  virtual ~StreamingSource();

  void notifyBuffersProcessed(ALsizei bufs);

private:
  /**
   * Fill the specified number of buffers with data, then queue them
   */
  void fillAndQueue(ALsizei num_bufs, ALuint bufs[]);

private: // Member variables
  AudioFile m_stream;
  ALuint m_bufs[NUM_BUFS];
  ALsizei m_buf_size;
};

#endif
