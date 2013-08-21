#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <memory>
#include "point.hpp"
#include "material.hpp"
#include "vector.hpp"

namespace math3d
{
	struct Intersection
	{
		Intersection();		
		Intersection(bool,Point const&,Vector const&,
						 std::weak_ptr<graphic::Material> const&);
		~Intersection();

		bool hit_;
		Point intersection_;
		Vector normal_;
		std::weak_ptr<graphic::Material> material_;
	};
}

#endif
