#include "engine.h"

namespace comput
{

    ComputEngine::ComputEngine()
    {
        _collisionSystem = 0;
    }

    void ComputEngine::setCollisionSystem(CollisionSystemBase *cs)
    {
        _collisionSystem = std::unique_ptr<CollisionSystemBase>(cs);
    }

    void ComputEngine::update(double dt)
    {
        for (auto &obj : _objects)
        {
            // update
            obj.update(dt);

            // collisions
            if (_collisionSystem)
            {
                _collisionSystem->checkCollisionsOf(obj, _objects, dt);
            }
        }
    }

    void ComputEngine::applyGravity(double dt)
    {
        Force gravity;
        gravity.vec[0] = 0;
        gravity.vec[1] = COMPUT_GRAVITY_CONSTANT; // downwards
        for (auto &obj : _objects)
        {
            gravity.vec *= obj.getMass().value;
            obj.applyForce(gravity);
        }
    }

    void ComputEngine::createObject(Object &obj) { _objects.push_back(obj); }

    std::vector<Object> &ComputEngine::getObjects() { return _objects; }

#ifdef COMPUT_DEBUG
    void ComputEngine::debugCollisionInteractions(SDL_Renderer *renderer)
    {
        for (auto &obj : _objects)
        {
            for (auto &obj2 : _objects)
            {
                if (obj.getName() == obj2.getName())
                    continue;

                auto f = obj.getCollisionResponseTo(obj2);
                auto pos = obj.getPosition();
                comput_util::visualizeVector(pos, f.vec, renderer);
            }
        }
    }

#endif

} // namespace comput
