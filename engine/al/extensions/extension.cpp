#include <cassert>
#include <type_traits>

#include <al.h>
#include <alc.h>

#include "al/extensions/extension.hpp"

// Safety to ensure the return type of Extension::getEnumValue is okay
static_assert(std::is_same_v<ALCenum, ALenum>,
              "ALCenum and ALenum must be the same type");
// ALCboolean and ALboolean needs to be the same too
static_assert(std::is_same_v<ALCboolean, ALboolean>,
              "ALCboolean and ALboolean must be the same type");
static_assert(ALC_FALSE == AL_FALSE);
static_assert(ALC_TRUE == AL_TRUE);

namespace openal {

Extension::Extension(ALboolean is_supported)
    : m_supported(is_supported == AL_TRUE) {}

AlcExtension::AlcExtension(ALCdevice *dev, const char *name)
    : Extension(alcIsExtensionPresent(dev, name)), m_dev(dev) {}

ALenum AlcExtension::getEnum(const char *name) const {
  return alcGetEnumValue(m_dev, name);
}

void *AlcExtension::getProcAddress(const char *name) const {
  return alcGetProcAddress(m_dev, name);
}

AlExtension::AlExtension(const char *name)
    : Extension(alIsExtensionPresent(name)) {}

ALenum AlExtension::getEnum(const char *name) const {
  return alGetEnumValue(name);
}

void *AlExtension::getProcAddress(const char *name) const {
  return alGetProcAddress(name);
}

} // namespace openal
