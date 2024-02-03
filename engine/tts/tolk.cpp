#include "tts/tolk.hpp"
#include "charsets.hpp"

namespace tts {

TolkSpeaker::TolkSpeaker() : Library("Tolk") {
  getSymbol("Tolk_Load", this->Tolk_Load);
  getSymbol("Tolk_Unload", this->Tolk_Unload);
  getSymbol("Tolk_TrySAPI", this->Tolk_TrySAPI);
  getSymbol("Tolk_Output", this->Tolk_Output);
  getSymbol("Tolk_Silence", this->Tolk_Silence);

  Tolk_TrySAPI(true);
  Tolk_Load();
}

TolkSpeaker::~TolkSpeaker() {
  if (Tolk_Unload) {
    Tolk_Unload();
  }
}

void TolkSpeaker::speak(const std::string &text, bool interrupt) {
  auto str = charsets::convert<wchar_t>("WCHAR_T", "UTF-8", text);
  Tolk_Output(str.get(), interrupt);
}

void TolkSpeaker::key(const char *key, bool interrupt) {
  char16_t utf16_char[3];
  auto len = charsets::UTF8toUTF16(key, utf16_char);
  if (len == 0) {
    return;
  }
  utf16_char[len] = 0;
  Tolk_Output((wchar_t *)utf16_char, interrupt);
}

void TolkSpeaker::stop() { Tolk_Silence(); }

} // namespace tts
