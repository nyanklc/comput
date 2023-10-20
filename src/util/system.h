#ifndef COMPUT_UTIL_SYSTEM_H
#define COMPUT_UTIL_SYSTEM_H

#include "../globals.h"

#include <memory>

#include <SDL.h>

class ComputSystem
{
public:
  ComputSystem() {}

  static std::unique_ptr<ComputSystem> create()
  {
    return std::unique_ptr<ComputSystem>(new ComputSystem());
  }

  void init()
  {
    SDL_Init(COMPUT_SDL_INIT_LIST);
  }

  void quit()
  {
    SDL_Quit(); 
  }
};

#endif