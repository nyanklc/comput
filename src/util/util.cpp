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
		void visualizeVector(Pointd &pos, Eigen::Vector2f& vec, SDL_Renderer* renderer)
		{
            comput_util_objects::SDLArrow arrow(pos.x, pos.y, vec.x(), vec.y());
            arrow.drawOnRenderer(renderer);
		}
	}

	namespace comput_util_objects
	{
		SDLArrow::SDLArrow(double x1, double y1, double x2, double y2, float headAngle, float headLengthMultiplier)
		{
            auto base = Pointi(static_cast<int>(x1), static_cast<int>(y1));
            auto head = Pointi(static_cast<int>(x2), static_cast<int>(y2));

            _line1.first = base;
            _line1.second = head;

            _line2.second = head;
            _line3.second = head;

            Eigen::Vector2d arrVec(x2-x1, y2-y1);
            arrVec = arrVec.reverse();

            Eigen::Rotation2D<double> rotation(headAngle);
            arrVec = rotation.toRotationMatrix() * arrVec;
            arrVec.normalize();
            _line2.first = Pointi(head.x + arrVec.x() * headLengthMultiplier, head.y + arrVec.y() * headLengthMultiplier);

            Eigen::Rotation2D<double> rotation2(-2 * headAngle);
            arrVec = rotation2.toRotationMatrix() * arrVec;
            arrVec.normalize();
            _line3.first = Pointi(head.x + arrVec.x() * headLengthMultiplier, head.y + arrVec.y() * headLengthMultiplier);
		}

        void SDLArrow::drawOnRenderer(SDL_Renderer *renderer)
        {
            SDL_Point p1{_line1.first.x, _line1.first.y};
            SDL_Point p2{_line1.second.x, _line1.second.y};
            SDL_Point p3{_line2.first.x, _line2.first.y};
            SDL_Point p4{_line3.first.x, _line3.first.y};
            SDL_Point points[] = {p1, p2, p3, p4};
            SDL_RenderDrawLines(renderer, points, 4);
        }
	}
}
