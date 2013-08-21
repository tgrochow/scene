#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <memory>
#include <string>

#include "intersection.hpp"
#include "ray.hpp"
#include "shape.hpp"

namespace graphic
{
	class Sphere : public Shape
	{
		public :
		Sphere();
		Sphere(std::string const& name,std::shared_ptr<Material> const& mat);
		Sphere(std::string const& name,std::shared_ptr<Material> const& mat,
				 math3d::Point const& center,double radius);
		~Sphere();
		math3d::Intersection const intersect(math3d::Ray const& r) const;		

		private :
		math3d::Point center_;
		double radius_;
	};
}

#endif
