#include "../include/scene_object.hpp"

#include <cmath>
#define _USE_MATH_DEFINES

namespace graphic
{
	Scene_object::Scene_object() :
	name_("default"),
	transform_(math3d::Matrix())
	{}

	Scene_object::Scene_object(std::string const& name) :
	name_(name),
	transform_(math3d::Matrix())
	{}

	Scene_object::~Scene_object()
	{}

	// transformation
	// rotate around x-axis
	void 
	Scene_object::rotate_x(double angle)
	{
		transform_ *= math3d::make_rotation_x(convert_angle(angle));
	}

	// rotate around y-axis
	void 
	Scene_object::rotate_y(double angle)
	{
		transform_ *= math3d::make_rotation_y(convert_angle(angle));
	}

	// rotate around z-axis
	void 
	Scene_object::rotate_z(double angle)
	{
		transform_ *= math3d::make_rotation_z(convert_angle(angle));
	}

	// scale coordinate system
	void 
	Scene_object::scale(math3d::Vector const& sv)
	{
		transform_ *= math3d::make_scale(sv);
	}

	// translate coordinate system
	void 
	Scene_object::translate(math3d::Vector const& tv)
	{
		transform_ *= math3d::make_translation(tv);
	}	

	// convert degree to radiant
	double convert_angle(double degree)
	{
		return degree * M_PI / 180;
	}

	// transform ray in coordinate system
	math3d::Ray const 
	Scene_object::transform(math3d::Ray const& r) const
	{
		math3d::Point origin(r.origin_);
		math3d::Vector direction(r.direction_);

		origin = transform_ * origin;		
		direction = transform_ * direction;

		return math3d::Ray(origin,direction);
	}
}
