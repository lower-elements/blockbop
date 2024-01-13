#include <glm/gtc/type_ptr.hpp>

#include "al/buffer.hpp"
#include "al/source.hpp"
#include "al/util.hpp"

namespace openal {

Source::Source(ALuint id) : m_id(id) {
  if (!alIsSource(id)) {
    throw AlError(AL_INVALID_NAME);
  }
}

Source::Source() {
  alGenSources(1, &m_id);
  check_al_error();
}

Source::Source(Source &&other) : m_id(other.m_id) { other.m_id = AL_NONE; }

Source &Source::operator=(Source &&other) {
  m_id = other.m_id;
  other.m_id = AL_NONE;
  return *this;
}

Source::~Source() { alDeleteSources(1, &m_id); }

ALint Source::getInt(ALenum prop) const {
  ALint val;
  alGetSourcei(m_id, prop, &val);
  check_al_error();
  return val;
}

float Source::getFloat(ALenum prop) const {
  float val;
  alGetSourcef(m_id, prop, &val);
  check_al_error();
  return val;
}

glm::vec3 Source::getVec3(ALenum prop) const {
  float vals[3];
  alGetSourcefv(m_id, prop, vals);
  check_al_error();
  return glm::make_vec3(vals);
}

glm::ivec3 Source::getIvec3(ALenum prop) const {
  ALint vals[3];
  alGetSourceiv(m_id, prop, vals);
  check_al_error();
  return glm::make_vec3(vals);
}

void Source::setBuffer(Buffer &buffer) { setBuffer(buffer.getID()); }

void Source::setBuffer(ALuint id) {
  alSourcei(m_id, AL_BUFFER, id);
  check_al_error();
}

void Source::set(ALenum prop, ALint val) {
  alSourcei(m_id, prop, val);
  check_al_error();
}

void Source::set(ALenum prop, ALfloat val) {
  alSourcef(m_id, prop, val);
  check_al_error();
}

void Source::set(ALenum prop, glm::vec3 val) {
  alSourcefv(m_id, prop, glm::value_ptr(val));
  check_al_error();
}

void Source::set(ALenum prop, glm::ivec3 val) {
  alSourceiv(m_id, prop, glm::value_ptr(val));
  check_al_error();
}

void Source::set(ALenum prop, float x, float y, float z) {
  alSource3i(m_id, prop, x, y, z);
  check_al_error();
}
void Source::set(ALenum prop, ALint x, ALint y, ALint z) {
  alSource3f(m_id, prop, x, y, z);
  check_al_error();
}

void Source::play() {
  alSourcePlay(m_id);
  check_al_error();
}

void Source::stop() {
  alSourceStop(m_id);
  check_al_error();
}

void Source::rewind() {
  alSourceRewind(m_id);
  check_al_error();
}

void Source::pause() {
  alSourcePause(m_id);
  check_al_error();
}

} // namespace openal
