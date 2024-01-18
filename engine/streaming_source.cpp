#include <utility>

#include <al.h>

#include "al/util.hpp"
#include "streaming_source.hpp"

using openal::check_al_error;

StreamingSource::StreamingSource(AudioFile &&stream, ALsizei buf_size)
    : m_stream(std::move(stream)), m_buf_size(buf_size) {
  ALuint bufs[NUM_BUFS];
  alGenBuffers(NUM_BUFS, bufs);
  check_al_error();
  fillAndQueue(NUM_BUFS, bufs);
}

StreamingSource::~StreamingSource() {
  stop();
  ALuint bufs[NUM_BUFS];
  alSourceUnqueueBuffers(m_id, NUM_BUFS, bufs);
  alDeleteBuffers(NUM_BUFS, bufs);
}

void StreamingSource::notifyBuffersProcessed(ALsizei num_bufs) {
  ALuint bufs[NUM_BUFS];
  alSourceUnqueueBuffers(m_id, num_bufs, bufs);
  check_al_error();
  fillAndQueue(num_bufs, bufs);
}

void StreamingSource::fillAndQueue(ALsizei num_bufs, ALuint bufs[]) {
  ALsizei i;
  for (i = 0; i < num_bufs; ++i) {
    // Type punning: this is safe so long as Buffer is always represented as
    // just an ID
    openal::Buffer *buf_ptr = reinterpret_cast<openal::Buffer *>(&bufs[i]);
    auto num_read = m_stream.fillBuffer(*buf_ptr, m_buf_size);
    if (num_read < m_buf_size) {
      // End of file, we don't need the additional buffers
      if (i < num_bufs) {
        alDeleteBuffers(num_bufs - i - 1, &bufs[i + 1]);
        check_al_error();
      }
      ++i;
      break;
    }
  }
  // Queue the buffers
  alSourceQueueBuffers(m_id, i, bufs);
  check_al_error();
}
