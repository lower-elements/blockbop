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

char32_t UTF8toUTF32(const char *utf8_char) {
  if (!utf8_char || (*utf8_char == '\0')) {
    // Invalid input
    return 0;
  }

  unsigned char first_byte = (unsigned char)utf8_char[0];

  // Determine the number of bytes in the UTF-8 sequence
  size_t num_bytes;
  if ((first_byte & 0x80) == 0x00) {
    num_bytes = 1;
  } else if ((first_byte & 0xE0) == 0xC0) {
    num_bytes = 2;
  } else if ((first_byte & 0xF0) == 0xE0) {
    num_bytes = 3;
  } else if ((first_byte & 0xF8) == 0xF0) {
    num_bytes = 4;
  } else {
    // Invalid UTF-8 sequence
    return 0;
  }

  char32_t codepoint = (unsigned char)utf8_char[0];

  // Extract the remaining bytes of the UTF-8 sequence
  for (size_t i = 1; i < num_bytes; ++i) {
    if ((utf8_char[i] & 0xC0) != 0x80) {
      // Invalid continuation byte
      return 0;
    }
    codepoint = (codepoint << 6) | (utf8_char[i] & 0x3F);
  }

  return codepoint;
}

std::size_t UTF32toUTF16(char32_t codepoint, char16_t utf16[2]) {
  if (codepoint < 0x10000) {
    // Single code unit (BMP)
    utf16[0] = (char16_t)codepoint;
    utf16[1] = 0; // Second unit is not used
    return 1;
  } else if (codepoint <= 0x10FFFF) {
    // Surrogate pair for code points outside BMP
    utf16[0] = (char16_t)(((codepoint - 0x10000) >> 10) + 0xD800);
    utf16[1] = (char16_t)(((codepoint - 0x10000) & 0x3FF) + 0xDC00);
    return 2;
  } else {
    // Invalid code point
    utf16[0] = utf16[1] = 0;
    return 0;
  }
}
