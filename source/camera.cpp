#include "../include/camera.hpp"

#include <cmath>
#define _USE_MATH_DEFINES

namespace graphic
{
	// default constructor
	Camera::Camera() :
	name_(std::string("default")),
	pos_(math3d::Point::origin()),
	dir_(math3d::Vector(0.0,0.0,-1.0)),
	up_(math3d::Vector::unit_y()),
	fovx_(45.0)
	{}

	// user constructor origin	
	Camera::Camera(std::string const& name,double fovx) :
	name_(name),
	pos_(math3d::Point::origin()),
	dir_(math3d::Vector(0.0,0.0,-1.0)),
	up_(math3d::Vector::unit_y()),
	fovx_(fovx)
	{}

	// user constructor
	Camera::Camera(std::string const& name,double fovx,
						math3d::Point const& pos,math3d::Vector const& dir,
						math3d::Vector const& up) :
	name_(name),
	pos_(pos),
	dir_(dir),
	up_(up),
	fovx_(fovx)
	{}


	// destructor
	Camera::~Camera()
	{}

	// cast ray through field of view
	math3d::Ray const 
	Camera::cast_ray(short viewx,short viewy,double distance) const
	{
		math3d::Point pixel(viewx,viewy,-distance);
		math3d::Vector direction(pixel - pos_);
		
		return math3d::Ray(pos_,direction);
	}

	// calc distance to field of view
	double 
	Camera::calc_distance(unsigned short res_x) const
	{
		return res_x / (2 * tan(convert_fov() / 2));
	}

	// convert degree to radiant
	double
	Camera::convert_fov() const
	{
		return fovx_ * M_PI / 180;
	}
}
