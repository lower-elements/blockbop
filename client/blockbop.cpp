#include "blockbop.hpp"

Blockbop::Blockbop() : Application("BlockBop") {}

bool Blockbop::onUserCreate() {
  m_speaker->speak("Welcome to BlockBop!");
  return true;
}
