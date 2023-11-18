#ifndef COMPUT_UTIL_UTIL_H
#define COMPUT_UTIL_UTIL_H

#include "position.h"

#include <Eigen/Dense>
#include <SDL.h>

#include <cmath>

namespace comput
{
	namespace comput_util
	{
		// returns unit vector from (1) to (2)
		Eigen::Vector2f getUnitVector(double x1, double y1, double x2, double y2);

		void visualizeVector(Eigen::Vector2f &vec, SDL_Renderer *renderer);
	}

	namespace comput_util_objects
	{
		class SDLArrow
		{
		public:
			SDLArrow(double x1, double y1, double x2, double y2, float headAngle = M_PI / 6, float headLengthMultiplier = 0.25);

			void drawOnRenderer(SDL_Renderer *renderer);
		
		protected:
			std::pair<Pointi, Pointi> _line1;
			std::pair<Pointi, Pointi> _line2;
			std::pair<Pointi, Pointi> _line3;
		};
	}
}

#endif