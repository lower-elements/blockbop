#include "al/source.hpp"
#include "al/buffer.hpp"
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

ALenum Source::getState() const {
  ALenum state;
  alGetSourcei(m_id, AL_SOURCE_STATE, &state);
  check_al_error();
  return state;
}

void Source::setBuffer(Buffer &buffer) { setBuffer(buffer.id()); }

void Source::setBuffer(ALuint id) {
  alSourcei(m_id, AL_BUFFER, id);
  check_al_error();
}

void Source::setPosition(float x, float y, float z) {
  alSource3f(m_id, AL_POSITION, x, y, z);
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
