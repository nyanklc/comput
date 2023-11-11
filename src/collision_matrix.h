// TODO:

#ifndef COMPUT_COLLISION_MATRIX_H
#define COMPUT_COLLISION_MATRIX_H
#include "object.h"

namespace comput
{

    class CollisionMatrix
    {
    public:
        CollisionMatrix(std::vector<Object> &objects);
        virtual ~CollisionMatrix();

        void addCollision();

        void reset();

    protected:
        bool **_matrix;
    };

}

#endif