#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <map>
#include <memory>
#include <string>

#include "light.hpp"
#include "ray.hpp"
#include "shape.hpp"

namespace graphic
{
	class Raytracer
	{
		public :
		Raytracer();
		Raytracer(unsigned short);	
		~Raytracer();

		Color const 
		trace(math3d::Ray const&,
				std::map<std::string,std::shared_ptr<Shape> > const&,
		 		std::map<std::string,Light> const&,unsigned short = 0) const;

		private :
		Color const ambient_lum(std::map<std::string,Light> const&) const;
		bool shadow(math3d::Ray const&,
						std::map<std::string,std::shared_ptr<Shape> > const&,
						std::string const&) const;
		Color const 
		calc_phong(math3d::Vector const&,math3d::Intersection const&,
					  std::map<std::string,std::shared_ptr<Shape> > const&,
					  std::map<std::string,Light> const&,std::string const&) const;
		
		unsigned short calc_depth_;
	};
}

#endif
