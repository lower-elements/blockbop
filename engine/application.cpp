#include <SDL.h>
#include <cstdlib>

#include "application.hpp"
#include "tts/espeak_ng.hpp"

Application::Application(const char *title, int width, int height)
    : m_sdl(SDL_INIT_VIDEO),
      m_win(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
            height, SDL_WINDOW_HIDDEN),
      m_speaker(std::make_unique<tts::EspeakNgSpeaker>()), m_states(),
      m_continue_running(true) {}

Application::~Application() { onUserDestroy(); }

int Application::run() {
  m_win.Show();

  // Tell the application to initialise
  if (!onUserCreate()) {
    return EXIT_FAILURE; // Abort
  }

  // This variable handles internal engine quit conditions, the member variable
  // handles explicit requests to quit via the quit() method
  bool continue_running = true;
  // Main loop
  do {
    // Process events
    for (SDL_Event ev; SDL_PollEvent(&ev);) {
      onUserEvent(ev);
    }

    // update the global application
    continue_running = onUserUpdate();
    // Update all states
    continue_running |= m_states.onUpdate();
  } while (continue_running && m_continue_running);

  return EXIT_SUCCESS;
}

bool Application::onUserEvent(SDL_Event &ev) {
  // By default we quit if we receive SDL_QUIT
  if (ev.type == SDL_QUIT) {
    quit();
    return true;
  }
  return false;
}

bool Application::onUserCreate() { return true; }
bool Application::onUserUpdate() { return true; }
void Application::onUserDestroy() {}
