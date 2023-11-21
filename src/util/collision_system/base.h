#ifndef COMPUT_UTIL_COLLISION_SYSTEM_BASE_H
#define COMPUT_UTIL_COLLISION_SYSTEM_BASE_H

#include "../../object.h"

#include <string>
#include <vector>

namespace comput
{
    // TODO: can we actually just create a shared engine state and directly use it here? we would probably
    // have to store some additional (perhaps mutated) information in the collision system as well,
    // but we may be able to simply define a 'general purpose' engine state, and quickly compute what
    // is necessary for the collision system if needed.

    // TODO: this is probably not a good idea, for example let's say
    // a collision system uses some sort of grid, and we'll just
    // pass in an object (to check collisions of) and a container
    // of all the objects (to check collisions against). If we need
    // to modify the state of this grid on every iteration, that should
    // be fine somehow. However when we need to modify the objects without
    // the knowledge of this collision system (which will presumably happen
    // frequently), and if the state of the grid is dependent on the state
    // of the objects container, that'll be an issue since we need to
    // capture the changes on the objects and modify the grid accordingly.
    // It should be fine though in cases where the state of the collision
    // system is recomputed on each update regardless.

    // TODO:
    // This is a base class for collision checkers.
    // Idea is to use this interface in the engine, but implement the details
    // (like how the objects will be mapped for collision checks,
    // approach of collision, detection etc.) in sub-classes.
    class CollisionSystemBase
    {
    public:
      CollisionSystemBase() {}
      virtual ~CollisionSystemBase() {}

      // in case the system needs to store the objects
      // TODO: (engine has a copy of the objects as well,
      // this is not efficient)
      virtual void setObjects() {} // optional override
      virtual void getObjects() const {} // optional override

      virtual void checkCollisionsOf(Object &obj,
                                     std::vector<Object> &objects,
                                     double dt)
      {
        for (auto &obj2 : objects)
          {
            if (obj.getName() == obj2.getName())
              continue;

            if (areColliding(obj, obj2))
              {
                obj.applyCollisionResponseTo(obj2, dt);
              }
          } 
      }

      virtual bool areColliding(const Object &obj1, const Object &obj2) = 0;
    };
}

#endif
