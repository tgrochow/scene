#ifndef SDF_PARSER_HPP
#define SDF_PARSER_HPP

#include <string>

#include "../include/box.hpp"
#include "../include/cone.hpp"
#include "../include/cylinder.hpp"
#include "../include/scene.hpp"
#include "../include/sphere.hpp"

namespace graphic
{
	class Sdf_parser 
	{
		public:

		// constructor,destructor
		Sdf_parser();	
		Sdf_parser(std::string const&);
		~Sdf_parser();

		// primary method
		Scene const parse_scene() const;
	
		private:

		// throw graphic exception
		void parsing_exception(std::string const&,unsigned short) const;

		// parsing objects for scene generation
		std::pair<std::string,std::shared_ptr<Material> > const
		parse_material(std::stringstream &,unsigned short) const;
		std::pair<std::string,std::shared_ptr<Box> > const
		parse_box(std::stringstream &,std::map<std::string,
					 std::shared_ptr<Material> > const&,unsigned short) const;
		std::pair<std::string,std::shared_ptr<Sphere> > const
		parse_sphere(std::stringstream &,std::map<std::string,
					 	 std::shared_ptr<Material> > const&,unsigned short) const;
		std::pair<std::string,std::shared_ptr<Cone> > const
		parse_cone(std::stringstream &,std::map<std::string,
					 	 std::shared_ptr<Material> > const&,unsigned short) const;
		std::pair<std::string,std::shared_ptr<Cylinder> > const
		parse_cylinder(std::stringstream &,std::map<std::string,
					 	 std::shared_ptr<Material> > const&,unsigned short) const;
		std::pair<std::string,Light> const
		parse_light(std::stringstream &,unsigned short) const;
		std::pair<std::string,std::shared_ptr<Camera> > const
		parse_camera(std::stringstream &,unsigned short) const;

		// transform generated objects
		void transform(std::stringstream &,
					 		std::map<std::string, std::shared_ptr<Shape> > &, 
					 		unsigned short) const;
		// transform field of view
		void fov(std::stringstream &,
					std::map<std::string, std::shared_ptr<Camera> > &,
					unsigned short) const;

		// name of sdf-file
		std::string filename_;
	};

	// help with syntax
	std::string const syntax_material();
	std::string const syntax_box();
	std::string const syntax_cone();
	std::string const syntax_cylinder();
	std::string const syntax_sphere();
	std::string const syntax_light();
	std::string const syntax_camera();
	std::string const syntax_render();

	unsigned short count_words(std::string const&);
}

#endif
