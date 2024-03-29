#ifndef BLOCKBOP_BLOCKBOP_HPP
#define BLOCKBOP_BLOCKBOP_HPP

#include "application.hpp"

class Blockbop : public Application {
public:
  Blockbop();

protected:
  virtual bool onUserCreate() override;
  virtual bool onUserEvent(SDL_Event &ev) override;
};

#endif
