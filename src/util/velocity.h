#ifndef COMPUT_UTIL_VELOCITY_H
#define COMPUT_UTIL_VELOCITY_H

#include <eigen3/Eigen/Dense>

namespace comput {

  struct Velocity {
  public:
    Eigen::Vector2f vec;

    Velocity() {
      vec = Eigen::Vector2f(0, 0);
    }

    Velocity(const Eigen::Vector2f &vel) {
      vec = vel;
    }

    Velocity(const Velocity &rhs) {
      vec = rhs.vec;
    }

    inline void operator=(const Velocity &rhs) {
      vec = rhs.vec;
    }

    static Velocity zero() {
      Velocity vel;
      vel.vec = Eigen::Vector2f(0, 0);
      return vel;
    }

    void operator+=(const Eigen::Vector2f &a) {
      vec += a;
    }
  };

}

#endif