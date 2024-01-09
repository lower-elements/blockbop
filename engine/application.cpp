#include <SDL.h>
#include <cstdlib>

#include "application.hpp"
#include "tts/espeak_ng.hpp"

Application::Application(const char *title, int width, int height)
    : m_sdl(SDL_INIT_VIDEO),
      m_win(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
            height, SDL_WINDOW_HIDDEN),
      m_speaker(std::make_unique<tts::EspeakNgSpeaker>()) {}

Application::~Application() { onUserDestroy(); }

int Application::run() {
  m_win.Show();
  if (!onUserCreate()) {
    return EXIT_FAILURE; // Abort
  }
  while (onUserUpdate()) {
  }
  return EXIT_SUCCESS;
}

bool Application::onUserCreate() { return true; }
bool Application::onUserUpdate() { return true; }
void Application::onUserDestroy() {}
