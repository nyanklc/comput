#include "util.h"
#include "util.h"

namespace comput
{
	namespace comput_util
	{
		Eigen::Vector2f getUnitVector(double x1, double y1, double x2, double y2)
		{
			Eigen::Vector2f vec;
			vec.x() = x2 - x1;
			vec.y() = y2 - y1;
			vec.normalize();
			return vec;
		}
		void comput_util::visualizeVector(Eigen::Vector2f& vec, SDL_Renderer* renderer)
		{

		}
	}

	namespace comput_util_objects
	{
		SDLArrow::SDLArrow(double x1, double y1, double x2, double y2, float headAngle, float headLengthMultiplier)
		{
			// base of the arrow
			_line1.first = Pointi(static_cast<int>(x1), static_cast<int>(y1));
			// tip of the arrow
			_line1.second = Pointi(static_cast<int>(x2), static_cast<int>(y2));

			// TODO:
		}
	}
}