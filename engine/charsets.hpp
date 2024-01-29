#ifndef BBENGINE_CHARSETS_HPP
#define BBENGINE_CHARSETS_HPP

#include <cstddef>

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

} // namespace charsets

#endif
