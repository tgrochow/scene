#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

#include "matrix.hpp"
#include "ray.hpp"
#include "scene_object.hpp"

namespace graphic
{
	class Camera : public Scene_object
	{
		public :
		
		// constructor,destructor
		Camera();
		Camera(std::string const&,double);
		Camera(std::string const&,double,math3d::Point const&,
				 math3d::Vector const&,math3d::Vector const&);
		~Camera();

		// basic raycasting
		math3d::Ray const cast_ray(short,short,double) const;
		// calc distance to field of view
		double calc_distance(unsigned short) const;
		
		private :

		math3d::Point pos_;
		math3d::Vector dir_,up_;
		double fovx_;
	};
}

#endif
