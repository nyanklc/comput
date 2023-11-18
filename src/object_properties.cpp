#include "object_properties.h"

namespace comput
{
    ObjectPropertiesInteraction::ObjectPropertiesInteraction(float repForce)
    {
        repulsionForceMagnitude = repForce;
    }

    ObjectPropertiesInteraction::ObjectPropertiesInteraction(const ObjectPropertiesInteraction& other)
    {
        repulsionForceMagnitude = other.repulsionForceMagnitude;
    }

    Force ObjectPropertiesInteraction::calculateRepulsionForce(double x1, double y1, double x2, double y2) const
    {
        Eigen::Vector2f vec = comput_util::getUnitVector(x1, y1, x2, y2);
        return Force(vec * repulsionForceMagnitude);
    }
}