#include "engine.h"

namespace comput {

void ComputEngine::update(double dt) {
  for (auto &obj : _objects) {
    // update
    obj.update(dt);

    // collisions
    checkCollisionsOf(obj, dt);
  }
}

// TODO: we're basically checking the collision of two objects TWICE,
// maybe add a 'adjacency' matrix that holds a flag indicating
// whether collision check (and the action to resolve it) has been
// processed with a certain object
void ComputEngine::checkCollisionsOf(Object &obj, double dt) {
  for (auto &obj2 : _objects) {
    if (obj.getName() == obj2.getName()) continue;

    if (obj.isCollidingWith(obj2)) {
      // TODO: exert force in opposite direction
      obj.applyCollisionResponseTo(obj2, dt);
      obj2.applyCollisionResponseTo(obj, dt);
    }
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
