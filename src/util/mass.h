#ifndef COMPUT_UTIL_MASS_H
#define COMPUT_UTIL_MASS_H

#include <limits>

namespace comput
{

    // used to contain a unit as well, but it complicates things
    class Mass
    {
    public:
        Mass() { value = 0; }

        Mass(float val) { value = val; }

        Mass(const Mass &other) { value = other.value; }

        static Mass maxMass() { return Mass(std::numeric_limits<float>::max()); }

        float value;
    };

} // namespace comput

#endif
