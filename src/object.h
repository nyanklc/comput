#ifndef COMPUT_OBJECT_H
#define COMPUT_OBJECT_H

#include "globals.h"
#include "util/force.h"
#include "util/mass.h"
#include "util/position.h"
#include "util/velocity.h"

namespace comput {

struct Shape {
};

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

class Object {
 public:
  Object(int x = 0, int y = 0, const Velocity &vel = Velocity::zero()) {
    _pos.x = x;
    _pos.y = y;
    _vel = vel;
  }

  // TODO:
  // Shape getShape();

  virtual void applyForce(Force &f,
                          float dt = COMPUT_SIMULATION_DEFAULT_TIMESTEP);

 private:
  Position _pos;
  Velocity _vel;
  Mass _mass;
};

}  // namespace comput
#endif
