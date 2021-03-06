#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include <string>

#include "intersection.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "scene_object.hpp"

namespace graphic
{
	class Shape : public Scene_object
	{
		public :
		Shape();
      Shape(std::string const& name,std::shared_ptr<Material> const& mat);
      virtual ~Shape();

      virtual math3d::Intersection const 
				  intersect(math3d::Ray const& r) const = 0;

		void rotate_x(double);
		void rotate_y(double);
		void rotate_z(double);
		void scale(math3d::Vector const&);		
		void translate(math3d::Vector const&);
   
		protected :
		math3d::Ray const transform(math3d::Ray const&) const;
		math3d::Intersection const transform(math3d::Intersection const&) const;

		std::weak_ptr<Material> material_;
		math3d::Matrix inv_transform_;
    };
}

#endif
