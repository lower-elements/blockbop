#include <SDL.h>
#include <cstdlib>
#include <exception>

#include "application.hpp"

int main() {
  try {
    Application app("BlockBop");
    return app.run();
  } catch (const std::exception &e) {
    // Show the error to the user and exit
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", e.what());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Critical Error", e.what(),
                             nullptr);
    return EXIT_FAILURE;
  }
}
