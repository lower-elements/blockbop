#include "state_manager.hpp"

StateManager::~StateManager() {
  // Dete all the states
  while (m_head != nullptr) {
    State *state = m_head;
    m_head = state->m_next_state;
    delete state;
  }
}

bool StateManager::onUpdate() {
  for (State *state = m_head; state != nullptr; state = state->m_next_state) {
    if (state->onUpdate()) {
      break;
    }
  }
  return m_head != nullptr;
}

void StateManager::push(State *state) {
  // Set prev and next correctly
  state->m_prev_state = nullptr;
  state->m_next_state = m_head;
  // Exit the current top state
  if (m_head) {
    m_head->onExit();
  }
  // Push the state
  m_head = state;
  // Notify state that it's pushed and on top
  state->onPush();
  state->onEnter();
}

std::unique_ptr<State> StateManager::pop() {
  State *state = m_head;
  if (state) {
    // Notify the state that it's no longer on top and it's being popped
    state->onExit();
    state->onPop();
    // Remove the state
    m_head = state->m_next_state;
    // Notify the next state that it's now on top
    if (m_head) {
      m_head->onEnter();
    }
  }
  return std::unique_ptr<State>(state);
}
