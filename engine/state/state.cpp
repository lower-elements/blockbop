#include "state/state.hpp"

State::State(Application &app) : m_app(app) {}

State::~State() {
  // Remove this state from the list
  if (m_prev_state) {
    m_prev_state->m_next_state = m_next_state;
  }
  if (m_next_state) {
    m_next_state->m_prev_state = m_prev_state;
  }
}

void State::onPush() {}
void State::onPop() {}
void State::onEnter() {}
void State::onExit() {}
bool State::onEvent(SDL_Event &) { return false; }
bool State::State::onUpdate() { return true; }
