#ifndef COMPUT_OBJECT_PROPERTIES_H
#define COMPUT_OBJECT_PROPERTIES_H

#include "util/force.h"
#include "util/util.h"

namespace comput
{
    struct ObjectPropertiesInteraction
    {
        ObjectPropertiesInteraction(float repForce = 0);
        ObjectPropertiesInteraction(const ObjectPropertiesInteraction& other);

        Force calculateRepulsionForce(double x1, double y1, double x2, double y2) const;
        float repulsionForceMagnitude;
    };
}

#endif
