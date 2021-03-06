#include "../include/cone.hpp"

#include "../include/graphic_exception.hpp"

#include <cmath>

namespace graphic
{
	// default constructor
	Cone::Cone() :
	Shape(),
	end_(math3d::Point(-0.7,-0.7,-0.7)),
	top_(math3d::Point(0.7,0.7,0.7)),
	radius_(1.0)
	{}

	// user constructor origin
	Cone::Cone(std::string const& name,std::shared_ptr<Material> const& mat):
	Shape(name,mat),
	end_(math3d::Point(-0.7,-0.7,-0.7)),
	top_(math3d::Point(0.7,0.7,0.7)),
	radius_(1.0)
	{
		if(radius_ <= 0.0) 
		throw Graphic_exception(std::string("violated radius condition (>0)"));
	}

	// user constructor
	Cone::Cone(std::string const& name,std::shared_ptr<Material> const& mat,
				 		math3d::Point const& end, math3d::Point const& top, double radius) :
	Shape(name,mat),
	end_(end),
	top_(top),
	radius_(radius)
	{
		if(radius_ <= 0.0) 
		throw Graphic_exception(std::string("violated radius condition (>0)"));
	}

	// destructor
	Cone::~Cone()
	{}

	math3d::Intersection const Cone::intersect(math3d::Ray const& ray) const
	{
		double a, b, c, discriminant, side_b, h;		
		math3d::Ray r(ray), s;
		r = transform(r);		
		math3d::Point origin(r.origin_);	
		math3d::Vector direction(r.direction_), d, normal;

		
		side_b = (top_ - end_).length(); 
		h = sqrt(pow(side_b,2) - pow(radius_,2));
		d = top_ - end_;
		s.origin_ = end_;
		s.direction_ = d;
		normal = origin - s.position(h);

		a = pow(direction[0],2) + pow(direction[1],2) - pow(direction[2],2);
		b = (2*origin[0]*direction[0]) + (2*origin[1]*direction[1]) - (2*origin[2]*direction[2]);
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
		

		return transform(math3d::Intersection(true,origin,normal,material_));
	}
}
