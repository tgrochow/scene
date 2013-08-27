#ifndef BOX_HPP
#define BOX_HPP

#include "point.hpp"
#include "shape.hpp"

namespace graphic
{
	class Box : public Shape
	{
		public :

		// constructor,destructor
		Box();
		Box(std::string const&,std::shared_ptr<Material> const&);
		Box(std::string const&,std::shared_ptr<Material> const&,
			 math3d::Point const&,math3d::Point const&);
		~Box();

		// intersect box - ray
		math3d::Intersection const intersect(math3d::Ray const&) const;
				
		private :
		
		// for intersect method
		bool inside(math3d::Point const&) const;

		math3d::Point min_,max_;
	};
}

#endif
