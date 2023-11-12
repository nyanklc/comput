#ifndef COMPUT_UTIL_VELOCITY_H
#define COMPUT_UTIL_VELOCITY_H

#include <Eigen/Dense>

namespace comput
{

    struct Velocity
    {
    public:
        Eigen::Vector2f vec;

        float x() { return vec(0); }

        float y() { return vec(1); }

        Velocity() { vec = Eigen::Vector2f(0, 0); }

        Velocity(const Eigen::Vector2f &velvec) { vec = velvec; }

        Velocity(const Velocity &rhs) { vec = rhs.vec; }

        inline void operator=(const Velocity &rhs) { vec = rhs.vec; }

        float magnitude()
        {
          // TODO: using squared values for things like these
          // is the preferred approach for performant computation.
          // We won't concern ourselves with performance yet though.
          return vec.norm();
        }

        static Velocity zero()
        {
            Velocity vel;
            vel.vec = Eigen::Vector2f(0, 0);
            return vel;
        }

        Velocity operator+(const Eigen::Vector2f &a)
        {
            Velocity v(vec);
            v.vec = v.vec + a;
            return v;
        }
    };

} // namespace comput

#endif
