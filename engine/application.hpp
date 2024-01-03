#ifndef BBENGINE_APPLICATION_HPP
#define BBENGINE_APPLICATION_HPP

#include <SDL2pp/SDL2pp.hh>

/**
 * Base class for an application using this engine
 */
class Application {
public:
  /**
   * Constructor
   */
  Application(const char *title, int width = 640, int height = 480);

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

protected: // Functions implemented by subclasses
  /**
   * Called onUserce when the application begins running
   * @returns true if the application should continue running
   */
  virtual bool onUserCreate();
  /**
   * Called every frame
   * @returns true if the application should continue running
   */
  virtual bool onUserUpdate();
  /**
   * Called when the application is exitting
   */
  virtual void onUserDestroy();

private: // Member variables
  SDL2pp::SDL m_sdl;
  SDL2pp::Window m_win;
};

#endif
