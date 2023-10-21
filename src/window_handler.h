#ifndef COMPUT_WINDOW_HANDLER_H
#define COMPUT_WINDOW_HANDLER_H

#include "globals.h"

#include <string>
#include <vector>

#include <SDL.h>

#ifdef COMPUT_DEBUG
#include <iostream>
#endif

namespace comput
{

  /**
   * Class that holds window-renderer pairs.
   */
  class WindowHandler
  {
  public:
    WindowHandler()
    {
      _windows.clear();
    }

    ~WindowHandler()
    {
      for (auto &it : _windows)
      {
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
          std::string title,
          int x = SDL_WINDOWPOS_CENTERED,
          int y = SDL_WINDOWPOS_CENTERED,
          int w = COMPUT_WINDOW_DEFAULT_W,
          int h = COMPUT_WINDOW_DEFAULT_H,
          Uint32 flags = COMPUT_WINDOW_DEFAULT_FLAGS,
          bool resizable = true
          )
    {
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

    bool setRenderer(std::string title, int index = COMPUT_RENDERER_DEFAULT_INDEX, Uint32 flags = COMPUT_RENDERER_DEFAULT_FLAGS)
    {
      auto winren = _findWindow(title);
      if (!winren.first) // window doesn't exist
        return false;
      winren.second = SDL_CreateRenderer(winren.first, index, flags);
      return true;
    }

    // TODO: doesn't work?
    bool resizeWindow(std::string title, int newW, int newH)
    {
      auto winren = _findWindow(title);
      if (!winren.first)
        return false;
    
      SDL_SetWindowSize(winren.first, newW, newH);            
      return true;
    }

#ifdef COMPUT_DEBUG
    void print()
    {
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
#endif

  private:
    typedef std::pair<SDL_Window *, SDL_Renderer *> window_renderer_t;
    // We'll allow windows without a renderer, but not the other way around.
    std::vector<window_renderer_t> _windows;

    // This is a very inefficient way of handling things, but there won't be many windows in the application so it shouldn't be a problem.
    std::pair<SDL_Window *, SDL_Renderer *>_findWindow(std::string &title)
    {
#ifdef COMPUT_DEBUG
      std::cout << "_findWindow called with title " << title << std::endl;
#endif
      SDL_Window *w = 0;
      SDL_Renderer *r = 0;
      for (auto &it : _windows)
      {
        std::string t = SDL_GetWindowTitle((it).first);
#ifdef COMPUT_DEBUG
        std::cout << "_findWindow title " << title << std::endl;
        std::cout << "_findWindow t " << t << std::endl;
#endif
        // TODO: using t.c_str() == title.c_str() fails
        if (t == title)
        {
#ifdef COMPUT_DEBUG
          std::cout << "_findWindow setting w " << it.first << ", r " << it.second << std::endl;
#endif
          w = it.first;
          r = it.second;
          break;
        }
      }
#ifdef COMPUT_DEBUG
      std::cout << "_findWindow returning <" << w << ", " << r << ">" << std::endl;
#endif
      return std::pair(w, r);
    }

  };

} // namespace comput

#endif
