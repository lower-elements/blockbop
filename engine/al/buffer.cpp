#include "al/buffer.hpp"
#include "al/util.hpp"

namespace openal {

Buffer::Buffer(ALuint id) : m_id(id) {
  if (!alIsBuffer(id)) {
    throw AlError(AL_INVALID_NAME);
  }
}

Buffer::Buffer() {
  alGenBuffers(1, &m_id);
  check_al_error();
}

Buffer::~Buffer() { alDeleteBuffers(1, &m_id); }

void Buffer::setData(ALenum format, void *data, ALsizei len, ALsizei freq) {
  alBufferData(m_id, format, data, len, freq);
  check_al_error();
}

void Buffer::setMonoData(std::int8_t *data, ALsizei len, ALsizei freq) {
  alBufferData(m_id, AL_FORMAT_MONO8, data, len * sizeof(data[0]), freq);
  check_al_error();
}

void Buffer::setMonoData(std::int16_t *data, ALsizei len, ALsizei freq) {
  alBufferData(m_id, AL_FORMAT_MONO16, data, len * sizeof(data[0]), freq);
  check_al_error();
}

void Buffer::setStereoData(std::int8_t *data, ALsizei len, ALsizei freq) {
  alBufferData(m_id, AL_FORMAT_STEREO8, data, len * sizeof(data[0]), freq);
  check_al_error();
}

void Buffer::setStereoData(std::int16_t *data, ALsizei len, ALsizei freq) {
  alBufferData(m_id, AL_FORMAT_STEREO16, data, len * sizeof(data[0]), freq);
  check_al_error();
}

} // namespace openal
