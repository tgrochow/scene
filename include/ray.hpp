#ifndef Ray_HPP
#define Ray_HPP

#include "point.hpp"
#include "vector.hpp"

namespace math3d
{
	struct Ray
	{
		Ray();		
		Ray(Point const& origin,Vector const& direction);
		~Ray();

		Point const position(double t) const;

		Point origin_;
		Vector direction_;
	};
}

#endif
