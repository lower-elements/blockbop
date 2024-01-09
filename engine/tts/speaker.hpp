#ifndef BBENGINE_TTS_SPEAKER_HPP
#define BBENGINE_TTS_SPEAKER_HPP

#include <string_view>

namespace tts {

/**
 * Abstract base class representing a speech synthesis method
 */
class Speaker {
public:
  Speaker() {}

  virtual ~Speaker() {}

  virtual void speak(std::string_view text, bool interrupt = true) = 0;
  virtual void key(const char *key, bool interrupt = true) = 0;
  virtual void stop() = 0;

  // No copy
  Speaker(const Speaker &) = delete;
  Speaker &operator=(const Speaker &) = delete;
};

} // namespace tts

#endif
