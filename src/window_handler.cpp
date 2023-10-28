#include "window_handler.h"

namespace comput {

  // TODO: colors should be inside shapes?
  void WindowHandler::drawShapes(SDL_Renderer *renderer, std::vector<Shape> &shapes) {
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100; 
    rect.w = 100;
    rect.h = 100;
    Color asd(0, 0, 0, 255);
    Color dsa(255, 255, 255, 255);
    _drawRect(renderer, rect, asd, dsa);
  }

  void WindowHandler::_drawRect(SDL_Renderer *renderer, SDL_Rect &rect, Color &before, Color &after) {
    _setColor(renderer, before.r, before.g, before.b, before.a);
    SDL_RenderFillRect(renderer, &rect);
    _setColor(renderer, after.r, after.g, after.b, after.a);
  }

} // namespace comput
