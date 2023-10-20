#include "globals.h"

#include <stdio.h>

void system_init()
{
  SDL_Init(COMPUT_SDL_INIT_LIST);
}

void system_quit()
{
  SDL_Quit();
}

int main(int argc, char **argv)
{
  system_init();

  printf("hhhhssssssssssssssssssss\n");

  system_quit();
  return 0;
}
