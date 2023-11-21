#include "axis_aligned.h"

namespace comput
{
  bool CollisionSystemAxisAligned::areColliding(const Object &obj1, const Object &obj2)
  {
    BBox b1 = obj1.getBBox();
    BBox b2 = obj2.getBBox();

    if (b1.lL().x < b2.uR().x &&
        b1.uR().x > b2.lL().x &&
        b1.lL().y > b2.uR().y &&
        b1.uR().y < b2.lL().y)
      return true;
    return false;

  }
}
