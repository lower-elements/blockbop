#ifndef BBENGINE_STATE_MANAGER_HPP
#define BBENGINE_STATE_MANAGER_HPP

#include <utility>

#include "state/state.hpp"

class StateManager {
public: // Member methods
  StateManager() {}
  ~StateManager();

  // No copy
  StateManager(const StateManager &) = delete;
  StateManager &operator=(const StateManager &) = delete;

  // Functions called by the application

  void onEvent(SDL_Event &ev);
  bool onUpdate();

  // State stack operations:

  /**
   * Push a new state object to the top of the stack
   * The state *must* be created with operator new!
   */
  void push(State *state);
  void push(std::unique_ptr<State> &&state) { push(state.release()); }

  /**
   * Construct a new state subclass and push it to the top of the stack
   */
  template <StateSubClass T, class... Args> void push(Args &&...args) {
    State *ptr = new T(std::forward(args...));
    push(ptr);
  }

  /**
   * Pop a state from the top of the stack
   * The returned state (if any) is disconnected from the stack and is owned by
   * the caller
   */
  std::unique_ptr<State> pop();

private: // Member variables
  State *m_head = nullptr;
};

#endif
