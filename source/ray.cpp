#include "../include/ray.hpp"

namespace math3d
{
	// default constructor	
	Ray::Ray() :
	origin_(Point()),
	direction_(Vector())
	{}	

	// user constrctor
	Ray::Ray(Point const& origin,Vector const& direction) :
	origin_(origin),
	direction_(normalize(direction))
	{}

	// destructor
	Ray::~Ray()
	{}

	// calc position
	Point const 
	Ray::position(double t) const
	{
		return origin_ + t * direction_;
	}
}
