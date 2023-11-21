#include <SDL.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>
#include <random>

#include "engine.h"
#include "globals.h"
#include "util/collision_system/axis_aligned.h"
#include "util/collision_system/separating_axis.h"
#include "util/mass.h"
#include "util/system.h"
#include "window_handler.h"

#define SEC_NANO 1000000000.

using namespace comput;

inline std::chrono::high_resolution_clock::time_point now()
{
    return std::chrono::high_resolution_clock::now();
}

inline bool hasBeenSeconds(double seconds, std::chrono::high_resolution_clock::time_point since)
{
    return (now() - since).count() >= SEC_NANO * seconds;
}

#ifdef _WIN32
#include <Windows.h>
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    return main(__argc, __argv);
}
#endif

// TODO: make all units in nanoseconds as default
int main(int argc, char **argv)
{
    // obj
    ComputEngine engine;
    engine.setCollisionSystem(new CollisionSystemAxisAligned());
    auto system = ComputSystem::create();
    WindowHandler windowHandler;

    // system setup
    system->init();

    // window setup
    std::string mainWindowName = "noyan";
    if (!windowHandler.createWindow(mainWindowName))
    {
        std::cerr << "Could not create window.";
        return 1;
    }
    if (!windowHandler.setRenderer(mainWindowName))
    {
        std::cerr << "Could not create renderer.";
        return 1;
    }
    auto mainWindow = windowHandler.getWindow(mainWindowName);
    if (!mainWindow)
    {
        std::cerr << "Main window null.";
        return 1;
    }
    auto mainRenderer = windowHandler.getRenderer(mainWindowName);
    if (!mainRenderer)
    {
        std::cerr << "Main renderer null.";
        return 1;
    }

    SDL_RenderClear(mainRenderer);

    // engine setup
    SDL_Color objColor = {255, 0, 255, 255};
    SDL_Color objColor2 = {0, 255, 0, 255};
    SDL_Color objColor3 = { 0, 255, 255, 255 };
    Object obj("obj1", false, 0, 0, 30, 30, objColor, Velocity{ Eigen::Vector2f(50, 0) }, 1);
    Object obj2("obj2", false, 100, 100, 20, 20, objColor2, Velocity{Eigen::Vector2f(20, -30)}, 10);
    Object obj_ground("obj_ground", true, 0, 150, COMPUT_WINDOW_DEFAULT_W, 20, objColor3, Velocity::zero(), Mass::maxMass());
    obj.getPropertiesInteraction().repulsionForceMagnitude = 1000;
    obj2.getPropertiesInteraction().repulsionForceMagnitude = 1000;
    obj_ground.getPropertiesInteraction().repulsionForceMagnitude = 1000;
    engine.createObject(obj);
    engine.createObject(obj2);
    engine.createObject(obj_ground);

    // main loop
    SDL_Event e;
    bool quit = false;
    auto lastUpdateTime = now();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    while (!quit)
    {
        // TODO: handling window resize is blocking currently, no other operations
        // are completed (engine update etc.) events
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // TODO: research on actual simulation implementation,
        // we should be able to decouple simulation timestep and other things
        // update
        if (hasBeenSeconds(1.0 / COMPUT_APPLICATION_FPS, lastUpdateTime))
        {
            auto &engineObjects = engine.getObjects();
            auto dt = COMPUT_SIMULATION_TIMESTEP;
            engine.applyGravity(dt);
            engine.update(dt);

            // TODO: this is not working
            engine.debugCollisionInteractions(mainRenderer);

            windowHandler.drawObjects(mainRenderer, engineObjects);
            windowHandler.update(mainRenderer);

            // profiling
            auto frame_time = now() - lastUpdateTime; // nanoseconds
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
