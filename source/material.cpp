#include "../include/material.hpp"

namespace graphic
{
	// default constructor	
	Material::Material() :
	name_(std::string("default")),
	ambient_(Color()),
	diffuse_(Color()),
	specular_(Color()),
	spec_exp_(1.0)
	{}

	// user constructor
	Material::Material(std::string const& name,Color const& ambient,
                      Color const& diffuse,Color const& specular,
							 double spec_exp) :
	name_(name),
	ambient_(ambient),
	diffuse_(diffuse),
	specular_(specular),
	spec_exp_(spec_exp)
	{}

	// destructor
	Material::~Material()
	{}
}
