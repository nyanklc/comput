#include "engine.h"

namespace comput {

//#include <cassert>
void ComputEngine::update(double dt) {
  // TODO: check for collisions
  //assert(false);
  for (auto &obj : _objects) {
    obj.update(dt);
  }
}

// TODO:
void ComputEngine::applyGravity() {
  Force gravity;
  gravity.vec[0] = 0;
  gravity.vec[1] = COMPUT_GRAVITY_CONSTANT;  // downwards
  for (auto &obj : _objects) {
    gravity.vec *= obj.getMass().value;
    obj.applyForce(gravity);
  }
}

void ComputEngine::createObject(Object &obj) { _objects.push_back(obj); }

std::vector<Object> &ComputEngine::getObjects() { return _objects; }

}  // namespace comput
