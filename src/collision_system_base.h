#ifndef COMPUT_COLLISION_SYSTEM_BASE_H
#define COMPUT_COLLISION_SYSTEM_BASE_H

#include "object.h"

#include <string>

namespace comput
{
    // TODO:
    // This is a base class for collision checkers.
    // Idea is to use this interface in the engine, but implement the details
    // (like how the objects will be mapped for collision checks, approach of collision
    // detection etc.) in sub-classes.
    class CollisionSystemBase
    {
    public:
        CollisionSystemBase(std::vector<Object> objects) { name = "base" }
        virtual ~CollisionSystemBase();

        virtual void setObjects();
        virtual void getObjects();

        virtual void checkCollisions();
        virtual void applyCollisionResponses();

    protected:
        std::string name;

    };
}

#endif