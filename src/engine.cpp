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

    // TODO:
    void ComputEngine::applyGravity()
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

} // namespace comput
