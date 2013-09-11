#ifndef SCENE_OBJECT
#define SCENE_OBJECT

#include <string>

#include "matrix.hpp"
#include "ray.hpp"

namespace graphic
{
	class Scene_object
	{
		public :	

		// constructor,destructor
		Scene_object();
		Scene_object(std::string const&);
		virtual ~Scene_object();

		// transform world
		virtual void rotate_x(double angle);
		virtual void rotate_y(double angle);
		virtual void rotate_z(double angle);	
		virtual void scale(math3d::Vector const&);
		virtual void translate(math3d::Vector const&);

		protected :

		// transform ray in coordinate system
		virtual math3d::Ray const transform(math3d::Ray const&) const;
		
		std::string name_;
		// world transformation matrix
		math3d::Matrix transform_;
	};

	// convert degree to radiant
	double convert_angle(double degree);
}

#endif
