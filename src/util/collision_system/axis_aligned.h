#ifndef COMPUT_UTIL_COLLISION_SYSTEM_AXIS_ALIGNED_H
#define COMPUT_UTIL_COLLISION_SYSTEM_AXIS_ALIGNED_H

#include "base.h"

namespace comput
{
    class CollisionSystemAxisAligned : public CollisionSystemBase
    {
    public:
        CollisionSystemAxisAligned()
            : CollisionSystemBase() {}
        ~CollisionSystemAxisAligned() {};

      bool areColliding(const Object &obj1, const Object &obj2) override;
    };
}

#endif
