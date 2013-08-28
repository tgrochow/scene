#include "../include/circle.hpp"

#include "../include/graphic_exception.hpp"

#include <cmath>

namespace graphic
{
	// default constructor	
	Circle::Circle() :
	Shape(),
	center_(math3d::Point::origin()),
	radius_(1.0)
	{}

	// user constructor origin
	Circle::Circle(std::string const& name,std::shared_ptr<Material> const& mat):
	Shape(name,mat),
	center_(math3d::Point::origin()),
	radius_(1.0)
	{
		if(radius_ <= 0.0) 
		throw Graphic_exception(std::string("violated radius condition(>0)"));
	}

	// user constructor
	Circle::Circle(std::string const& name,std::shared_ptr<Material> const& mat,
				 		math3d::Point const& center,double radius) :
	Shape(name,mat),
	center_(center),
	radius_(radius)
	{
		if(radius_ <= 0.0) 
		throw Graphic_exception(std::string("violated radius condition(>0)"));
	}

	// destructor
	Circle::~Circle()
	{}

	math3d::Intersection const Circle::intersect(math3d::Ray const& ray) const
	{
		double a,b,c,discriminant;		
		math3d::Ray r(ray);
		r = transform(r);		
		math3d::Point origin(r.origin_);	
		math3d::Vector direction(r.direction_), f;
		
		f = r.origin_ - center_;
		a = dot(r.direction_, r.direction_);
		b = 2 * dot(f, r.direction_);
		c = dot(f, f) - pow(radius_,2);


		/* a = pow(direction[0],2) + pow(direction[1],2);
		b = 2*origin[0]*direction[0] + 2*origin[1]*direction[1] 
			 - 2*center_[0]*direction[0] - 2*center_[1]*direction[1];
		c = pow(origin[0],2) + pow(origin[1],2) + pow(center_[0],2) 
			 + pow(center_[1],2) - 2*origin[0]*center_[0] 
			 - 2*origin[1]*center_[1] - pow(radius_,2); */

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

		math3d::Point p1(center_[0] + radius_, center_[1], center_[2]); 
		math3d::Point p2(center_[0], center_[1] + radius_, center_[2]); 
		math3d::Vector v1(p1-center_); 
		math3d::Vector v2(p2-center_);
		math3d::Vector normal (cross(v1,v2));

		return transform(math3d::Intersection(true,origin,normal,material_));
	}
}
