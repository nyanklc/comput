#include <SDL.h>

#include <iostream>
#include <memory>

#include "util/system.h"
#include "window_handler.h"

using namespace comput;

int main(int argc, char **argv) {
  // obj
  auto system = ComputSystem::create();
  WindowHandler windowHandler;

  // system setup
  system->init();

  // window setup
  std::string mainWindowName = "noyan";
  if (!windowHandler.createWindow(mainWindowName)) {
    std::cerr << "Could not create window.";
    return 1;
  }
  if (!windowHandler.setRenderer(mainWindowName)) {
    std::cerr << "Could not create renderer.";
    return 1;
  }
  auto mainWindow = windowHandler.getWinRen(mainWindowName).first;
  if (!mainWindow) {
    std::cerr << "Main window null.";
    return 1;
  }
  auto mainRenderer = windowHandler.getWinRen(mainWindowName).second;
  if (!mainRenderer) {
    std::cerr << "Main renderer null.";
    return 1;
  }

  // main loop
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    // profiling
    auto start_time = SDL_GetTicks();

    // events
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // TODO: update (also update rendered screen in the engine update)
    windowHandler.drawShapes(mainWindowName);

    // draw
    windowHandler.clear(mainWindowName);
    windowHandler.update(mainWindowName);

    // profiling
    auto frame_time = SDL_GetTicks() - start_time;
    auto fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
    std::cout << "fps: " << fps << std::endl;
  }

  windowHandler.quit();
  system->quit();
  // TODO: segmentation fault at the end of the program in WSL... is that an
  // issue with wsl display server? check. backtrace on gdb points to wsl
  // libraries
  return 0;
}
