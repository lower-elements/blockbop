#ifndef BBENGINE_AL_EXTENSIONS_EVENTS_HPP
#define BBENGINE_AL_EXTENSIONS_EVENTS_HPP

#include <functional>
#include <string_view>

#include "al/extensions/extension.hpp"
#include "al/util.hpp"

namespace openal {

typedef void(AL_APIENTRY *ALEVENTPROCSOFT)(ALenum eventType, ALuint object,
                                           ALuint param, ALsizei length,
                                           const ALchar *message,
                                           ALvoid *userParam);

// For internal use only
AL_APIENTRY void callback_wrapper(ALenum, ALuint, ALuint, ALsizei,
                                  const ALchar *, void *);

class EventsExtension : public AlExtension {
public: // Member methods
  EventsExtension();
  ~EventsExtension();

  void resetCallback();

  template <class T> void setCallback(T cb) {
    m_callback = cb;
    if (m_callback) {
      alEventCallbackSOFT(callback_wrapper, &m_callback);
      check_al_error();
    }
  }

  void setEvents(ALenum events[], ALsizei length, ALboolean enable);

  template <class... T> void enableEvents(T... events) {
    ALenum events_array[]{events...};
    setEvents(events_array, sizeof...(events), AL_TRUE);
  }

  template <class... T> void disableEvents(T... events) {
    ALenum events_array[]{events...};
    setEvents(events_array, sizeof...(events), AL_FALSE);
  }

private: // Member variables
  std::function<void(ALenum, ALuint, ALuint, std::string_view)> m_callback;

  // Use this->member when assigning these to avoid name conflicts, in case the
  // AL headers include these. The OpenAL Soft ones don't seem to, but other
  // implementations might have them
  void(AL_APIENTRY *alEventControlSOFT)(ALsizei count, const ALenum *types,
                                        ALboolean enable) = nullptr;
  void(AL_APIENTRY *alEventCallbackSOFT)(ALEVENTPROCSOFT callback,
                                         ALvoid *userParam) = nullptr;

public:
  ALenum E_EVENT_TYPE_BUFFER_COMPLETED_SOFT = AL_NONE;
  ALenum E_EVENT_TYPE_SOURCE_STATE_CHANGED_SOFT = AL_NONE;
  ALenum E_EVENT_TYPE_DISCONNECTED_SOFT = AL_NONE;
};

} // namespace openal

#endif
