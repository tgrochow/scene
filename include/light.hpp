#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include "color.hpp"
#include "point.hpp"

namespace graphic
{
	struct Light
	{
		Light();		
		Light(std::string const&,math3d::Point const&,Color const&, Color const&);
		~Light();

		std::string name_;
		math3d::Point position_;
		Color amb_lum_,dif_lum_;	// ambient, diffuse luminosity
	};
}

#endif
