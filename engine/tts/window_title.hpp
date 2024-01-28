#ifndef BBENGINE_TTS_ESPEAK_NG_HPP
#define BBENGINE_TTS_ESPEAK_NG_HPP

#include <string>

#include "tts/speaker.hpp"

// Forward declaration
class Application;

namespace tts {

class WindowTitleSpeaker : public Speaker {
public: // Member methods
  WindowTitleSpeaker(Application &app);

  virtual void speak(const std::string &text, bool interrupt = true) override;
  virtual void key(const char *key, bool interrupt = true) override;
  virtual void stop() override;

private: // Member variables
  Application &m_app;
  std::string m_queued_text;
};

} // namespace tts

#endif
