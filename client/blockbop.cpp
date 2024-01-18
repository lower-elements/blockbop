#include <fmt/core.h>

#include "al/source.hpp"
#include "blockbop.hpp"
#include "state/menu.hpp"

Blockbop::Blockbop() : Application("lower-elements", "BlockBop") {}

bool Blockbop::onUserCreate() {
  m_speaker->speak("Welcome to BlockBop!");

  m_states.push(
      new Menu(*this, "Main Menu", {"Single Player", "Multi Player", "Exit"}));

  m_audio.streamByPath("complete.ogg");

  return true;
}
