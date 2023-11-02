#ifndef COMPUT_ENGINE_H
#define COMPUT_ENGINE_H

#include <vector>

#include "object.h"

namespace comput {

class ComputEngine {
 public:
  ComputEngine() {}

  void update(double dt);

  void applyGravity(double dt);

  void createObject(Object &obj);

  std::vector<Object> &getObjects();

 private:
  std::vector<Object> _objects;
};

}  // namespace comput

#endif
