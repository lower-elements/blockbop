#ifndef BBENGINE_AL_EXTENSIONS_DIRECT_CHANNELS_HPP
#define BBENGINE_AL_EXTENSIONS_DIRECT_CHANNELS_HPP

#include "al/extensions/extension.hpp"
#include "al/source.hpp"

namespace openal {

class DirectChannelsExtension : public AlExtension {
public: // Member methods
  DirectChannelsExtension();

  void enable(Source &src) const;
  void disable(Source &src) const;
  void remix(Source &src, ALenum fallback_value = AL_TRUE) const;

private: // Member variables
  ALenum E_DIRECT_CHANNELS_SOFT = AL_NONE;
  ALenum E_REMIX_UNMATCHED_SOFT = AL_NONE;
};

} // namespace openal

#endif
