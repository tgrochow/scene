#ifndef SDF_PARSER_HPP
#define SDF_PARSER_HPP

#include <string>

#include "../include/box.hpp"
#include "../include/scene.hpp"
#include "../include/sphere.hpp"

namespace graphic
{
	class Sdf_parser 
	{
		public:
		Sdf_parser();	
		Sdf_parser(std::string const&);
		~Sdf_parser();

		Scene const parse_scene() const;
	
		private:
		std::pair<std::string,std::shared_ptr<Material> > const
		parse_material(std::stringstream &) const;
		std::pair<std::string,std::shared_ptr<Box> > const
		parse_box(std::stringstream &,std::map<std::string,
					 std::shared_ptr<Material> > const&,unsigned short) const;
		std::pair<std::string,std::shared_ptr<Sphere> > const
		parse_sphere(std::stringstream &,std::map<std::string,
					 	 std::shared_ptr<Material> > const&,unsigned short) const;
		std::pair<std::string,Light> const
		parse_light(std::stringstream &) const;
		std::pair<std::string,std::shared_ptr<Camera> > const
		parse_camera(std::stringstream &) const;
		
		void 
		transform(std::stringstream &,
					 std::map<std::string, std::shared_ptr<Shape> > &, 
					 unsigned short) const;

		std::string filename_;
	};

}

#endif
