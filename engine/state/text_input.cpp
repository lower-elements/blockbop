#include <utility>

#include "application.hpp"
#include "charsets.hpp"
#include "state/text_input.hpp"

using namespace charsets;

TextInputState::TextInputState(Application &app, std::string prompt,
                               std::string default_text)
    : State(app), m_prompt(std::move(prompt)), m_text(std::move(default_text)),
      m_pos(m_text.size()), m_mark(std::string::npos) {}

void TextInputState::onEnter() {
  SDL_StartTextInput();

  if (m_text.empty()) {
    m_app.m_speaker->speak(m_prompt);
  } else {
    m_app.m_speaker->speak(fmt::format("{} {} selected", m_prompt, m_text));
  }
}

void TextInputState::onExit() { SDL_StopTextInput(); }

bool TextInputState::onEvent(SDL_Event &ev) {
  switch (ev.type) {
  case SDL_TEXTINPUT:
    insertText(ev.text.text);
    return true;
  case SDL_KEYDOWN:
    if (ev.key.keysym.mod & KMOD_CTRL) {
      switch (ev.key.keysym.sym) {
      case SDLK_v: {
        char *clipboard_text = SDL_GetClipboardText();
        if (!clipboard_text) {
          return true;
        }
        if (*clipboard_text != '\0') {
          insertText(clipboard_text);
        }
        SDL_free(clipboard_text);
      }
        return true;
      }
    } else if (!(ev.key.keysym.mod & KMOD_CTRL)) {
      switch (ev.key.keysym.sym) {
      case SDLK_BACKSPACE:
        backspace();
        return true;
      case SDLK_DELETE:
        del();
        return true;
      case SDLK_LEFT:
        cursorLeft();
        return true;
      case SDLK_RIGHT:
        cursorRight();
        return true;
      case SDLK_HOME:
        cursorBeginning();
        return true;
      case SDLK_END:
        cursorEnd();
        return true;
      }
    }
    return false;
  default:
    return false;
  }
}

void TextInputState::insertText(const char *text) {
  // Insert the text
  std::size_t len = SDL_strlen(text);
  m_text.insert(m_pos, text, len);
  m_pos += len;

  // Speak the inserted text
  len = SDL_utf8strlen(text);
  if (len == 1) {
    m_app.m_speaker->key(text);
  } else {
    m_app.m_speaker->speak(text);
  }
}

void TextInputState::backspace() {
  auto pos = prevUTF8Character(m_text, m_pos);
  if (pos == std::string::npos) {
    return;
  }

  auto count = m_pos - pos;
  std::string deleted_text(&m_text[pos], count);
  deleted_text += " deleted";

  m_text.erase(pos, count);
  m_pos = pos;

  m_app.m_speaker->speak(deleted_text);
}

void TextInputState::del() {
  if (m_pos == m_text.size()) {
    return; // At end of buffer
  }

  auto new_pos = nextUTF8Character(m_text, m_pos);
  if (new_pos == std::string::npos) {
    new_pos = m_text.size();
  }
  auto count = new_pos - m_pos;
  std::string deleted_text(&m_text[m_pos], count);

  m_text.erase(m_pos, count);

  m_app.m_speaker->key(deleted_text.c_str());
  m_app.m_speaker->speak(" deleted", false);
}

void TextInputState::cursorLeft() {
  auto new_pos = prevUTF8Character(m_text, m_pos);
  if (new_pos == std::string::npos) {
    return;
  }
  std::string ch(&m_text[new_pos], m_pos - new_pos);
  m_pos = new_pos;
  m_app.m_speaker->key(ch.c_str());
}

void TextInputState::cursorRight() {
  if (m_pos == m_text.size()) {
    return; // Already at end
  }

  std::string ch;
  auto new_pos = nextUTF8Character(m_text, m_pos);
  if (new_pos == std::string::npos) {
    new_pos = m_text.size(); // Set cursor to end
    ch = "blank";            // No character to read
  } else {
    // Extract character under cursor
    auto next_pos = nextUTF8Character(m_text, new_pos);
    auto count = next_pos == std::string::npos ? m_text.size() - new_pos
                                               : next_pos - new_pos;
    ch = std::string(&m_text[new_pos], count);
  }

  // Move to the calculated position
  m_pos = new_pos;
  m_app.m_speaker->key(ch.c_str());
}

void TextInputState::cursorBeginning() {
  if (m_text.empty() || m_pos == 0) {
    return;
  }

  m_pos = 0;
  auto next_pos = nextUTF8Character(m_text, 0);
  std::string ch(m_text, 0, next_pos);
  m_app.m_speaker->key(ch.c_str());
}

void TextInputState::cursorEnd() {
  if (m_text.empty() || m_pos == m_text.size()) {
    return;
  }
  m_pos = m_text.size();
  m_app.m_speaker->speak("blank");
}
