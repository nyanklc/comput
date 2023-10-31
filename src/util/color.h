#ifndef COMPUT_UTIL_COLOR_H
#define COMPUT_UTIL_COLOR_H

#include <stdint.h>

namespace comput {

  // I simply use SDL_Color as well, but we may tweak the values or add hue etc.
  // later on
  struct Color {
  public:
    Color () {
      r = 255;
      g = 255;
      b = 255;
      a = 255;
    }

    Color(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa) {
      r = rr;
      g = gg;
      b = bb;
      a = aa;
    }

    Color (const Color &rhs) {
      r = rhs.r;
      g = rhs.g;
      b = rhs.b;
      a = rhs.a;
    }

    void operator=(const Color &rhs) {
      r = rhs.r;
      g = rhs.g;
      b = rhs.b;
      a = rhs.a;
    }

    bool operator==(const Color &rhs) {
      if (
          rhs.r == r &&
          rhs.g == g &&
          rhs.b == b &&
          rhs.a == a
          )
        return true;
      return false;
    }

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
  };

}

#endif
