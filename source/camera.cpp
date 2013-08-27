#include "../include/camera.hpp"

#include <cmath>
#define _USE_MATH_DEFINES

namespace graphic
{
	// default constructor
	Camera::Camera() :
	Scene_object(),
	pos_(math3d::Point::origin()),
	dir_(math3d::Vector(0.0,0.0,-1.0)),
	up_(math3d::Vector::unit_y()),
	fovx_(45.0)
	{}

	// user constructor origin	
	Camera::Camera(std::string const& name,double fovx) :
	Scene_object(name),
	pos_(math3d::Point::origin()),
	dir_(math3d::Vector(0.0,0.0,-1.0)),
	up_(math3d::Vector::unit_y()),
	fovx_(fovx)
	{}

	// user constructor
	Camera::Camera(std::string const& name,double fovx,
						math3d::Point const& pos,math3d::Vector const& dir,
						math3d::Vector const& up) :
	Scene_object(name),
	pos_(math3d::Point::origin()),
	dir_(math3d::Vector(0.0,0.0,-1.0)),
	up_(math3d::Vector::unit_y()),
	fovx_(fovx)
	{
		math3d::Vector u(math3d::cross(dir_,up_));
		math3d::Vector v(math3d::cross(u,dir_));

		transform_[0] = u[0];
		transform_[1] = v[0];
		transform_[2] = -dir[0];
		transform_[3] = pos_[0];
		transform_[4] = u[1];
		transform_[5] = v[1];
		transform_[6] = -dir[1];
		transform_[7] = pos_[1];
		transform_[8] = u[2];
		transform_[9] = v[2];
		transform_[10] = -dir[2];
		transform_[11] = pos_[2];
	}

	// destructor
	Camera::~Camera()
	{}

	// cast ray through field of view
	math3d::Ray const 
	Camera::cast_ray(short viewx,short viewy,double distance) const
	{
		math3d::Point pixel(viewx,viewy,-distance);
		math3d::Vector direction(pixel - pos_);
		
		return transform(math3d::Ray(pos_,direction));
	}

	// calc distance to field of view
	double 
	Camera::calc_distance(unsigned short res_x) const
	{
		return res_x / (2 * tan(convert_angle(fovx_) / 2));
	}
}
