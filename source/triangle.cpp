#include "../include/triangle.hpp"
#include "../include/graphic_exception.hpp"
#include <iostream>
namespace graphic
{
	// default constructor	
	Triangle::Triangle() :
	Shape(),
	a_(math3d::Point(-0.5,-0.5,-0.5)),
	b_(math3d::Point(0.5,0.5,0.5))
	c_(math3d::Point(0.9,0.9,0.9))
	{}	

	// user constructor origin
	Triangle::Triangle(std::string const& name,std::shared_ptr<Material> const& mat) :
	Shape(name,mat),
	a_(math3d::Point(-0.5,-0.5,-0.5)),
	b_(math3d::Point(0.5,0.5,0.5))
	c_(math3d::Point(0.9,0.9,0.9))
	{}
	
	// user constructor
	Triangle::Triangle(std::string const& name,std::shared_ptr<Material> const& mat,
		 		math3d::Point const& a,math3d::Point const& b,math3d::Point const& b) :
	Shape(name,mat),
	a_(a),
	b_(b),
	c_(C)
	{
		if(a_[0] == b_[0] && a_[0] == c_[0] || a_[1] == b_[1] && a_[1] == c_[1] || 
		   a_[2] == b_[2] && a_[2] == c_[2])
		{
			throw Graphic_exception(std::string("coordinate - condition violated"));
		}
	}

	// destructor
	Triangle::~Triangle()
	{}

	//math3d::Intersection const 
	//Triangle::intersect(math3d::Ray const& r) const
	//{}	

}
