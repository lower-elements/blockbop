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

std::size_t nextUTF8Character(const std::string &utf8_str,
                              std::size_t current_position) {
  std::size_t size = utf8_str.size();

  if (current_position >= size) {
    // Position is at or beyond the end of the string
    return std::string::npos;
  }

  // Move to the next character
  for (std::size_t i = current_position + 1; i < size; ++i) {
    if ((utf8_str[i] & 0xC0) != 0x80) {
      // Found the start of the next UTF-8 character
      return i;
    }
  }

  // No next character found
  return std::string::npos;
}

std::size_t prevUTF8Character(const std::string &utf8_str,
                              std::size_t current_position) {
  if (current_position == 0 || current_position == std::string::npos) {
    // Position is at the beginning or the string is empty
    return std::string::npos;
  }

  // Move to the previous character
  for (std::size_t i = current_position - 1; i != std::string::npos; --i) {
    if ((utf8_str[i] & 0xC0) != 0x80) {
      // Found the start of the previous UTF-8 character
      return i;
    }
  }

  // No previous character found
  return std::string::npos;
}
