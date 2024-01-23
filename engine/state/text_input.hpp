#ifndef BBENGINE_STATE_TEXT_INPUT_HPP
#define BBENGINE_STATE_TEXT_INPUT_HPP

#include <cstddef>
#include <string>

#include <SDL.h>

#include "state/state.hpp"

class Application;

class TextInputState : public State {
public: // Member methods
  TextInputState(Application &app, std::string prompt,
                 std::string default_text = "");
  virtual ~TextInputState() {}

  virtual void onEnter() override;
  virtual void onExit() override;
  virtual bool onEvent(SDL_Event &ev) override;

protected:
  void insertText(const char *text);
  void backspace();
  void del();
  void cursorLeft();
  void cursorRight();
  void cursorBeginning();
  void cursorEnd();

private: // Member variables
  std::string m_prompt;
  std::string m_text;
  std::size_t m_pos, m_mark;
};

#endif
