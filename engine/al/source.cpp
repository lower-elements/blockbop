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

Source::~Source() { alDeleteSources(1, &m_id); }

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
