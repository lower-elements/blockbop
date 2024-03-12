#ifndef BBENGINE_APPLICATION_HPP
#define BBENGINE_APPLICATION_HPP

#include <SDL_opengles2.h>
#include <memory>

#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "audio_manager.hpp"
#include "state/manager.hpp"
#include "tts/speaker.hpp"

/**
 * Base class for an application using this engine
 */
class Application {
public:
  /**
   * Constructor
   */
  Application(const char *org_name, const char *app_name, int width = 640,
              int height = 480);

  /**
   * Destructor
   * Calls onUserDestroy() automatically
   */
  ~Application();

  // No copy
  Application(const Application &) = delete;
  Application &operator=(const Application &) = delete;

  /**
   * Run the application until it decides to quit
   * @returns exit status that can be returned from main()
   */
  int run();

  /**
   * Request that the app quit
   */
  void quit() noexcept { m_continue_running = false; }

  /**
   * Get the app's preference path
   * @returns A directory path, this is the only directory guaranteed to be
   * writable
   */
  const char *getPrefPath() const { return m_pref_path.get(); }

  /**
   * Get the application's current frame rate
   */
  float getFrameRate() const noexcept { return m_fps; }

protected: // Functions implemented by subclasses
  /**
   * Called once when the application begins running
   * @returns true if the application should continue running
   */
  virtual bool onUserCreate();
  /**
   * Called every frame
   * @returns true if the application should continue running
   */
  virtual bool onUserUpdate();
  /**
   * Process a received SDL event
   * @param ev The newly received event
   * @returns true if the Application handled the event, false to proppogate it
   * to states
   */
  virtual bool onUserEvent(SDL_Event &ev);
  /**
   * Called when the application is exitting
   */
  virtual void onUserDestroy();

public: // Member variables
  SDL2pp::SDL m_sdl;
  SDL2pp::Window m_win;
  AudioManager m_audio;
  std::unique_ptr<tts::Speaker> m_speaker;
  StateManager m_states;

private:
  SDL_GLContext m_gl_ctx;
  std::unique_ptr<char[], void (*)(void *)> m_pref_path;
  float m_fps;
  bool m_continue_running;
};

#endif
