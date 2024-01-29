#include <exception>

#include <fmt/core.h>

#include "library.hpp"

Library::Library(const char *name) : m_lib(SDL_LoadObject(name)) {
  if (m_lib == nullptr) {
    throw std::runtime_error(
        fmt::format("Could not load \"{}\": {}", name, SDL_GetError()));
  }
}

Library::~Library() {
  if (m_lib) {
    SDL_UnloadObject(m_lib);
  }
}
