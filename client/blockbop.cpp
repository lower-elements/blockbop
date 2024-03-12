#include <fmt/core.h>

#include "al/source.hpp"
#include "blockbop.hpp"
#include "state/menu.hpp"
#include "state/text_input.hpp"

Blockbop::Blockbop() : Application("lower-elements", "BlockBop") {}

bool Blockbop::onUserCreate() {
  m_speaker->speak("Welcome to BlockBop!");

  m_states.push(
      new Menu(*this, "Main Menu", {"Single Player", "Multi Player", "Exit"}));

  // m_states.push(new TextInputState(*this, "Enter text: "));

  // m_audio.streamByPath("complete.ogg");

  return true;
}

bool Blockbop::onUserEvent(SDL_Event &ev) {
  if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_F11) {
    std::string fps(fmt::format("{:.0f} fps", getFrameRate()));
    m_speaker->speak(fps);
    return true;
  }
  return Application::onUserEvent(ev);
}
