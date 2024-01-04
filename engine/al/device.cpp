#include "al/device.hpp"
#include "al/util.hpp"

namespace openal {

Device::Device(const char *name) : m_device(alcOpenDevice(name)) {
  if (!m_device) {
    check_alc_error();
  }
}

Device::~Device() {
  if (m_device)
    alcCloseDevice(m_device);
  check_alc_error();
}

} // namespace openal
