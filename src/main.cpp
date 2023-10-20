#include "util/system.h"

#include <iostream>
#include <memory>

#include <SDL.h>


int main(int argc, char **argv)
{
  auto system = ComputSystem::create();
  system->init();

  SDL_Window* window = SDL_CreateWindow("comput", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  if (window == NULL) {
      printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
      return 1;
  }
  SDL_SetWindowResizable(window, SDL_TRUE);

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
      printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
      return 1;
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  SDL_Event e;
  bool quit = false;
  while (!quit)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  system->quit();
  return 0;
}
