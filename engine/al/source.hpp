#ifndef BBENGINE_AL_SOURCE_HPP
#define BBENGINE_AL_SOURCE_HPP

#include <cstdint>

#include <al.h>

namespace openal {

class Buffer;

class Source {
public: // Member methods
  Source();
  Source(ALuint id);

  ~Source();

  // No copy
  Source(const Source &) = delete;
  Source &operator=(const Source &) = delete;

  bool isValid() const noexcept { return alIsSource(m_id); }

  void setBuffer(Buffer &buffer);
  void setBuffer(ALuint id);

  void setPosition(float x, float y, float z);

  void play();
  void stop();
  void rewind();
  void pause();

private: // Member variables
  ALuint m_id;
};

} // namespace openal

#endif
