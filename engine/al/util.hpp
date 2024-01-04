#ifndef BBENGINE_AL_UTIL_HPP
#define BBENGINE_AL_UTIL_HPP

#include <exception>
#include <string>

#include <alc.h>

namespace openal {

// Avoid cyclic references
class Device;

/**
 * Check for OpenAL context errors
 */
void check_alc_error(ALCcontext *context);
void check_alc_error(Device *device);
void check_alc_error(ALCdevice *device = nullptr);

/**
 * An exception class thrown by check_alc_error()
 */
class Error : std::exception {
public:
  Error(ALCenum errcode, ALCdevice *device = nullptr);

  virtual const char *what() const noexcept override;

private:
  std::string m_errstr;
  ALCdevice *m_device;
  ALCenum m_errcode;
};

} // namespace openal

#endif
