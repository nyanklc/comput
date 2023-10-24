#ifndef COMPUT_WINDOW_HANDLER_H
#define COMPUT_WINDOW_HANDLER_H

#include "globals.h"

#include <string>
#include <vector>

#include <SDL.h>

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
        if (w)
          SDL_DestroyWindow(w);
        if (r)
          SDL_DestroyRenderer(r);
      }
      _windows.clear();
    }

    bool createWindow(
          std::string &title,
          int x = SDL_WINDOWPOS_CENTERED,
          int y = SDL_WINDOWPOS_CENTERED,
          int w = COMPUT_WINDOW_DEFAULT_W,
          int h = COMPUT_WINDOW_DEFAULT_H,
          Uint32 flags = COMPUT_WINDOW_DEFAULT_FLAGS,
          bool resizable = true
          ) {
      auto window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
      if (!window)
      {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
      }
      if (resizable)
        SDL_SetWindowResizable(window, SDL_TRUE);
      SDL_Renderer *r = 0;
      _windows.push_back(std::pair(window, r));
      return true;
    }

    bool setRenderer(std::string &title, int index = COMPUT_RENDERER_DEFAULT_INDEX, Uint32 flags = COMPUT_RENDERER_DEFAULT_FLAGS) {
      auto winren_i = _findWindow(title);
      auto &winren = _windows[winren_i];
      if (!winren.first) // window doesn't exist
        return false;
      if (winren.second) // window already has a renderer
        return false;
      winren.second = SDL_CreateRenderer(winren.first, index, flags);
      if (!winren.second)
        return false;
      return true;
    }

    bool resizeWindow(std::string &title, int newW, int newH) {
      auto winren_i = _findWindow(title);
      auto winren = _windows[winren_i];
      if (!winren.first)
        return false;
      SDL_SetWindowSize(winren.first, newW, newH);            
      return true;
    }

    void clear(std::string &title) {
      auto winren_i = _findWindow(title);
      auto winren = _windows[winren_i];
      if (!winren.first) return;
      SDL_RenderClear( winren.second );
    }

    void update(std::string &title) {
      auto winren_i = _findWindow(title);
      auto winren = _windows[winren_i];
      if (!winren.first) return;
      SDL_UpdateWindowSurface( winren.first );
    }

    window_renderer_t &getWinRen(std::string &title) {
      auto winren_i = _findWindow(title);
      return _windows[winren_i];
    }

#ifdef COMPUT_DEBUG
    void print() {
      std::cout << std::endl << "Printing window-renderer pairs.\n";
      for (auto &it : _windows)
      {
        if (it.first)
        {
          std::cout << "Window ptr " << it.first << ", title " << SDL_GetWindowTitle(it.first) << std::endl;
          std::cout << "Renderer ptr " << it.second << ", title " << SDL_GetWindowTitle(it.first) << std::endl << std::endl;
        }
      }
      std::cout << std::endl;
    }

    void printWinRen(std::pair<SDL_Window *, SDL_Renderer *> &winren) {
      std::cout << "winren: " << winren.first << ", " << winren.second << ", title " << SDL_GetWindowTitle(winren.first) << std::endl;
    }
#endif

  private:
    // We'll allow windows without a renderer, but not the other way around.
    std::vector<window_renderer_t> _windows;
    window_renderer_t _noWinRen;

    // This is a very inefficient way of handling things, but there won't be many windows in the application so it shouldn't be a problem.
    size_t _findWindow(std::string &title) {
      for (size_t i = 0; i < _windows.size(); i++)
      {
        std::string t = SDL_GetWindowTitle(_windows[i].first);
        // TODO: using t.c_str() == title.c_str() fails
        if (t == title)
        {
          return i;
        }
      }
      return -1;
    }

  };

} // namespace comput

#endif
