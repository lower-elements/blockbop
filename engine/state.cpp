#include "state.hpp"

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
