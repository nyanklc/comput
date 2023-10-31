#include "window_handler.h"
#include <SDL_rect.h>

namespace comput {

  void WindowHandler::drawObjects(SDL_Renderer *renderer,
                                  std::vector<Object> &objects) {
    for (auto &obj : objects) {
      _drawObjectRect(renderer, obj);
    }
  }

  void WindowHandler::_drawObjectRect(SDL_Renderer *renderer,
                                      Object &obj) {
    SDL_Color color = obj.getColor();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, obj.getRect());
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // default black
  }

} // namespace comput
