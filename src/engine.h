#ifndef COMPUT_ENGINE_H
#define COMPUT_ENGINE_H

#include "object.h"

#include <vector>

namespace comput {

  class ComputEngine {
  public:
    ComputEngine() {}

    void init() {
      _shapes.clear();
    }

    // units are in nanoseconds
    void update(double dt);

  private:
    std::vector<Shape> _shapes;
  };

}

#endif
