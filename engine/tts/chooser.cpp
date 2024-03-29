#include <exception>

#include "application.hpp"
#include "config.hpp"
#if HAVE_ESPEAK_NG
#include "tts/espeak_ng.hpp"
#endif
#if HAVE_TOLK
#include "tts/tolk.hpp"
#endif
#include "tts/window_title.hpp"

#include "tts/chooser.hpp"

namespace tts {

using Factory = std::unique_ptr<Speaker> (*)(Application &);

#if HAVE_ESPEAK_NG
static std::unique_ptr<Speaker> make_espeak_ng_speaker(Application &) {
  return std::make_unique<EspeakNgSpeaker>();
}
#endif
#if HAVE_TOLK
static std::unique_ptr<Speaker> make_tolk_speaker(Application &) {
  return std::make_unique<TolkSpeaker>();
}
#endif
static std::unique_ptr<Speaker> make_window_title_speaker(Application &app) {
  return std::make_unique<WindowTitleSpeaker>(app);
}

static const Factory FACTORIES[] {
#if HAVE_TOLK
  make_tolk_speaker,
#endif
#if HAVE_ESPEAK_NG
      make_espeak_ng_speaker,
#endif
      make_window_title_speaker
};

std::unique_ptr<Speaker> choose(Application &app) {
  std::unique_ptr<Speaker> speaker;
  for (const Factory factory : FACTORIES) {
    try {
      return factory(app);
    } catch (...) {
      continue;
    }
  }
  throw std::runtime_error("No tts engine is available");
}

} // namespace tts
