#ifndef COMPUT_BBOX_H
#define COMPUT_BBOX_H

#include "util/position.h"

namespace comput
{

class BBox {
public:
  BBox(Point lL = Point{0, 0}, Point uR = Point{0, 0});

  BBox(const BBox &other);

  float getArea();

  //float division, adds error
  Point getCenter();

  //scales around center point
  void scale(float multiplier);

  bool isCollidingWith(const BBox &other);

#ifdef COMPUT_DEBUG
  void print() const;
#endif

protected:
  Point _lL;
  Point _uR;
};

} // namespace comput


#endif
