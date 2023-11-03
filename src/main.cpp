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
  ComputEngine engine;
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

  // engine setup
  // TODO:
  SDL_Color objColor;
  objColor.r = 255;
  objColor.g = 0;
  objColor.b = 255;
  objColor.a = 255;
  Object obj(0, 0, 30, 30, objColor, Velocity::zero(), 1);
  Object obj2(100, 100, 20, 20, objColor, Velocity::zero(), 10);
  engine.createObject(obj);
  engine.createObject(obj2);

  // main loop
  SDL_Event e;
  bool quit = false;
  auto lastUpdateTime = now();
  while (!quit) {
    // TODO: handling window resize is blocking currently, no other operations
    // are completed (engine update etc.) events
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // TODO: research on actual simulation implementation,
    // we should be able to decouple simulation timestep and other things
    // update
    auto sinceLastUpdate = (now() - lastUpdateTime).count();
    if (sinceLastUpdate > SEC_NANO * COMPUT_SIMULATION_DEFAULT_TIMESTEP) {
      auto engineObjects = engine.getObjects();
      auto dt = (now() - lastUpdateTime).count() / SEC_NANO;
      std::cout << "dt: " << dt << std::endl;
      engine.applyGravity();
      engine.update(dt);

      windowHandler.drawObjects(mainRenderer, engineObjects);
      windowHandler.update(mainRenderer);

      // profiling
      auto frame_time = now() - lastUpdateTime;  // nanoseconds
      double fps = SEC_NANO / frame_time.count();
      std::cout << "simulation fps: " << fps << std::endl;
      lastUpdateTime = now();
    }
  }

  windowHandler.quit();
  system->quit();
  // TODO: segmentation fault at the end of the program in WSL... is that an
  // issue with wsl display server? check. backtrace on gdb points to wsl
  // libraries
  return 0;
}
