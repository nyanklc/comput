#ifndef COMPUT_UTIL_POSITION_H
#define COMPUT_UTIL_POSITION_H

#include <cmath>

namespace comput {

struct Position {
 public:
  float x;
  float y;

  Position(float xx = 0, float yy = 0) {
    x = xx;
    y = yy;
  }

  Position(const Position &other) {
    x = other.x;
    y = other.y;
  }

  float distanceTo(const Position &other) const {
    using namespace std;
    return sqrt(pow(x-other.x, 2) + pow(y-other.y, 2));
  }
};

typedef Position Point;

}  // namespace comput

#endif
