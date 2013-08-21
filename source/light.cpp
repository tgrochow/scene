#include "../include/light.hpp"

namespace graphic
{
	// default constructor	
	Light::Light() :
	name_(std::string("default")),
	position_(math3d::Point()),
	amb_lum_(Color(0.25,0.25,0.25)),	
	dif_lum_(Color(0.5,0.5,0.5))
	{}

	// user constructor
	Light::Light(std::string const& name,math3d::Point const& position,
                Color const& amb_lum,Color const& dif_lum) :
	name_(name),
	position_(position),
	amb_lum_(amb_lum),
	dif_lum_(dif_lum)
	{}

	// destructor
	Light::~Light()
	{}
}
