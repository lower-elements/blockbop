#include "tts/window_title.hpp"
#include "application.hpp"

namespace tts {

WindowTitleSpeaker::WindowTitleSpeaker(Application &app) : m_app(app) {}

void WindowTitleSpeaker::speak(const std::string &text, bool interrupt) {
  m_queued_text += text;
  if (interrupt) {
    m_app.m_win.SetTitle(m_queued_text);
    m_queued_text.clear();
  }
}
void WindowTitleSpeaker::key(const char *key, bool interrupt) {
  m_queued_text += key;
  if (interrupt) {
    m_app.m_win.SetTitle(m_queued_text);
    m_queued_text.clear();
  }
}

void WindowTitleSpeaker::stop() {}

} // namespace tts
