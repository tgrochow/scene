#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "intersection.hpp"
#include "point.hpp"
#include "shape.hpp"

namespace graphic
{
	class Triangle : public Shape
	{
		public :
		Triangle();
		Triangle(std::string const&,std::shared_ptr<Material> const&);
		Triangle(std::string const&,std::shared_ptr<Material> const&,
			 math3d::Point const&, math3d::Point const&, math3d::Point const&);
		~Triangle();

		bool inside(math3d::Point const&) const;	
		math3d::Intersection const intersect(math3d::Ray const&) const;
				
		private :
		math3d::Point a_,b_,c_;
	};
}

#endif