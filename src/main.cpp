#include <SDL.h>

#include <chrono>
#include <iostream>
#include <memory>

#include "engine.h"
#include "globals.h"
#include "util/system.h"
#include "window_handler.h"

#define SEC_NANO 1000000000.

using namespace comput;

inline std::chrono::high_resolution_clock::time_point now() {
  return std::chrono::high_resolution_clock::now();
}

// TODO: make all units in nanoseconds as default
int main(int argc, char **argv) {
  // obj
  auto system = ComputSystem::create();
  WindowHandler windowHandler;

  // system setup
  system->init();

  ComputEngine engine;
  engine.init();

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
  auto mainWindow = windowHandler.getWindow(mainWindowName);
  if (!mainWindow) {
    std::cerr << "Main window null.";
    return 1;
  }
  auto mainRenderer = windowHandler.getRenderer(mainWindowName);
  if (!mainRenderer) {
    std::cerr << "Main renderer null.";
    return 1;
  }

  SDL_RenderClear(mainRenderer);

  // main loop
  SDL_Event e;
  bool quit = false;
  auto last_update_time = now();
  while (!quit) {
    // events
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // update (every millisecond)
    auto since_last_update =  (now() - last_update_time).count();
    if (since_last_update > SEC_NANO / COMPUT_DT_LIMIT) {
      engine.update((now() - last_update_time).count());
      std::vector<Shape> dummyShapes;
      windowHandler.drawShapes(mainRenderer, dummyShapes);
      windowHandler.update(mainRenderer);

      // profiling
      auto frame_time = now() - last_update_time; // nanoseconds
      double fps = SEC_NANO / frame_time.count();
      std::cout << "fps: " << fps << std::endl;
      last_update_time = now();
    }
  }

  windowHandler.quit();
  system->quit();
  // TODO: segmentation fault at the end of the program in WSL... is that an
  // issue with wsl display server? check. backtrace on gdb points to wsl
  // libraries
  return 0;
}
