#ifndef COMPUT_UTIL_FORCE_H
#define COMPUT_UTIL_FORCE_H

#include "mass.h"

#include <eigen3/Eigen/Dense>

namespace comput {

  struct Force {
  public:
    Eigen::Vector2f vec;

    static Force zero() {
      Force f;
      f.vec = Eigen::Vector2f(0, 0);
      return f;
    }

    Eigen::Vector2f operator/(const Mass &m) {
      return Eigen::Vector2f(vec / m.value);
    }
  };

}

#endif