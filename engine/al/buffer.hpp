#ifndef BBENGINE_AL_BUFFER_HPP
#define BBENGINE_AL_BUFFER_HPP

#include <cstdint>

#include <al.h>
#include <alext.h>

namespace openal {

class Buffer {
public: // Member methods
  Buffer();
  Buffer(ALuint id);

  ~Buffer();

  // No copy
  Buffer(const Buffer &) = delete;
  Buffer &operator=(const Buffer &) = delete;

  Buffer(Buffer &&);
  Buffer &operator=(Buffer &&other);

  ALuint getID() const { return m_id; }
  bool isValid() const noexcept { return alIsBuffer(m_id); }

  void setData(ALenum format, void *data, ALsizei len, ALsizei freq = 48000);
  void setMonoData(std::int8_t *data, ALsizei len, ALsizei freq = 48000);
  void setStereoData(std::int8_t *data, ALsizei len, ALsizei freq = 48000);
  void setMonoData(std::int16_t *data, ALsizei len, ALsizei freq = 48000);
  void setStereoData(std::int16_t *data, ALsizei len, ALsizei freq = 48000);
#ifdef AL_EXT_float32
  void setMonoData(float *data, ALsizei len, ALsizei freq = 48000);
  void setStereoData(float *data, ALsizei len, ALsizei freq = 48000);
#endif

private: // Member variables
  ALuint m_id;
};

} // namespace openal

#endif
