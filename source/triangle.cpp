#include "../include/triangle.hpp"
#include "../include/graphic_exception.hpp"
#include <iostream>
namespace graphic
{
	// default constructor	
	Triangle::Triangle() :
	Shape(),
	a_(math3d::Point(-0.1,-0.1,-0.1)),
	b_(math3d::Point(0.4,0.4,0.4)),
	c_(math3d::Point(0.9,0.9,0.9))
	{}	

	// user constructor origin
	Triangle::Triangle(std::string const& name,std::shared_ptr<Material> const& mat) :
	Shape(name,mat),
	a_(math3d::Point(-0.1,-0.1,-0.1)),
	b_(math3d::Point(0.4,0.4,0.4)),
	c_(math3d::Point(0.9,0.9,0.9))
	{}
	
	// user constructor
	Triangle::Triangle(std::string const& name,std::shared_ptr<Material> const& mat,
		 		math3d::Point const& a,math3d::Point const& b,math3d::Point const& b) :
	Shape(name,mat),
	a_(a),
	b_(b),
	c_(c)
	{
		if(a_[0] == b_[0] (&&) a_[0] == c_[0] || a_[1] == b_[1] (&&) a_[1] == c_[1] || 
		   a_[2] == b_[2] (&&) a_[2] == c_[2])
		{
			throw Graphic_exception(std::string("coordinate - condition violated"));
		}
	}

	// destructor
	Triangle::~Triangle()
	{}

	math3d::Intersection const Triangle::intersect(math3d::Ray const& ray) const
	{
		math3d::Vector u, v, n;
		math3d::Vector w0, w
		float rr, ra, rb;		
		math3d::Ray r(ray);
		r = transform(r);		
		math3d::Point origin(r.origin_);	
		math3d::Vector direction(r.direction_);



		u = b - a;
		v = c - a;
		n = u * v;
		if (n == (math3d::Vector)0)
			return -1;



		a = pow(direction[0],2) + pow(direction[1],2) - pow(direction[2],2);
		b = 2*origin[0]*direction[0] + 2*origin[1]*direction[1] - 2*origin[2]*direction[2];
		c = pow(origin[0],2) + pow(origin[1],2) - pow(origin[2],2);	
		discriminant = pow(b,2) - 4*a*c;

		if(discriminant < 0)
		{
			return math3d::Intersection();
		}
	
		else if(discriminant == 0)
		{
			double t = -b / (2*a);
			origin = r.position(t);
		}

		else
		{
			double t1,t2;
			t1 = (-b + sqrt(discriminant)) / (2*a);
			t2 = (-b - sqrt(discriminant)) / (2*a);
			origin = r.position(std::min(t1,t2));
		}

		direction = origin - end_;                                                 // und top_?
		return transform(math3d::Intersection(true,origin,direction,material_));
	}
}
