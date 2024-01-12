#include "state/menu.hpp"

Menu::Menu(Application &app, std::string title,
           std::initializer_list<std::string> items, int default_item)
    : State(app), m_title(title), m_items(items), m_selected(default_item) {}

Menu::~Menu() {}

void Menu::onEnter() {
  // Todo: Play menu-open sound
  m_app.m_speaker->speak(m_title);
}
void Menu::onExit() {
  // Todo: Play menu-close sound
}

bool Menu::onEvent(SDL_Event &ev) {
  if (ev.type == SDL_KEYDOWN) {
    switch (ev.key.keysym.sym) {
    case SDLK_UP:
      prevItem();
      return true;
    case SDLK_DOWN:
      nextItem();
      return true;
    }
  }
  return false;
}

bool Menu::onUpdate() {
  // Menus are (currently) not transparent, so stop rendering here
  return false;
}

const std::string &Menu::getSelectedItem() const {
  return m_items.at(m_selected);
}

void Menu::nextItem() {
  m_selected = (m_selected + 1) % m_items.size();
  m_app.m_speaker->speak(getSelectedItem());
}

void Menu::prevItem() {
  if (m_selected == -1) {
    // Nothing is selected, select last
    m_selected = m_items.size() - 1;
  } else {
    m_selected = (m_selected + m_items.size() - 1) % m_items.size();
  }
  m_app.m_speaker->speak(getSelectedItem());
}
