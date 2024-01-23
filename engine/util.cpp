#include <SDL.h>

#include "util.hpp"

static const char *const LOG_PRIORITIES[]{"verbose", "debug", "info",
                                          "warn",    "error", "critical"};

void setSDLLogPriority() {
  const char *log_env = SDL_getenv("BLOCKBOP_LOG");

  if (log_env) {
    for (unsigned i = 0; i < SDL_arraysize(LOG_PRIORITIES); ++i) {
      if (SDL_strcasecmp(log_env, LOG_PRIORITIES[i]) == 0) {
        SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION,
                           (SDL_LogPriority)(i + 1));
        return;
      }
    }
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                "Unknown value for BLOCKBOP_LOG: '%s'", log_env);
  }
}
