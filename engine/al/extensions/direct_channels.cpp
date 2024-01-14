#include "al/extensions/direct_channels.hpp"

namespace openal {

DirectChannelsExtension::DirectChannelsExtension()
    : AlExtension("AL_SOFT_direct_channels") {
  if (isSupported()) {
    E_DIRECT_CHANNELS_SOFT = getEnum("AL_DIRECT_CHANNELS_SOFT");
    E_REMIX_UNMATCHED_SOFT = getEnum("AL_REMIX_UNMATCHED_SOFT");
  }
}

void DirectChannelsExtension::enable(Source &src) const {
  src.set(E_DIRECT_CHANNELS_SOFT, AL_TRUE);
}
void DirectChannelsExtension::disable(Source &src) const {
  src.set(E_DIRECT_CHANNELS_SOFT, AL_FALSE);
}
void DirectChannelsExtension::remix(Source &src, ALenum fallback_value) const {
  src.set(E_DIRECT_CHANNELS_SOFT, E_REMIX_UNMATCHED_SOFT != AL_NONE
                                      ? E_REMIX_UNMATCHED_SOFT
                                      : fallback_value);
}

} // namespace openal
