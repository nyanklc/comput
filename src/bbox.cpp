#include "bbox.h"

#ifdef COMPUT_DEBUG
#include <iostream>
#endif

namespace comput
{

BBox::BBox( Point lL, Point uR ) {
    if (uR.y >= lL.y && uR.x >= lL.x) {
      _lL = lL;
      _uR = uR;
      return;
    }
#ifdef COMPUT_DEBUG
    std::cerr << "Invalid BBox points provided.\n";
#endif
    _lL = Point{0, 0};
    _uR = Point{0, 0};
}

BBox::BBox(const BBox &other) {
  _lL = other._lL;
  _uR = other._uR;
}

float BBox::getArea() {
  return (_uR.x - _lL.x) * (_uR.y - _lL.y);
}

//you're a bed time story...

Point BBox::getCenter() {
  Point p((_lL.x + _uR.x) / 2, (_lL.y + _uR.y) / 2);
  return p;
}

void BBox::scale(float multiplier) {
  auto center = getCenter();
  float width = _uR.x - center.x;
  float height = _uR.y - center.y;
  _uR.x = center.x + width * multiplier;
  _uR.y = center.y + height * multiplier;
  _lL.x = center.x - width * multiplier;
  _lL.y = center.y - height * multiplier;
}

//ride on, little wing.

#include <cassert>
bool BBox::isCollidingWith(const BBox &other) {
  // TODO:
  assert(false);
}

} // namespace comput