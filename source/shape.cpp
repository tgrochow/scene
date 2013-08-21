#include "../include/shape.hpp"

#include <cmath>
#define _USE_MATH_DEFINES

namespace graphic
{
	Shape::Shape() :
   name_(std::string("default")),
   material_(std::shared_ptr<Material>(new Material())),
	transform_(math3d::Matrix()),
	inv_transform_(math3d::Matrix())
   {}

	Shape::Shape(std::string const& name,std::shared_ptr<Material> const& mat) :
   name_(name),
   material_(mat),
	transform_(math3d::Matrix()),
	inv_transform_(math3d::Matrix())
   {}

   Shape::~Shape()
   {}

	void 
	Shape::rotate_x(double angle)
	{
		transform_ *= math3d::make_rotation_x(convert_angle(angle));
		inv_transform_ *= math3d::make_rotation_x(-convert_angle(angle));
	}

	void 
	Shape::rotate_y(double angle)
	{
		transform_ *= math3d::make_rotation_y(convert_angle(angle));
		inv_transform_ *= math3d::make_rotation_y(-convert_angle(angle));
	}

	void 
	Shape::rotate_z(double angle)
	{
		transform_ *= math3d::make_rotation_z(convert_angle(angle));
		inv_transform_ *= math3d::make_rotation_z(-convert_angle(angle));
	}

	void 
	Shape::scale(math3d::Vector const& s)
	{
		transform_ *= math3d::make_scale(s);
		inv_transform_ *= math3d::make_scale(1/s[0],1/s[1],1/s[2]);
	}

	void 
	Shape::translate(math3d::Vector const& t)
	{
		transform_ *= math3d::make_translation(t);
		inv_transform_ *= math3d::make_translation(-t[0],-t[1],-t[2]);
	}

	math3d::Ray const 
	Shape::transform(math3d::Ray const& r) const
	{
		math3d::Point origin(inv_transform_ * r.origin_);		
		math3d::Vector direction(inv_transform_ * r.direction_);
		
		return math3d::Ray(origin,direction);
	}

   math3d::Intersection const 
	Shape::transform(math3d::Intersection const& i) const
	{
		math3d::Point intersection(transform_ * i.intersection_);
		math3d::Matrix inv_trans(inv_transform_);
		inv_trans.transpose();
		math3d::Vector normal(inv_trans * i.normal_);

		return math3d::Intersection(i.hit_,intersection,normal,i.material_);
	}

	double 
	Shape::convert_angle(double angle) const
	{
		return angle * M_PI / 180;
	}
}
