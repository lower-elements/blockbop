#ifndef BBENGINE_LIBRARY_HPP
#define BBENGINE_LIBRARY_HPP

#include <SDL_loadso.h>

class Library {
public: // Member methods
  Library(const char *name);
  virtual ~Library();

  template <class T> void getSymbol(const char *name, T *&val) const {
    val = (T *)(SDL_LoadFunction(m_lib, name));
  }

private: // Member variables
  void *m_lib;
};

#endif
