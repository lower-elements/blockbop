#ifndef BBENGINE_TTS_CHOOSER_HPP
#define BBENGINE_TTS_CHOOSER_HPP

#include <memory>

#include "tts/speaker.hpp"

// Forward declaration
class Application;

namespace tts {

std::unique_ptr<Speaker> choose(Application &app);

}

#endif
