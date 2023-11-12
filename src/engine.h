#ifndef COMPUT_ENGINE_H
#define COMPUT_ENGINE_H

#include <vector>

#include "object.h"
#include "util/collision_system/base.h"

namespace comput
{

    // this is like the manager of objects, objects themselves resolve their problems,
    // like force calculation in case of collision,
    // however engine is the one who notifies them
    class ComputEngine
    {
    public:
        ComputEngine();

        void setCollisionSystem(CollisionSystemBase *cs);

        void update(double dt);

        void applyGravity();

        void createObject(Object &obj);

        std::vector<Object> &getObjects();

    private:
        std::vector<Object> _objects;
        std::unique_ptr<CollisionSystemBase> _collisionSystem;
    };

} // namespace comput

#endif
