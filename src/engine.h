#ifndef COMPUT_ENGINE_H
#define COMPUT_ENGINE_H

#include <vector>

#include "object.h"

namespace comput {

// this is like the manager of objects, objects themselves resolve their problems,
// like force calculation in case of collision,
// however engine is the one who notifies them
class ComputEngine {
 public:
  ComputEngine() {}

  void update(double dt);

  void checkCollisionsOf(Object &obj);

  void applyGravity();

  void createObject(Object &obj);

  std::vector<Object> &getObjects();

 private:
  std::vector<Object> _objects;
};

}  // namespace comput

#endif
