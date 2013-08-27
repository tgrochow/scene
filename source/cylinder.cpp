#include "../include/cylinder.hpp"

#include "../include/graphic_exception.hpp"

#include <cmath>

namespace graphic
{
	// default constructor
	Cylinder::Cylinder() :
	Shape(),
	min_(math3d::Point(-0.3,-0.3,-0.3)),
	max_(math3d::Point(0.3,0.3,0.3)),
	radius_(1.0)
	{}

	// user constructor origin
	Cylinder::Cylinder(std::string const& name,std::shared_ptr<Material> const& mat):
	Shape(name,mat),
	min_(math3d::Point(-0.3,-0.3,-0.3)),
	max_(math3d::Point(0.3,0.3,0.3)),
	radius_(1.0)
	{
		if(radius_ <= 0.0) 
		throw Graphic_exception(std::string("violated radius condition (>0)"));
	}

	// user constructor
	Cylinder::Cylinder(std::string const& name,std::shared_ptr<Material> const& mat,
				 		math3d::Point const& min, math3d::Point const& max, double radius) :
	Shape(name,mat),
	min_(min),
	max_(max),
	radius_(radius)
	{
		if(radius_ <= 0.0) 
		throw Graphic_exception(std::string("violated radius condition (>0)"));
	}

	// destructor
	Cylinder::~Cylinder()
	{}

	math3d::Intersection const Cylinder::intersect(math3d::Ray const& ray) const
	{
		double a,b,c,discriminant,side_b, h;		
		math3d::Ray r(ray), s;
		//r = transform(r);		
		math3d::Point origin(r.origin_);	
		math3d::Vector direction(r.direction_), d, normal;

		a = pow(direction[0],2) + pow(direction[1],2);
		b = 2*origin[0]*direction[0] + 2*origin[1]*direction[1];
		c = pow(origin[0],2) + pow(origin[1],2) - 1;	
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
		
		side_b = (origin - min_).length(); 
		h = sqrt(pow(side_b,2) - pow(radius_,2));
		d = max_ - min_;
		s.origin_ = min_;
		s.direction_ = d;
		normal = origin - s.position(h);

		//direction = origin - norm;
                                                 // und max_?
		return transform(math3d::Intersection(true,origin,normal,material_));
	}
}
