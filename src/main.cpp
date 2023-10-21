#include "util/system.h"
#include "window_handler.h"

#include <iostream>
#include <memory>

#include <SDL.h>

using namespace comput;

int main(int argc, char **argv)
{
  auto system = ComputSystem::create();
  system->init();

  WindowHandler windowHandler;

  if (!windowHandler.createWindow("noyan"))
    return 1;
  if (!windowHandler.createWindow("asd"))
    return 1;
  if (!windowHandler.setRenderer("asd"))
    return 1;


#ifdef COMPUT_DEBUG
  windowHandler.print();
#endif

  // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  // SDL_RenderClear(renderer);
  // SDL_RenderPresent(renderer);

  // SDL_Event e;
  // bool quit = false;
  // while (!quit)
  // {
  //   while (SDL_PollEvent(&e))
  //   {
  //     if (e.type == SDL_QUIT)
  //     {
  //       quit = true;
  //     }
  //   }
  // }

  // SDL_DestroyRenderer(renderer);
  // SDL_DestroyWindow(window);
  //
  int input;
  std::cin >> input;

  windowHandler.resizeWindow("noyan", 200, 200);

  std::cin >> input;

  system->quit();
  return 0;
}
