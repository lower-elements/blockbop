#include "al/context.hpp"
#include "al/util.hpp"
namespace openal {

Context::Context(ALCcontext *context) : m_context(context) {}

Context::Context(ALCdevice *device, ALCint attrs[])
    : m_context(alcCreateContext(device, attrs)) {
  if (!m_context) {
    check_alc_error(device);
  }
}

Context::~Context() {
  alcDestroyContext(m_context);
  check_alc_error();
}

void Context::makeCurrent() const {
  if (!alcMakeContextCurrent(m_context)) {
    check_alc_error(m_context);
  }
}

std::optional<Context> Context::current() {
  ALCcontext *ctx = alcGetCurrentContext();
  if (ctx) {
    return Context(ctx);
  } else {
    return {};
  }
}

} // namespace openal
