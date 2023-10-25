#include "object.h"

namespace comput {

void Object::applyForce(Force &f, float dt) {
  auto a = f / _mass;
  _vel += a * dt;
}

}  // namespace comput