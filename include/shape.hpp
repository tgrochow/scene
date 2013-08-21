#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include <string>
#include "intersection.hpp"
#include "material.hpp"
#include "ray.hpp"

namespace graphic
{
	class Shape
	{
		public :
		Shape();
      Shape(std::string const& name,std::shared_ptr<Material> const& mat);
      virtual ~Shape();
      virtual math3d::Intersection const 
				  intersect(math3d::Ray const& r) const = 0;
   
		protected :
		std::string name_;
		std::weak_ptr<Material> material_;
    };
}

#endif
