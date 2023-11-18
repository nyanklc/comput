#include "brute_force.h"

namespace comput
{
// we're applying Newton's Third Law by checking collisions obj1->obj2 and obj2->obj1.
// objects apply collision response based on the forces given by the other object (and environment) only,
// and they do not exert force on the other.
void CollisionSystemBruteForce::checkCollisionsOf(Object &obj,
        std::vector<Object> &objects,
        double dt)
{
    for (auto &obj2 : objects)
    {
        if (obj.getName() == obj2.getName())
            continue;

        if (obj.isCollidingWith(obj2))
        {
            obj.applyCollisionResponseTo(obj2, dt);
        }
    }

}

}
