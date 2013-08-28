#include "../include/cylinder.hpp"
#include "../include/circle.hpp"

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
		double ab2,a,b,c,discriminant,side_b,h;		
		math3d::Ray r(ray), s;
		r = transform(r);		
		math3d::Point origin(r.origin_);	
		math3d::Vector AB, AO, AOxAB, VxAB, direction(r.direction_), d, normal;

		//Intersection Cylinder Mantel 
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

		math3d::Intersection icylinder(math3d::Intersection(true,origin,normal,material_));

		if(!(origin[0] >= min_[0] -radius_ && origin[0] <= max_[0] + radius_ &&
			origin[1] >= min_[1] -radius_ && origin[1] <= max_[1] + radius_ &&
			origin[2] >= min_[2] -radius_ && origin[2] <= max_[2] + radius_))
		{
			icylinder.hit_ = false;
		}

		icylinder = transform(icylinder);


		math3d::Intersection ic1(Circle(name_, std::shared_ptr<Material>(material_), min_, radius_).intersect(r));
		math3d::Intersection ic2(Circle(name_, std::shared_ptr<Material>(material_), max_, radius_).intersect(r));
			
		if (icylinder.hit_)
		{
			if (ic1.hit_)
			{
				if (math3d::distance(icylinder.intersection_, r.origin_) < math3d::distance(ic1.intersection_, r.origin_))
					return icylinder;
				else 
					return ic1;
			}
			else if (ic2.hit_)
			{
				if (math3d::distance(icylinder.intersection_, r.origin_) < math3d::distance(ic2.intersection_, r.origin_))
					return icylinder;
				else 
					return ic2;
			}		
		}

		else
		{
			if (ic1.hit_)
			{
				if (ic2.hit_)
				{
					if (math3d::distance(ic1.intersection_, r.origin_) < math3d::distance(ic2.intersection_, r.origin_))
						return ic1;
					else 
						return ic2;
				}
				
				else 
				{
					return ic1;
				}
			}

			else
			{
				return ic2;
			}
		}
			return icylinder;
	}
}
