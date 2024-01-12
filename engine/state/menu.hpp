#ifndef BBENGINE_STATE_MENU_HPP
#define BBENGINE_STATE_MENU_HPP

#include <initializer_list>
#include <string>
#include <vector>

#include "application.hpp"
#include "state/state.hpp"

class Menu : public State {
public: // Member methods
  Menu(Application &app, std::string title = "Menu",
       std::initializer_list<std::string> items = {}, int default_item = -1);
  virtual ~Menu() override;

  virtual void onEnter() override;
  virtual void onExit() override;
  virtual bool onEvent(SDL_Event &ev) override;
  virtual bool onUpdate() override;

protected: // Helper methods
  const std::string &getSelectedItem() const;
  void nextItem();
  void prevItem();

private: // Member variables
  std::string m_title;
  std::vector<std::string> m_items;
  int m_selected;
};

#endif
