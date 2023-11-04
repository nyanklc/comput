#ifndef COMPUT_UTIL_POSITION_H
#define COMPUT_UTIL_POSITION_H

namespace comput {

struct Position {
 public:
  float x = 0;
  float y = 0;

  Position(float xx = 0, float yy = 0) {
    x = xx;
    y = yy;
  }

  Position(const Position &other) {
    x = other.x;
    y = other.y;
  }
};

typedef Position Point;

}  // namespace comput

#endif