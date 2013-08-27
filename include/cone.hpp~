#ifndef CONE_HPP
#define CONE_HPP

#include "intersection.hpp"
#include "point.hpp"
#include "shape.hpp"

namespace graphic
{
	class Cone : public Shape
	{
		public :
		Cone();
		Cone(std::string const&,std::shared_ptr<Material> const&);
		Cone(std::string const&,std::shared_ptr<Material> const&,
			  math3d::Point const&, math3d::Point const&, double radius);
		~Cone();

		math3d::Intersection const intersect(math3d::Ray const&) const;
				
		private :
		math3d::Point end_, top_;
		double radius_;
	};
}

#endif
