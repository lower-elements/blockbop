#include <cassert>
#include <exception>
#include <memory>

#include <fmt/core.h>

#include "audio_file.hpp"

static sf_count_t rwops_get_filelen(void *data) {
  auto ops = static_cast<SDL_RWops *>(data);
  return (sf_count_t)SDL_RWsize(ops);
}

static sf_count_t rwops_seek(sf_count_t offset, int whence, void *data) {
  auto ops = static_cast<SDL_RWops *>(data);
  return (sf_count_t)SDL_RWseek(ops, offset, whence);
}

static sf_count_t rwops_read(void *ptr, sf_count_t count, void *data) {
  auto ops = static_cast<SDL_RWops *>(data);
  return (sf_count_t)SDL_RWread(ops, ptr, count, 1);
}

static sf_count_t rwops_write(const void *ptr, sf_count_t count, void *data) {
  auto ops = static_cast<SDL_RWops *>(data);
  return (sf_count_t)SDL_RWwrite(ops, ptr, count, 1);
}

static sf_count_t rwops_tell(void *data) {
  auto ops = static_cast<SDL_RWops *>(data);
  return (sf_count_t)SDL_RWtell(ops);
}

static struct SF_VIRTUAL_IO RWOPS_VIO = {
    .get_filelen = rwops_get_filelen,
    .seek = rwops_seek,
    .read = rwops_read,
    .write = rwops_write,
    .tell = rwops_tell,
};

AudioFile::AudioFile(SDL2pp::RWops &&ops, int mode)
    : m_ops(std::move(ops)), m_sndfile(nullptr) {
  m_sndfile = sf_open_virtual(&RWOPS_VIO, mode, &m_info, m_ops.Get());
  if (!m_sndfile) {
    throw std::runtime_error(
        fmt::format("Could not load audio file: {}", sf_strerror(nullptr)));
  }
}

AudioFile AudioFile::fromFile(const std::string &path, int mode) {
  std::string mode_str;
  if (mode == SFM_READ) {
    mode_str = "rb";
  } else if (mode == SFM_WRITE) {
    mode_str = "wb";
  } else if (mode == SFM_RDWR) {
    mode_str = "rb+";
  } else {
    throw std::runtime_error("Invalid mode specified when opening audio file");
  }
  auto ops(SDL2pp::RWops::FromFile(path, mode_str));
  return AudioFile(std::move(ops), mode);
}

AudioFile::~AudioFile() {
  if (m_sndfile) {
    sf_close(m_sndfile);
  }
}

sf_count_t AudioFile::read(void *ptr, sf_count_t bytes) {
  auto res = sf_read_raw(m_sndfile, ptr, bytes);
  if (res < 0) {
    throw std::runtime_error(fmt::format("Could not read from audio file: {}",
                                         sf_strerror(m_sndfile)));
  }
  return res;
}

static_assert(sizeof(short) == sizeof(std::int16_t));
sf_count_t AudioFile::read(std::int16_t *ptr, sf_count_t bytes) {
  auto res = sf_read_short(m_sndfile, ptr, bytes);
  if (res < 0) {
    throw std::runtime_error(fmt::format("Could not read from audio file: {}",
                                         sf_strerror(m_sndfile)));
  }
  return res;
}

static_assert(sizeof(int) == sizeof(std::int32_t));
sf_count_t AudioFile::read(std::int32_t *ptr, sf_count_t bytes) {
  auto res = sf_read_int(m_sndfile, ptr, bytes);
  if (res < 0) {
    throw std::runtime_error(fmt::format("Could not read from audio file: {}",
                                         sf_strerror(m_sndfile)));
  }
  return res;
}

sf_count_t AudioFile::read(float *ptr, sf_count_t bytes) {
  auto res = sf_read_float(m_sndfile, ptr, bytes);
  if (res < 0) {
    throw std::runtime_error(fmt::format("Could not read from audio file: {}",
                                         sf_strerror(m_sndfile)));
  }
  return res;
}

sf_count_t AudioFile::read(double *ptr, sf_count_t bytes) {
  auto res = sf_read_double(m_sndfile, ptr, bytes);
  if (res < 0) {
    throw std::runtime_error(fmt::format("Could not read from audio file: {}",
                                         sf_strerror(m_sndfile)));
  }
  return res;
}

openal::Buffer AudioFile::makeBuffer() {
  auto num_samples = numSamples();
  std::unique_ptr<std::int16_t[]> samples(new std::int16_t[num_samples]);
  auto num_read = read(samples.get(), num_samples);
  openal::Buffer buf;
  if (m_info.channels == 1) {
    buf.setMonoData(samples.get(), num_read, m_info.samplerate);
  } else if (m_info.channels == 2) {
    buf.setStereoData(samples.get(), num_read, m_info.samplerate);
  } else {
    throw std::runtime_error(
        fmt::format("Invalid number of channels, expected 1 or 2, got {}",
                    m_info.channels));
  }
  return buf;
}
