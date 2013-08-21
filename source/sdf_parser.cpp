#include "../include/sdf_parser.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <utility> 

#include "../include/color.hpp"
#include "../include/graphic_exception.hpp"

namespace graphic
{
	// default constructor	
	Sdf_parser::Sdf_parser() :
	filename_ (std::string("sdf/default.sdf")) 
	{}

	// user constructor
	Sdf_parser::Sdf_parser(std::string const& filename) :
	filename_ (std::string("sdf/" + filename)) 
	{}

	// destructor
	Sdf_parser::~Sdf_parser()
	{}

	// parse material for map insertion
	std::pair<std::string,std::shared_ptr<Material> > const
	Sdf_parser::parse_material(std::stringstream & ss) const
	{
		std::string name;		
		float ambient[3], diffuse[3], specular[3], exp;

		ss >> name;
		ss >> ambient[0];
		ss >> ambient[1];
		ss >> ambient[2];
		ss >> diffuse[0];
		ss >> diffuse[1];
		ss >> diffuse[2];
		ss >> specular[0];
		ss >> specular[1];
		ss >> specular[2];
		ss >> exp;

		Color amb(ambient[0],ambient[1],ambient[2]),
				dif(diffuse[0],diffuse[1],diffuse[2]),
				spe(specular[0],specular[1],specular[2]);

		Material * material = new Material(name,amb,dif,spe,exp);

		return std::make_pair(name,std::shared_ptr<Material>(material));
	}

	// parse box for map insertion
	std::pair<std::string,std::shared_ptr<Box> > const
	Sdf_parser::parse_box(std::stringstream & ss,std::map<std::string,
					 			 std::shared_ptr<Material> > const& materials,
								 unsigned short line) const
	{
		std::string name, material;
		double min[3], max[3];	

		ss >> name;
		ss >> min[0];
		ss >> min[1];
		ss >> min[2];
		ss >> max[0];
		ss >> max[1];
		ss >> max[2];
		ss >> material;

		if (materials.find(material) == materials.end())
		{	
			std::stringstream message;
			message << std::string("line ");	
			message << line;
			message << std::string(" : unknown material");						
			throw Graphic_exception(message.str());
		}		

		std::shared_ptr<Material> m = materials.find(material)->second;
		math3d::Point pmin(min[0],min[1],min[2]),pmax(max[0],max[1],max[2]);
		Box * box = new Box(name,m,pmin,pmax);	

		return std::make_pair(name,std::shared_ptr<Box>(box));			
	}

	// parse sphere for map insertion
	std::pair<std::string,std::shared_ptr<Sphere> > const
	Sdf_parser::parse_sphere(std::stringstream & ss,std::map<std::string,
					 			 	 std::shared_ptr<Material> > const& materials,
								 	 unsigned short line) const
	{
		std::string name,material;
		double center[3], radius;
						
		ss >> name;
		ss >> center[0];
		ss >> center[1];
		ss >> center[2];
		ss >> radius;
		ss >> material;

		if (materials.find(material) == materials.end())
		{	
			std::stringstream message;
			message << std::string("line ");	
			message << line;
			message << std::string(" : unknown material");						
			throw Graphic_exception(message.str());
		}	

		std::shared_ptr<Material> m = materials.find(material)->second;
		math3d::Point c(center[0],center[1],center[2]);
		Sphere * sphere = new Sphere(name,m,c,radius);	

		return std::make_pair(name,std::shared_ptr<Sphere>(sphere));
	}

	// parse light for map insertion
	std::pair<std::string,Light> const
	Sdf_parser::parse_light(std::stringstream & ss) const
	{
		std::string name;
		double pos[3], ambient[3], diffuse[3];

		ss >> name;
		ss >> pos[0];
		ss >> pos[1];
		ss >> pos[2];
		ss >> ambient[0];
		ss >> ambient[1];
		ss >> ambient[2];
		ss >> diffuse[0];
		ss >> diffuse[1];
		ss >> diffuse[2];

		math3d::Point position(pos[0],pos[1],pos[2]);
		Color amb(ambient[0],ambient[1],ambient[2]),
				dif(diffuse[0],diffuse[1],diffuse[2]);
		Light light(name,position,amb,dif);

		return std::make_pair(name,light);
	}

	// parse camera for map insertion
	std::pair<std::string,std::shared_ptr<Camera> > const
	Sdf_parser::parse_camera(std::stringstream & ss) const
	{
		std::string name;
		double fovx;

		ss >> name;
		ss >> fovx;

		Camera * camera = new Camera(name, fovx);

		return std::make_pair(name,std::shared_ptr<Camera>(camera));
	}

	Scene const Sdf_parser::parse_scene() const
	{
		std::ifstream in;
		std::string line;
		std::map<std::string, std::shared_ptr<Material> > materials;
		std::map<std::string, std::shared_ptr<Shape> > shapes;
		std::map<std::string, Light> lights;
		std::map<std::string, std::shared_ptr<Camera> > cameras;
		std::shared_ptr<Camera> rcam;
		std::string filename;
		unsigned short xres,yres,number = 1;


		in.open(filename_);

		if(!in.is_open()) throw Graphic_exception("sdf-file not found");
		if(in.bad()) throw Graphic_exception("sdf-file is damaged");

		while (!in.eof())
		{
			std::string command; 
			line = "";			
			std::getline(in,line);
			std::stringstream ss(line);

			ss >> command;

			if (command == "define")
			{
				ss >> command;
				if (command == "material")
				{
					materials.insert(parse_material(ss));
				}
				
				else if (command == "shape")
				{
					ss >> command;

					if (command == "box")
					{
						shapes.insert(parse_box(ss,materials,number));
					}

					else if (command == "sphere")
					{
						shapes.insert(parse_sphere(ss,materials,number));
					}
				
					else 
					{
						std::stringstream message;
						message << std::string("line ");	
						message << number;
						message << std::string(" : unknown shape");						
						throw Graphic_exception(message.str());
					}
				
				}

				else if (command == "light")
				{
					lights.insert(parse_light(ss));
				}

				else if (command == "camera")
				{

					cameras.insert(parse_camera(ss));
				}

				else 
				{
					std::stringstream message;
					message << std::string("line ");	
					message << number;
					message << std::string(" : unknown type");						
					throw Graphic_exception(message.str());
				}

			}

			else if (command == "render")
			{
				std::string cam_name;	
				ss >> cam_name;			
				ss >> filename;
				ss >> xres;
				ss >> yres;

				if (cameras.find(cam_name)==cameras.end())
				{	
					std::stringstream message;
					message << std::string("line ");	
					message << number;
					message << std::string(" : unknown type");						
					throw Graphic_exception(message.str());
				}

			   rcam = cameras.find(cam_name)->second;		
			}

			else if (command[0] == '#' || command == "")
			{}

			else 
			{
				std::stringstream message;
				message << std::string("line ");	
				message << number;
				message << std::string(" : unknown command");						
				throw Graphic_exception(message.str());
			}

			number++;	
		}

		in.close();

		return Scene(cameras,lights,materials,shapes,rcam,filename,xres,yres); 
	}
}
