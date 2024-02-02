#ifndef BBENGINE_CHARSETS_HPP
#define BBENGINE_CHARSETS_HPP

#include <cstddef>

#include <memory>
#include <string_view>

#include <SDL_stdinc.h>

namespace charsets {

class Iconv {
public: // Member methods
  Iconv(const char *tocode, const char *fromcode);
  ~Iconv();

  std::size_t convert(const char *&inbuf, size_t &inbytesleft, char *&outbuf,
                      size_t &outbytesleft);

  std::size_t convert(const std::string &input, std::string &output);

private: // Member variables
  SDL_iconv_t m_cd;
};

template <class T = char>
std::unique_ptr<T[], void (*)(void *)>
convert(const char *tocode, const char *fromcode, const char *buf,
        std::size_t size) {
  T *str = (T *)SDL_iconv_string(tocode, fromcode, buf, size);
  return {str, SDL_free};
}

template <class T = char>
std::unique_ptr<T[], void (*)(void *)>
convert(const char *tocode, const char *fromcode, std::string_view text) {
  return convert<T>(tocode, fromcode, text.data(), text.size());
}

template <class T = char>
std::unique_ptr<T[], void (*)(void *)>
convert(const char *tocode, const char *fromcode, const std::string &text) {
  return convert<T>(tocode, fromcode, text.data(), text.size());
}

} // namespace charsets

#endif
