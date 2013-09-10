#include "../include/cylinder.hpp"
#include "../include/circle.hpp"

#include "../include/graphic_exception.hpp"
#include <iostream>
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
		double ab2,a,b,c,discriminant,side_b,h,t;	
		math3d::Ray r(ray), s;
		r = transform(r);	
		math3d::Point origin(r.origin_);	
		math3d::Vector AB, AO, AOxAB, VxAB, direction(r.direction_), d, normal;

		AB = max_ - min_;
		AO = origin - min_;
		AOxAB = cross(AO,AB);
		VxAB = cross(ray.direction_,AB);

		ab2 = dot(AB,AB);
		a = dot(VxAB,VxAB);
		b = 2 * dot(VxAB, AOxAB);
		c = dot(AOxAB,AOxAB) - (pow(radius_,2) * ab2);

		discriminant = pow(b,2) - 4*a*c;
	
		if(discriminant < 0)
		{
			return math3d::Intersection();
		}
	
		else if(discriminant == 0)
		{
			t = -b / (2*a);
			origin = r.position(t);
		}
	
		else
		{
			double t1,t2;
			t1 = (-b + sqrt(discriminant)) / (2*a);
			t2 = (-b - sqrt(discriminant)) / (2*a);
			origin = r.position(std::min(t1,t2));
			t = std::min(t1,t2);
		}
	
		side_b = (origin - min_).length();
		h = sqrt(pow(side_b,2) - pow(radius_,2));
		d = max_ - min_;
		s.origin_ = min_;
		s.direction_ = d;
		normal = origin - s.position(h);

		// circle intersection
		unsigned short dim;
		double t2,t3;

		if(min_[0] != max_[0]) dim = 0;
		else if(min_[1] != max_[1]) dim = 1;
		else dim = 2;
		
		t2 = (min_[dim] - r.origin_[dim]) / direction[dim];
		t3 = (max_[dim] - r.origin_[dim]) / direction[dim];
		math3d::Point c1(r.position(t2)),c2(r.position(t3));
		math3d::Intersection is1(true,origin,normal,material_),
									is2(true,c1,normal,material_),
									is3(true,c2,normal,material_);
	
		// hit condition mantle and circles
		if(math3d::distance(min_,c1) > radius_) is2.hit_ = false;
		if(math3d::distance(max_,c2) > radius_) is3.hit_ = false;
		if(!(origin[0] >= min_[0] -radius_ && origin[0] <= max_[0] + radius_ &&
			  origin[1] >= min_[1] -radius_ && origin[1] <= max_[1] + radius_ &&
			  origin[2] >= min_[2] -radius_ && origin[2] <= max_[2] + radius_))
		{
			is1.hit_ = false;
		}

		// return nearest hit
		if(!is1.hit_ && !is2.hit_ && !is3.hit_) return math3d::Intersection();
		else if(is1.hit_ && is2.hit_)
			if(t <= t2)
				return transform(is1);
			else
				return transform(is2);
		else if(is1.hit_ && is3.hit_)
			if(t <= t3)
				return transform(is1);
			else
				return transform(is3);
		else if(is2.hit_ && is3.hit_)
			if(t2 <= t3)
				return transform(is2);
			else
				return transform(is3);
		else
			return transform(is1);
	}

}
