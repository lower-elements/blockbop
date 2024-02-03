#ifndef BBENGINE_TTS_TOLK_HPP
#define BBENGINE_TTS_TOLK_HPP

#include "library.hpp"
#include "tts/speaker.hpp"

namespace tts {

class TolkSpeaker : Library, public Speaker {
public: // Member Methods
  TolkSpeaker();
  virtual ~TolkSpeaker();

  virtual void speak(const std::string &text, bool interrupt = true) override;
  virtual void key(const char *key, bool interrupt = true) override;
  virtual void stop() override;

private: // Member variables
  void (*Tolk_Load)();
  void (*Tolk_Unload)();
  void (*Tolk_TrySAPI)(bool trySAPI);
  bool (*Tolk_Output)(const wchar_t *text, bool interrupt);
  bool (*Tolk_Silence)();
};

} // namespace tts

#endif
