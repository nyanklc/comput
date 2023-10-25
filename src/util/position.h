#ifndef COMPUT_UTIL_POSITION_H
#define COMPUT_UTIL_POSITION_H

namespace comput {

struct Position {
 public:
  float x = 0;
  float y = 0;
};

struct IPosition {
 public:
  int x = 0;
  int y = 0;
};

}  // namespace comput

#endif