#ifndef BBENGINE_AL_EXTENSIONS_PAUSE_DEVICE_HPP
#define BBENGINE_AL_EXTENSIONS_PAUSE_DEVICE_HPP

#include <alc.h>

#include "al/extensions/extension.hpp"

namespace openal {

class PauseDeviceExtension : public AlcExtension {
public:
  PauseDeviceExtension(ALCdevice *dev);

  void pause() { alcDevicePauseSOFT(m_dev); }
  void resume() { alcDeviceResumeSOFT(m_dev); }

private: // Member variables
  void(ALC_APIENTRY *alcDevicePauseSOFT)(ALCdevice *) = nullptr;
  void(ALC_APIENTRY *alcDeviceResumeSOFT)(ALCdevice *) = nullptr;
};

} // namespace openal
#endif
