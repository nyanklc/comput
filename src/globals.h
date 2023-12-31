#ifndef COMPUT_GLOBALS_H
#define COMPUT_GLOBALS_H

#include <Eigen/Dense>
#include <SDL.h>

namespace comput
{

#define COMPUT_SDL_INIT_LIST \
    SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS

#define COMPUT_SIMULATION_TIMESTEP 0.01
#define COMPUT_APPLICATION_FPS 144

#define COMPUT_WINDOW_DEFAULT_W 640
#define COMPUT_WINDOW_DEFAULT_H 480
#define COMPUT_WINDOW_DEFAULT_FLAGS 0

#define COMPUT_RENDERER_DEFAULT_INDEX 1
#define COMPUT_RENDERER_DEFAULT_FLAGS 0

#define COMPUT_GRAVITY_CONSTANT 9.80665

#ifdef COMPUT_DEBUG
#define COMPUT_DEBUG_SEPARATOR \
    std::cout << "#########################" << std::endl
#endif

} // namespace comput

#endif
