#include <SDL.h>
#include <cstdlib>
#include <exception>

#include "blockbop.hpp"
#include "init.hpp"

int main(int argc, char *argv[]) {
  (void)argc, (void)argv;

  try {
    init_engine();
    Blockbop app;
    return app.run();
  } catch (const std::exception &e) {
    // Show the error to the user and exit
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", e.what());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Critical Error", e.what(),
                             nullptr);
    return EXIT_FAILURE;
  }
}
