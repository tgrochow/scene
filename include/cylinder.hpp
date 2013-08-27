#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "intersection.hpp"
#include "point.hpp"
#include "shape.hpp"

namespace graphic
{
	class Cylinder : public Shape
	{
		public :
		Cylinder();
		Cylinder(std::string const&,std::shared_ptr<Material> const&);
		Cylinder(std::string const&,std::shared_ptr<Material> const&,
			 math3d::Point const& min, math3d::Point const& max, double radius);
		~Cylinder();

		math3d::Intersection const intersect(math3d::Ray const&) const;
				
		private :
		math3d::Point min_,max_;
		double radius_;
	};
}

#endif
