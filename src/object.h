#ifndef COMPUT_OBJECT_H
#define COMPUT_OBJECT_H

#include "globals.h"
#include "util/force.h"
#include "util/mass.h"
#include "util/position.h"
#include "util/velocity.h"

namespace comput {

class Object {
public:
  Object(int x = 0, int y = 0, const Velocity &vel = Velocity::zero()) {
    _pos.x = x;
    _pos.y = y;
    _vel = vel;
  }

  void applyForce(Force &f, float dt = COMPUT_SIMULATION_DEFAULT_TIMESTEP);

private:
  Position _pos;
  Velocity _vel;
  Mass _mass;
};

}
#endif