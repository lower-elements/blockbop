#include <fmt/core.h>

#include "al/device.hpp"
#include "al/util.hpp"

namespace openal {

void check_alc_error(Device *device) {
  if (device) {
    check_alc_error(device->get());
  } else {
    check_alc_error(static_cast<ALCdevice *>(nullptr));
  }
}

void check_alc_error(ALCdevice *device) {
  ALCenum err = alcGetError(device);
  if (err != ALC_NO_ERROR) {
    throw Error(err, device);
  }
}

Error::Error(ALCenum errcode, ALCdevice *device)
    : m_errstr(), m_device(device), m_errcode(errcode) {
  // Create the error string
  const char *alc_error = alcGetString(device, errcode);
  if (alc_error) {
    m_errstr = fmt::format("OpenAL error: {}", alc_error);
  } else {
    m_errstr = fmt::format("OpenAL error: Unknown error {}", errcode);
  }
}

const char *Error::what() const noexcept { return m_errstr.c_str(); }

} // namespace openal
