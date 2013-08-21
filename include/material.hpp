#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include "color.hpp"

namespace graphic
{
	struct Material
	{
		Material();		
		Material(std::string const&,Color const&,Color const&,Color const&,
					double spec_exp);
		~Material();

		std::string name_;
		Color ambient_,diffuse_,specular_;	// relfecting coefficient
		double spec_exp_; 						// specular exponent
	};
}

#endif
