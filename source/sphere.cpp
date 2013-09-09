#include "../include/sphere.hpp"

#include "../include/graphic_exception.hpp"

#include <cmath>

namespace graphic
{
	Sphere::Sphere() :
	Shape(),
	center_(math3d::Point::origin()),
	radius_(1.0)
	{}

	Sphere::Sphere(std::string const& name,std::shared_ptr<Material> const& mat):
	Shape(name,mat),
	center_(math3d::Point::origin()),
	radius_(1.0)
	{
		if(radius_ <= 0.0) 
		throw Graphic_exception(std::string("violated radius condition(>0)"));
	}

	Sphere::Sphere(std::string const& name,std::shared_ptr<Material> const& mat,
				 		math3d::Point const& center,double radius) :
	Shape(name,mat),
	center_(center),
	radius_(radius)
	{
		if(radius_ <= 0.0) 
		throw Graphic_exception(std::string("violated radius condition(>0)"));
	}

	Sphere::~Sphere()
	{}

	math3d::Intersection const Sphere::intersect(math3d::Ray const& ray) const
	{
		double a,b,c,discriminant;		
		math3d::Ray r(ray);
		r = transform(r);		
		math3d::Point origin(r.origin_);	
		math3d::Vector direction(r.direction_);

		a = pow(direction[0],2) + pow(direction[1],2) + pow(direction[2],2);
		b = 2*origin[0]*direction[0] + 2*origin[1]*direction[1] +
			 2*origin[2]*direction[2] - 2*center_[0]*direction[0] -
			 2*center_[1]*direction[1] - 2*center_[2]*direction[2];
		c = pow(origin[0],2) + pow(origin[1],2) + pow(origin[2],2) +
			 pow(center_[0],2) + pow(center_[1],2) + pow(center_[2],2) -
			 2*origin[0]*center_[0] - 2*origin[1]*center_[1] - 
			 2*origin[2]*center_[2] - pow(radius_,2);
		discriminant = pow(b,2) - 4*a*c;

		if(discriminant < 0)
		{
			return math3d::Intersection();
		}
	
		else if(discriminant == 0)
		{
			double t = -b / (2*a);
			if(t <= 0.0) return math3d::Intersection();
			origin = r.position(t);
		}

		else
		{
			double t1,t2;
			t1 = (-b + sqrt(discriminant)) / (2*a);
			t2 = (-b - sqrt(discriminant)) / (2*a);
			if(t1 <= 0.0 && t2 < 0.0) return math3d::Intersection();
			else if(t1 <= 0.0) origin = r.position(t2);
			else if(t2 <= 0.0) origin = r.position(t1);
			else origin = r.position(std::min(t1,t2));
		}

		direction = origin - center_;
		return transform(math3d::Intersection(true,origin,direction,material_));
	}
}
