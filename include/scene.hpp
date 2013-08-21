#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "camera.hpp"
#include "light.hpp"
#include "pixel.hpp"
#include "shape.hpp"

namespace graphic
{
	class Scene
	{
		public :	
		Scene(std::map<std::string,std::shared_ptr<Camera> > const& cameras,
				std::map<std::string,Light> const& lights,
				std::map<std::string,std::shared_ptr<Material> > const& materials,
				std::map<std::string,std::shared_ptr<Shape> > const& shapes,
				std::shared_ptr<Camera> const& rcam,std::string const& filename,
				unsigned short resx,unsigned short resy);
		void save() const;

		private :
		std::vector<Pixel> const render() const;

		std::map<std::string,std::shared_ptr<Camera> > cameras_;
		std::map<std::string,Light> lights_;
		std::map<std::string,std::shared_ptr<Material> > materials_;
		std::map<std::string,std::shared_ptr<Shape> > shapes_;
		std::weak_ptr<Camera> rcam_;
		std::string filename_;
		unsigned short resx_,resy_;
	};
}

#endif
