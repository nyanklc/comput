#ifndef COMPUT_UTIL_POSITION_H
#define COMPUT_UTIL_POSITION_H

#include <cmath>

namespace comput
{
    template <typename T>
    struct Position
    {
    public:
        T x;
        T y;

        explicit Position(T xx = 0, T yy = 0)
        {
            x = xx;
            y = yy;
        }

        Position(const Position &other)
        {
            x = other.x;
            y = other.y;
        }

        T distanceTo(const Position &other) const
        {
            using namespace std;
            return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
        }
    };

    typedef Position<float> Pointf;
    typedef Position<int> Pointi;
    typedef Position<double> Pointd;

} // namespace comput

#endif
