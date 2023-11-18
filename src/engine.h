#ifndef COMPUT_ENGINE_H
#define COMPUT_ENGINE_H

#include <memory>
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

        void applyGravity(double dt);

        void createObject(Object &obj);

        std::vector<Object> &getObjects();

        void debugCollisionInteractions(SDL_Renderer *renderer);

    private:
        std::vector<Object> _objects;
        std::unique_ptr<CollisionSystemBase> _collisionSystem;
    };

} // namespace comput

#endif
