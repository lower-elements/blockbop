#ifndef BBENGINE_AL_BUFFER_HPP
#define BBENGINE_AL_BUFFER_HPP

#include <cstdint>

#include <al.h>

namespace openal {

class Buffer {
public: // Member methods
  Buffer();
  Buffer(ALuint id);

  ~Buffer();

  // No copy
  Buffer(const Buffer &) = delete;
  Buffer &operator=(const Buffer &) = delete;

  ALuint id() const { return m_id; }
  bool isValid() const noexcept { return alIsBuffer(m_id); }

  void setData(ALenum format, void *data, ALsizei len, ALsizei freq = 48000);
  void setMonoData(std::int8_t *data, ALsizei len, ALsizei freq = 48000);
  void setMonoData(std::int16_t *data, ALsizei len, ALsizei freq = 48000);
  void setStereoData(std::int8_t *data, ALsizei len, ALsizei freq = 48000);
  void setStereoData(std::int16_t *data, ALsizei len, ALsizei freq = 48000);

private: // Member variables
  ALuint m_id;
};

} // namespace openal

#endif
