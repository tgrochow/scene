#include "../include/intersection.hpp"

namespace math3d
{
	// default constructor	
	Intersection::Intersection() :
	hit_(false),
	intersection_(math3d::Point::origin()),
	normal_(math3d::Vector::unit_x()),
	material_(std::shared_ptr<graphic::Material>(new graphic::Material()))
	{}	

	// user constructor
	Intersection::
	Intersection(bool hit,Point const& intersection,Vector const& normal,
					 std::weak_ptr<graphic::Material> const& mat) :
	hit_(hit),
	intersection_(intersection),
	normal_(normal),
	material_(mat)
	{}
	
	// destructor
	Intersection::~Intersection()
	{}
}
