#ifndef BBENGINE_AL_DEVICE_HPP
#define BBENGINE_AL_DEVICE_HPP

#include <alc.h>

namespace openal {

class Device {
public: // Member methods
  Device(const char *name = nullptr);
  ~Device();

  // No copy
  Device(const Device &) = delete;
  Device &operator=(const Device &) = delete;

  ALCdevice *get() { return m_device; }
  const ALCdevice *get() const { return m_device; }

private: // Member variables
  ALCdevice *m_device;
};

} // namespace openal

#endif
