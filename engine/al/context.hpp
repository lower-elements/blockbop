#ifndef BBENGINE_AL_CONTEXT_HPP
#define BBENGINE_AL_CONTEXT_HPP

#include <optional>

#include <alc.h>

namespace openal {

class Context {
public: // Member methods
  Context(ALCcontext *context);
  Context(ALCdevice *device, ALCint attrs[] = {0});

  template <class... Args> Context(ALCdevice *device, Args... args) {
    ALCint attrs[]{args..., 0};
    Context(device, attrs);
  }

  ~Context();

  ALCcontext *get() { return m_context; }
  const ALCcontext *get() const { return m_context; }

  ALCdevice *getDevice() { return alcGetContextsDevice(m_context); }
  const ALCdevice *getDevice() const { return alcGetContextsDevice(m_context); }

  void makeCurrent() const;
  bool isCurrent() const { return m_context == alcGetCurrentContext(); }

public: // Static methods
  static std::optional<Context> current();

private: // Member variables
  ALCcontext *m_context;
};

} // namespace openal

#endif
