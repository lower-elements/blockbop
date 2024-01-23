#include "al/extensions/pause_device.hpp"

namespace openal {

PauseDeviceExtension::PauseDeviceExtension(ALCdevice *dev)
    : AlcExtension(dev, "ALC_SOFT_pause_device") {
  if (isSupported()) {
    getFunction("alcDevicePauseSOFT", this->alcDevicePauseSOFT);
    getFunction("alcDeviceResumeSOFT", this->alcDeviceResumeSOFT);
  }
}

} // namespace openal
