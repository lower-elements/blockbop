#include <SDL.h>
#include <SDL_opengles2.h>

#include "util.hpp"

void init_engine() {
  setSDLLogPriority();

  // Require OpenGL ES 3.0
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  // Set hints
  // Force usage of the GLES backend
  SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
  // Want double-buffering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // Todo: Support IMEs properly
  SDL_SetHint(SDL_HINT_IME_INTERNAL_EDITING, "1");
  SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#ifdef SDL_HINT_IME_SUPPORT_EXTENDED_TEXT
  SDL_SetHint(SDL_HINT_IME_SUPPORT_EXTENDED_TEXT, "1");
#endif

  SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
}
