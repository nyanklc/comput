#ifndef COMPUT_BBOX_H
#define COMPUT_BBOX_H

#include "util/position.h"

namespace comput
{

    class BBox
    {
    public:
        BBox(Pointf lL = Pointf{0, 0}, Pointf uR = Pointf{0, 0});

        BBox(const BBox &other);

        float getArea();

        // float division, adds error
        Pointf getCenter();

        // scales around center point
        void scale(float multiplier);

        bool isCollidingWith(const BBox &other) const;

#ifdef COMPUT_DEBUG
        void print() const;
#endif

    protected:
        Pointf _lL;
        Pointf _uR;
    };

} // namespace comput

#endif
