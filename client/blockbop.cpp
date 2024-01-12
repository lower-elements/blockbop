#include "blockbop.hpp"
#include "state/menu.hpp"

Blockbop::Blockbop() : Application("BlockBop") {}

bool Blockbop::onUserCreate() {
  m_speaker->speak("Welcome to BlockBop!");
  m_states.push(
      new Menu(*this, "Main Menu", {"Single Player", "Multi Player", "Exit"}));
  return true;
}
