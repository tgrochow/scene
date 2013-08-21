#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

#include "ray.hpp"

namespace graphic
{
	class Camera
	{
		public :
		Camera();
		Camera(std::string const&,double);
		~Camera();

		math3d::Ray const cast_ray(short,short,double) const;
		double calc_distance(unsigned short) const;
		
		private :
		double convert_fov() const;

		std::string name_;
		math3d::Point pos_;
		math3d::Vector up_,dir_;
		double fovx_;
	};
}

#endif
