#ifndef COMPUT_UTIL_COLLISION_SYSTEM_BRUTE_FORCE_H
#define COMPUT_UTIL_COLLISION_SYSTEM_BRUTE_FORCE_H

#include "base.h"

namespace comput
{
    class CollisionSystemBruteForce : public CollisionSystemBase
    {
    public:
        CollisionSystemBruteForce()
            : CollisionSystemBase() {}
        ~CollisionSystemBruteForce() {};

        void checkCollisionsOf(Object &obj,
                std::vector<Object> &objects,
                double dt) override;
    };
}

#endif
