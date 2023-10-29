// TODO: carry method implementations to source file
#ifndef COMPUT_WINDOW_HANDLER_H
#define COMPUT_WINDOW_HANDLER_H

#include <SDL.h>

#include <SDL_render.h>
#include <string>
#include <vector>

#include "globals.h"
#include "object.h"

#ifdef COMPUT_DEBUG
#include <iostream>
#endif

namespace comput {

/**
 * Class that holds window-renderer pairs.
 */
class WindowHandler {
  typedef std::pair<SDL_Window *, SDL_Renderer *> window_renderer_t;

 public:
  WindowHandler() {
    _windows.clear();
    _noWinRen = window_renderer_t(0, 0);
  }

  ~WindowHandler() {
    // just in case
    quit();
  }

  void quit() {
    for (auto &it : _windows) {
      auto w = (it).first;
      auto r = (it).second;
      if (w) SDL_DestroyWindow(w);
      if (r) SDL_DestroyRenderer(r);
    }
    _windows.clear();
  }

  void update(SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
  }

  // TODO:
  // This only draws on SDL backbuffer. Call update() to actually draw things.
  void drawShapes(SDL_Renderer *renderer, std::vector<Shape> &shapes);

  bool createWindow(std::string &title, int x = SDL_WINDOWPOS_CENTERED,
                    int y = SDL_WINDOWPOS_CENTERED,
                    int w = COMPUT_WINDOW_DEFAULT_W,
                    int h = COMPUT_WINDOW_DEFAULT_H,
                    Uint32 flags = COMPUT_WINDOW_DEFAULT_FLAGS,
                    bool resizable = true) {
    auto window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (!window) {
      printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
      return false;
    }
    if (resizable) SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_Renderer *r = 0;
    _windows.push_back(std::pair(window, r));
    return true;
  }

  bool setRenderer(std::string &title,
                   int index = COMPUT_RENDERER_DEFAULT_INDEX,
                   Uint32 flags = COMPUT_RENDERER_DEFAULT_FLAGS) {
    auto winren_i = _findWinRen(title);
    auto &winren = _windows[winren_i];
    if (!winren.first)  // window doesn't exist
      return false;
    if (winren.second)  // window already has a renderer
      return false;
    winren.second = SDL_CreateRenderer(winren.first, index, flags);
    if (!winren.second) return false;
    return true;
  }

  bool resizeWindow(std::string &title, int newW, int newH) {
    auto winren_i = _findWinRen(title);
    auto winren = _windows[winren_i];
    if (!winren.first) return false;
    SDL_SetWindowSize(winren.first, newW, newH);
    return true;
  }


  window_renderer_t &getWinRen(std::string &title) {
    auto winren_i = _findWinRen(title);
    return _windows[winren_i];
  }

  SDL_Window *getWindow(std::string &title) {
    return _findWindow(title);
  }

  SDL_Renderer *getRenderer(std::string &title) {
    return _findRenderer(title);
  }

#ifdef COMPUT_DEBUG
  void print() {
    std::cout << std::endl << "Printing window-renderer pairs.\n";
    for (auto &it : _windows) {
      if (it.first) {
        std::cout << "Window ptr " << it.first << ", title "
                  << SDL_GetWindowTitle(it.first) << std::endl;
        std::cout << "Renderer ptr " << it.second << ", title "
                  << SDL_GetWindowTitle(it.first) << std::endl
                  << std::endl;
      }
    }
    std::cout << std::endl;
  }

  void printWinRen(std::pair<SDL_Window *, SDL_Renderer *> &winren) {
    std::cout << "winren: " << winren.first << ", " << winren.second
              << ", title " << SDL_GetWindowTitle(winren.first) << std::endl;
  }
#endif

 private:
  // We'll allow windows without a renderer, but not the other way around.
  std::vector<window_renderer_t> _windows;
  window_renderer_t _noWinRen;

  SDL_Window *_findWindow(std::string &title) {
    auto index = _findWinRen(title);
    if (index == -1)
      return 0;
    return _windows[index].first;
  }

  SDL_Renderer *_findRenderer(std::string &title) {
    auto index = _findWinRen(title);
    if (index == -1)
      return 0;
    return _windows[index].second;
  }

  // void _drawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY,
  //                  int32_t radius) {
  //   const int32_t diameter = (radius * 2);
  //   int32_t x = (radius - 1);
  //   int32_t y = 0;
  //   int32_t tx = 1;
  //   int32_t ty = 1;
  //   int32_t error = (tx - diameter);
  //   while (x >= y) {
  //     //  Each of the following renders an octant of the circle
  //     SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
  //     SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
  //     SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
  //     SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
  //     SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
  //     SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
  //     SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
  //     SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
  //     if (error <= 0) {
  //       ++y;
  //       error += ty;
  //       ty += 2;
  //     }
  //     if (error > 0) {
  //       --x;
  //       tx += 2;
  //       error += (tx - diameter);
  //     }
  //   }
  // }

  void _setColor(SDL_Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
  }

  void _drawRect(SDL_Renderer *renderer, SDL_Rect &rect, Color &before, Color &after);

  // This is a very inefficient way of handling things, but there won't be
  // many windows in the application so it shouldn't be a problem.
  // Returns index to be used in _windows container.
  int _findWinRen(std::string &title) {
    for (size_t i = 0; i < _windows.size(); i++) {
      std::string t = SDL_GetWindowTitle(_windows[i].first);
      // TODO: using t.c_str() == title.c_str() fails
      if (t == title) {
        return i;
      }
    }
    return -1;
  }
};

}  // namespace comput

#endif
