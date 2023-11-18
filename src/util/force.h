#ifndef COMPUT_UTIL_FORCE_H
#define COMPUT_UTIL_FORCE_H

#include "mass.h"

#include <Eigen/Dense>

namespace comput
{

    struct Force
    {
    public:
        Eigen::Vector2f vec;

        Force() { vec = Eigen::Vector2f(0, 0); }

        Force(const Eigen::Vector2f& v)
        {
            vec = v;
        }

        Force(const Force &other) { vec = other.vec; }

        static Force zero()
        {
            Force f;
            f.vec = Eigen::Vector2f(0, 0);
            return f;
        }

        // acceleration is just a vector
        Eigen::Vector2f operator/(const Mass &m)
        {
            return Eigen::Vector2f(vec / m.value);
        }

        void operator+=(const Force& f)
        {
            vec += f.vec;
        }

        void operator+=(const Eigen::Vector2f &v)
        {
            vec += v;
        }
    };

} // namespace comput

#endif
