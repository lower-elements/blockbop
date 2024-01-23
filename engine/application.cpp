#include <SDL.h>
#include <cstdlib>

#include "application.hpp"
#include "tts/espeak_ng.hpp"
#include "util.hpp"

Application::Application(const char *org_name, const char *app_name, int width,
                         int height)
    : m_sdl(SDL_INIT_VIDEO),
      m_win(app_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
            height, SDL_WINDOW_HIDDEN),
      m_audio(), m_speaker(std::make_unique<tts::EspeakNgSpeaker>()),
      m_states(), m_pref_path(SDL_GetPrefPath(org_name, app_name), SDL_free),
      m_continue_running(true) {
  setSDLLogPriority();
}

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
      // Is the AudioManager interested?
      if (m_audio.onEvent(ev)) {
        continue;
      }
      // Is the Application interested?
      if (onUserEvent(ev)) {
        continue;
      }
      // Forward to states
      m_states.onEvent(ev);
    }

    // update the global application
    continue_running = onUserUpdate();
    // Update all states
    continue_running |= m_states.onUpdate();
  } while (continue_running && m_continue_running);

  return EXIT_SUCCESS;
}

bool Application::onUserEvent(SDL_Event &ev) {
  switch (ev.type) {
  case SDL_QUIT:
    // By default we quit if we receive SDL_QUIT
    quit();
    return true;
  case SDL_APP_WILLENTERBACKGROUND:
    goto pause_audio;
  case SDL_APP_DIDENTERFOREGROUND:
    goto resume_audio;
  case SDL_WINDOWEVENT:
    switch (ev.window.event) {
    case SDL_WINDOWEVENT_FOCUS_LOST:
      goto pause_audio;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
      goto resume_audio;
    default:
      return false;
    }
  default:
    return false;
  }

pause_audio:
  // Pause audio if possible
  if (m_audio.m_pause_device.isSupported()) {
    m_audio.m_pause_device.pause();
  }
  return false; // Allow other handlers to process this

resume_audio:
  // Resume audio if possible
  if (m_audio.m_pause_device.isSupported()) {
    m_audio.m_pause_device.resume();
  }
  return false; // Allow other handlers to process this
}

bool Application::onUserCreate() { return true; }
bool Application::onUserUpdate() { return true; }
void Application::onUserDestroy() {}
