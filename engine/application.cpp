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

  // Main loop
  do {
    // update the global application
    m_continue_running = onUserUpdate();
    // Update all states
    m_continue_running |= m_states.onUpdate();
  } while (m_continue_running);

  return EXIT_SUCCESS;
}

bool Application::onUserCreate() { return true; }
bool Application::onUserUpdate() { return true; }
void Application::onUserDestroy() {}
