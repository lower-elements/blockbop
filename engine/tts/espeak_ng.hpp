#ifndef BBENGINE_TTS_ESPEAK_NG_HPP
#define BBENGINE_TTS_ESPEAK_NG_HPP

#include "tts/speaker.hpp"

namespace tts {

class EspeakNgSpeaker : public Speaker {
public:
  EspeakNgSpeaker();

  virtual ~EspeakNgSpeaker() override;

  virtual void speak(const std::string &text, bool interrupt = true) override;
  virtual void key(const char *key, bool interrupt = true) override;
  virtual void stop() override;
};

} // namespace tts

#endif
