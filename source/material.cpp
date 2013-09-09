#include "../include/material.hpp"

namespace graphic
{
	// default constructor	
	Material::Material() :
	name_(std::string("default")),
	ambient_(Color()),
	diffuse_(Color()),
	specular_(Color()),
	spec_exp_(1.0),
	opacity_(1.0),
	refraction_(1.5)
	{}

	// user constructor
	Material::Material(std::string const& name,Color const& ambient,
                      Color const& diffuse,Color const& specular,
							 double spec_exp) :
	name_(name),
	ambient_(ambient),
	diffuse_(diffuse),
	specular_(specular),
	spec_exp_(spec_exp),	
	opacity_(1.0),
	refraction_(1.5)
	{}

	// user constructor with refraction
	Material::Material(std::string const& name,Color const& ambient,
							 Color const& diffuse,Color const& specular,
							 double spec_exp,double opacity,double refraction) :
	name_(name),
	ambient_(ambient),
	diffuse_(diffuse),
	specular_(specular),
	spec_exp_(spec_exp),	
	opacity_(opacity),
	refraction_(refraction)
	{
		if(opacity_ < 0.0) opacity_ = 0.0;
		else if(opacity > 1.0) opacity_ = 1.0;
		if(refraction_ <= 1.0) refraction_ = 1.5; 
	}

	// destructor
	Material::~Material()
	{}
}
