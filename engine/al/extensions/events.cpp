#include "al/extensions/events.hpp"
#include "al/util.hpp"

namespace openal {

static void callback_wrapper(ALenum event, ALuint object, ALuint param,
                             ALsizei length, const ALchar *message,
                             void *udata) {
  auto &callback = *static_cast<
      std::function<void(ALenum, ALuint, ALuint, std::string_view)> *>(udata);
  std::string_view msg(message, length);
  if (callback) {
    callback(event, object, param, message);
  }
}

EventsExtension::EventsExtension()
    : AlExtension("AL_SOFT_events"), m_callback() {
  if (isSupported()) {
    getFunction("alEventControlSOFT", this->alEventControlSOFT);
    getFunction("alEventCallbackSOFT", this->alEventCallbackSOFT);
    alEventCallbackSOFT(callback_wrapper, &m_callback);

    E_EVENT_TYPE_BUFFER_COMPLETED_SOFT =
        getEnum("AL_EVENT_TYPE_BUFFER_COMPLETED_SOFT");
    E_EVENT_TYPE_SOURCE_STATE_CHANGED_SOFT =
        getEnum("AL_EVENT_TYPE_SOURCE_STATE_CHANGED_SOFT");
    E_EVENT_TYPE_DISCONNECTED_SOFT = getEnum("AL_EVENT_TYPE_DISCONNECTED_SOFT");
  }
}

EventsExtension::~EventsExtension() {
  if (isSupported()) {
    alEventCallbackSOFT(nullptr, nullptr);
  }
}

void EventsExtension::setEvents(ALenum events[], ALsizei length,
                                ALboolean enable) {
  alEventControlSOFT(length, events, enable);
  check_al_error();
}

} // namespace openal
