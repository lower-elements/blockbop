#include <exception>

#include <espeak-ng/espeak_ng.h>
#include <fmt/core.h>

#include "tts/espeak_ng.hpp"

namespace tts {

EspeakNgSpeaker::EspeakNgSpeaker() {
  auto status = espeak_ng_Initialize(nullptr);
  if (status != ENS_OK) {
    char errmsg[256];
    espeak_ng_GetStatusCodeMessage(status, errmsg, sizeof(errmsg));
    throw std::runtime_error(
        fmt::format("Could not initialize espeak-ng: {}", errmsg));
  }
}

EspeakNgSpeaker::~EspeakNgSpeaker() { espeak_ng_Terminate(); }

void EspeakNgSpeaker::speak(std::string_view text, bool interrupt) {
  auto flags = espeakCHARS_UTF8;
  if (interrupt) {
    stop();
    flags |= espeakENDPAUSE;
  }
  auto status = espeak_ng_Synthesize(text.data(), text.size(), 0, POS_CHARACTER,
                                     0, flags, nullptr, nullptr);
  if (status != ENS_OK) {
    char errmsg[256];
    espeak_ng_GetStatusCodeMessage(status, errmsg, sizeof(errmsg));
    throw std::runtime_error(
        fmt::format("Could not speak text with espeak-ng: {}", errmsg));
  }
}

void EspeakNgSpeaker::key(const char *keyname, bool interrupt) {
  if (interrupt) {
    stop();
  }
  auto status = espeak_ng_SpeakKeyName(keyname);
  if (status != ENS_OK) {
    char errmsg[256];
    espeak_ng_GetStatusCodeMessage(status, errmsg, sizeof(errmsg));
    throw std::runtime_error(
        fmt::format("Could not speak key name with espeak-ng: {}", errmsg));
  }
}

void EspeakNgSpeaker::stop() { espeak_ng_Cancel(); }

} // namespace tts
