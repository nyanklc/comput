#include "engine.h"

namespace comput {

  void ComputEngine::update(double dt) {
    for (auto &obj : _objects) {
      obj.update(dt);
    }
  }

  // TODO:
  void ComputEngine::applyGravity(double dt) {
    Force gravity;
    gravity.vec[0] = 0;
    gravity.vec[1] = COMPUT_GRAVITY_CONSTANT * dt; // downwards
    for (auto &obj : _objects) {
      obj.applyForce(gravity);
    }
  }

  void ComputEngine::createObject(Object &obj) {
    _objects.push_back(obj);
  }

  std::vector<Object> &ComputEngine::getObjects() {
    return _objects;
  }

}
