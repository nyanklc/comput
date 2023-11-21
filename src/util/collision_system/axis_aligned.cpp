#include "brute_force.h"

namespace comput
{
// we're applying Newton's Third Law by checking collisions obj1->obj2 and obj2->obj1.
// objects apply collision response based on the forces given by the other object (and environment) only,
// and they do not exert force on the other.
void CollisionSystemAxisAligned::checkCollisionsOf(Object &obj,
        std::vector<Object> &objects,
        double dt) override
{


}

  bool CollisionSystemAxisAligned::areColliding(const Object &obj1, const Object &obj2)
  {
    
  }

}
