#ifndef CIRLCE_HPP
#define CIRLCE_HPP

#include <memory>
#include <string>

#include "intersection.hpp"
#include "ray.hpp"
#include "shape.hpp"

namespace graphic
{
	class Circle : public Shape
	{
		public :
		Circle();
		Circle(std::string const& name,std::shared_ptr<Material> const& mat);
		Circle(std::string const& name,std::shared_ptr<Material> const& mat,
				 math3d::Point const& center,double radius);
		~Circle();
		math3d::Intersection const intersect(math3d::Ray const& r) const;		

		private :
		math3d::Point center_;
		double radius_;
	};
}

#endif
