#ifndef BBENGINE_AL_SOURCE_HPP
#define BBENGINE_AL_SOURCE_HPP

#include <cstdint>

#include <al.h>
#include <glm/glm.hpp>

namespace openal {

class Buffer;

class Source {
public: // Member methods
  Source();
  Source(ALuint id);

  Source(Source &&);
  Source &operator=(Source &&);

  ~Source();

  // No copy
  Source(const Source &) = delete;
  Source &operator=(const Source &) = delete;

  bool isValid() const noexcept { return alIsSource(m_id); }

  ALuint getID() const { return m_id; }

  ALint getInt(ALenum prop) const;
  ALenum getEnum(ALenum prop) const { return getInt(prop); }
  float getFloat(ALenum prop) const;
  glm::vec3 getVec3(ALenum prop) const;
  glm::ivec3 getIvec3(ALenum prop) const;

  void setBuffer(Buffer &buffer);
  void setBuffer(ALuint id);

  void set(ALenum prop, ALint val);
  void set(ALenum prop, ALfloat val);
  void set(ALenum prop, glm::vec3 val);
  void set(ALenum prop, glm::ivec3 val);
  void set(ALenum prop, float x, float y, float z);
  void set(ALenum prop, ALint x, ALint y, ALint z);

  void play();
  void stop();
  void rewind();
  void pause();

private: // Member variables
  ALuint m_id;
};

} // namespace openal

#endif
