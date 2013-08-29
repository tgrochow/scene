#include "../include/triangle.hpp"
#include "../include/graphic_exception.hpp"
#include <iostream>

namespace graphic
{
	// default constructor	
	Triangle::Triangle() :
	Shape(),
	V0_(math3d::Point(-0.1,-0.1,-0.1)),
	V1_(math3d::Point(0.4,0.4,0.4)),
	V2_(math3d::Point(0.9,0.9,0.9))
	{}	

	// user constructor origin
	Triangle::Triangle(std::string const& name,std::shared_ptr<Material> const& mat) :
	Shape(name,mat),
	V0_(math3d::Point(-0.1,-0.1,-0.1)),
	V1_(math3d::Point(0.4,0.4,0.4)),
	V2_(math3d::Point(0.9,0.9,0.9))
	{}
	
	// user constructor
	Triangle::Triangle(std::string const& name,std::shared_ptr<Material> const& mat,
		 		math3d::Point const& V0,math3d::Point const& V1,math3d::Point const& V2) :
	Shape(name,mat),
	V0_(V0),
	V1_(V1),
	V2_(V2)
	{
		/*if(V0_[0] == V1_[0] (&&) V0_[0] == V2_[0] || V0_[1] == V1_[1] (&&) V0_[1] == V2_[1] || 
		   V0_[2] == V1_[2] (&&) V0_[2] == V2_[2])
		{
			throw Graphic_exception(std::string("coordinate - condition violated"));
		}*/
	}

	// destructor
	Triangle::~Triangle()
	{}

	math3d::Intersection const Triangle::intersect(math3d::Ray const& ray) const
	{
		math3d::Ray r(ray);
		r = transform(r);		
		math3d::Point origin(r.origin_), V0, V1, V2;
		math3d::Vector direction(r.direction_), normal;	
		
		//origin = r.position(std::min(t1,t2));

		return transform(math3d::Intersection(true,origin,normal,material_));
	}
}
