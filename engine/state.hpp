#ifndef BBENGINE_STATE_HPP
#define BBENGINE_STATE_HPP

#include "application.hpp"

class State {
protected: // Member methods
           /**
            * Construct a new state (used by subclasses)
            */
  State(Application &app);

public:
  virtual ~State();

  // No copy
  State(const State &) = delete;
  State &operator=(const State &) = delete;

  /**
   * Called after a state is pushed to the top of the state stack
   */
  virtual void onPush() = 0;
  /**
   * Called before a state has been popped from the state stack
   */
  virtual void onPop() = 0;
  /**
   * Called after the state becomes the top state on the stack
   */
  virtual void onEnter() = 0;
  /**
   * Called before another state becomes the top state on the stack
   */
  virtual void onExit() = 0;
  /**
   * Called every frame
   * @returns true if lower states in the stack should be updated, false
   * otherwise
   */
  virtual bool onUpdate() = 0;

private: // Member variables
         // Intrusive linked list members
  State *m_prev_state = nullptr;
  State *m_next_state = nullptr;
  Application &m_app;
};

#endif
