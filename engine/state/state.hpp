#ifndef BBENGINE_STATE_STATE_HPP
#define BBENGINE_STATE_STATE_HPP

#include <memory>
#include <type_traits>

// Forward-declare this to avoid a circular reference
class Application;

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
  virtual void onPush();
  /**
   * Called before a state has been popped from the state stack
   */
  virtual void onPop();
  /**
   * Called after the state becomes the top state on the stack
   */
  virtual void onEnter();
  /**
   * Called before another state becomes the top state on the stack
   */
  virtual void onExit();
  /**
   * Called every frame
   * @returns true if lower states in the stack should be updated, false
   * otherwise
   */
  virtual bool onUpdate();

private: // Member variables
         // Intrusive linked list members
  State *m_prev_state = nullptr;
  State *m_next_state = nullptr;

protected:
  Application &m_app;

  friend class StateManager;
};

template <class T>
concept StateSubClass = std::is_base_of<State, T>::value;

#endif
