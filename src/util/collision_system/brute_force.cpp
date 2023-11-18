#include "brute_force.h"

namespace comput
{
// TODO: we're basically checking the collision of two objects TWICE,
// maybe add a 'adjacency' matrix that holds a flag indicating
// whether collision check (and the action to resolve it) has been
// processed with a certain object
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
            // TODO: use collision matrix for this collision system
            // TODO: collision check should only be conducted once
            // in order to not apply the responses twice
            obj.applyCollisionResponseTo(obj2, dt);
            obj2.applyCollisionResponseTo(obj, dt);
        }
    }

}

}
