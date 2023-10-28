#include <SDL.h>

#include <iostream>
#include <memory>

#include "util/system.h"
#include "window_handler.h"

using namespace comput;

// int main(int argc, char **argv) {
 //  // obj
 //  auto system = ComputSystem::create();
 //  WindowHandler windowHandler;

 //  // system setup
 //  system->init();

 //  // window setup
 //  std::string mainWindowName = "noyan";
 //  if (!windowHandler.createWindow(mainWindowName)) {
 //    std::cerr << "Could not create window.";
 //    return 1;
 //  }
 //  if (!windowHandler.setRenderer(mainWindowName)) {
 //    std::cerr << "Could not create renderer.";
 //    return 1;
 //  }
 //  auto mainWindow = windowHandler.getWindow(mainWindowName);
 //  if (!mainWindow) {
 //    std::cerr << "Main window null.";
 //    return 1;
 //  }
 //  auto mainRenderer = windowHandler.getRenderer(mainWindowName);
 //  if (!mainRenderer) {
 //    std::cerr << "Main renderer null.";
 //    return 1;
 //  }

 //  // main loop
 //  SDL_Event e;
 //  bool quit = false;
 //  while (!quit) {
 //    // profiling
 //    auto start_time = SDL_GetTicks();

 //    // events
 //    while (SDL_PollEvent(&e)) {
 //      if (e.type == SDL_QUIT) {
 //        quit = true;
 //      }
 //    }

 //    // TODO: update (also update rendered screen in the engine update)
 //    // draw/update
 //    std::vector<Shape> dummyShapes;
 //    windowHandler.drawShapes(mainRenderer, dummyShapes);
 //    windowHandler.clear(mainRenderer);
 //    windowHandler.update(mainRenderer);

 //    // profiling
 //    auto frame_time = SDL_GetTicks() - start_time;
 //    auto fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
 //    std::cout << "fps: " << fps << std::endl;
 //  }

 //  windowHandler.quit();
 //  system->quit();
 //  // TODO: segmentation fault at the end of the program in WSL... is that an
 //  // issue with wsl display server? check. backtrace on gdb points to wsl
 //  // libraries
 //  return 0;
// }

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Handle initialization error
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Rectangle Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        // Handle window creation error
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        // Handle renderer creation error
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color

    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 200;
    rect.h = 150;

    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
