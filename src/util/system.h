#ifndef COMPUT_UTIL_SYSTEM_H
#define COMPUT_UTIL_SYSTEM_H

#include <SDL.h>

#include <memory>

#include "../globals.h"

namespace comput
{

    class ComputSystem
    {
    public:
        ComputSystem() {}

        // TODO: is it okay to call quit twice?
        // ~ComputSystem() {
        //   quit();
        // }

        static std::unique_ptr<ComputSystem> create()
        {
            return std::unique_ptr<ComputSystem>(new ComputSystem());
        }

        void init() { SDL_Init(COMPUT_SDL_INIT_LIST); }

        void quit() { SDL_Quit(); }
    };

} // namespace comput

#endif
