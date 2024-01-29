#include <exception>

#include <SDL.h>
#include <fmt/core.h>

#include "charsets.hpp"

namespace charsets {

Iconv::Iconv(const char *tocode, const char *fromcode)
    : m_cd(SDL_iconv_open(tocode, fromcode)) {
  if (m_cd == nullptr) {
    throw std::runtime_error(
        fmt::format("Could not create Iconv handle: {}", SDL_GetError()));
  }
}

Iconv::~Iconv() {
  if (m_cd && SDL_iconv_close(m_cd) < 0) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                "Could not close Iconv handle: %s", SDL_GetError());
  }
}

std::size_t Iconv::convert(const char *&inbuf, size_t &inbytesleft,
                           char *&outbuf, size_t &outbytesleft) {
  return SDL_iconv(m_cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
}

std::size_t Iconv::convert(const std::string &input, std::string &output) {
  std::size_t inbytesleft = input.size();
  const char *inbuf = input.data();

  std::size_t outbytesleft = inbytesleft * 4; // Reasonable estimate
  output.reserve(outbytesleft);
  char *outbuf = output.data();

  std::size_t total_converted = 0;
  while (true) {
    auto converted = convert(inbuf, inbytesleft, outbuf, outbytesleft);
    if (converted >= SDL_ICONV_EINVAL) {
      return converted; // Error condition
    }
    total_converted += converted;
    if (inbytesleft == 0) {
      break; // Done conversion
    } else {
      // Allocate more space
      auto extra_space = inbytesleft * 4; // Reasonable guess
      output.reserve(output.capacity() + extra_space);
      outbytesleft += extra_space;
    }
  }

  output.resize(output.capacity() - outbytesleft);
  return total_converted;
}

} // namespace charsets
