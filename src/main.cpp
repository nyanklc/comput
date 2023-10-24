#include "util/system.h"
#include "window_handler.h"

#include <iostream>
#include <memory>

#include <SDL.h>

using namespace comput;

int main(int argc, char **argv) {
  auto system = ComputSystem::create();
  WindowHandler windowHandler;
  system->init();

  if (!windowHandler.createWindow("noyan"))
    return 1;
  if (!windowHandler.setRenderer("noyan"))
    return 1;

  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  windowHandler.quit();
  system->quit();
  // TODO: segmentation fault at the end of the program in WSL... is that an issue with wsl display server? check.
  // backtrace on gdb points to wsl libraries
  return 0;
}
