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

	// throw graphix exception
	void Sdf_parser::
	parsing_exception(std::string const& message,unsigned short line) const
	{
			std::stringstream ss;
			ss << std::string("\nline ");	
			ss << line;
			ss << std::string(" : " + message);						
			throw Graphic_exception(ss.str());
	}

	// parse material for map insertion
	std::pair<std::string,std::shared_ptr<Material> > const
	Sdf_parser::parse_material(std::stringstream & ss,unsigned short line) const
	{		
		if(count_words(ss.str()) != 13 && count_words(ss.str()) != 15)
			parsing_exception(syntax_material(),line);	
		
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
		
		Material * material;

		if(count_words(ss.str()) == 13)
		{
			material = new Material(name,amb,dif,spe,exp);
		}
	
		else
		{
			double refr[2];
			ss >> refr[0];	
			ss >> refr[1];			
			material = new Material(name,amb,dif,spe,exp,refr[0],refr[1]);
		}

		return std::make_pair(name,std::shared_ptr<Material>(material));
	}

	// parse box for map insertion
	std::pair<std::string,std::shared_ptr<Box> > const
	Sdf_parser::parse_box(std::stringstream & ss,std::map<std::string,
					 			 std::shared_ptr<Material> > const& materials,
								 unsigned short line) const
	{
		if(count_words(ss.str()) != 11)
			parsing_exception(syntax_box(),line);		

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
			parsing_exception("unknown material",line);
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
		if(count_words(ss.str()) != 9)
			parsing_exception(syntax_sphere(),line);			

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
			parsing_exception("unknown material",line);
		}	

		std::shared_ptr<Material> m = materials.find(material)->second;
		math3d::Point c(center[0],center[1],center[2]);
		Sphere * sphere = new Sphere(name,m,c,radius);	

		return std::make_pair(name,std::shared_ptr<Sphere>(sphere));
	}

	// parse triangle for map insertion
	std::pair<std::string,std::shared_ptr<Triangle> > const
	Sdf_parser::parse_triangle(std::stringstream & ss,std::map<std::string,
								  std::shared_ptr<Material> > const& materials,
								  unsigned short line) const
	{
		if(count_words(ss.str()) != 14)
			parsing_exception(syntax_triangle(),line);	

		std::string name,material;
		double A[3],B[3],C[3];

		ss >> name;
		ss >> A[0];
		ss >> A[1];
		ss >> A[2];
		ss >> B[0];
		ss >> B[1];
		ss >> B[2];
		ss >> C[0];
		ss >> C[1];
		ss >> C[2];
		ss >> material;

		if (materials.find(material) == materials.end())
		{	
			parsing_exception("unknown material",line);
		}	

		std::shared_ptr<Material> m = materials.find(material)->second;
		math3d::Point p_A(A[0],A[1],A[2]),
						  p_B(A[0],B[1],B[2]),
						  p_C(B[0],C[1],C[2]);
		Triangle * triangle = new Triangle(name,m,p_A,p_B,p_C);	

		return std::make_pair(name,std::shared_ptr<Triangle>(triangle));
	}

	// parse cone for map insertion
	std::pair<std::string,std::shared_ptr<Cone> > const
	Sdf_parser::parse_cone(std::stringstream & ss,std::map<std::string,
								  std::shared_ptr<Material> > const& materials,
								  unsigned short line) const
	{
		if(count_words(ss.str()) != 12)
			parsing_exception(syntax_cone(),line);	

		std::string name,material;
		double end[3],top[3],radius;

		ss >> name;
		ss >> end[0];
		ss >> end[1];
		ss >> end[2];
		ss >> top[0];
		ss >> top[1];
		ss >> top[2];
		ss >> radius;
		ss >> material;

		if (materials.find(material) == materials.end())
		{	
			parsing_exception("unknown material",line);
		}	

		std::shared_ptr<Material> m = materials.find(material)->second;
		math3d::Point p_end(end[0],end[1],end[2]),
						  p_top(top[0],top[1],top[2]);
		Cone * cone = new Cone(name,m,p_end,p_top,radius);	

		return std::make_pair(name,std::shared_ptr<Cone>(cone));
	}

	// parse cylinder for map insertion
	std::pair<std::string,std::shared_ptr<Cylinder> > const
	Sdf_parser::parse_cylinder(std::stringstream & ss,std::map<std::string,
					 			 	 std::shared_ptr<Material> > const& materials,
								 	 unsigned short line) const
	{
		if(count_words(ss.str()) != 12)
			parsing_exception(syntax_cylinder(),line);			

		std::string name,material;
		double min[3],max[3],radius;
						
		ss >> name;
		ss >> min[0];
		ss >> min[1];
		ss >> min[2];
		ss >> max[0];
		ss >> max[1];
		ss >> max[2];
		ss >> radius;
		ss >> material;

		if (materials.find(material) == materials.end())
		{	
			parsing_exception("unknown material",line);
		}	

		std::shared_ptr<Material> m = materials.find(material)->second;
		math3d::Point p_min(min[0],min[1],min[2]),
						  p_max(max[0],max[1],max[2]);
		Cylinder * cylinder = new Cylinder(name,m,p_min,p_max,radius);	

		return std::make_pair(name,std::shared_ptr<Cylinder>(cylinder));
	}

	// parse light for map insertion
	std::pair<std::string,Light> const
	Sdf_parser::parse_light(std::stringstream & ss,unsigned short line) const
	{			
		if(count_words(ss.str()) != 12)
			parsing_exception(syntax_light(),line);		

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
	Sdf_parser::parse_camera(std::stringstream & ss,unsigned short line) const
	{
		if(count_words(ss.str()) != 4 && count_words(ss.str()) != 13)
			parsing_exception(syntax_camera(),line);		

		std::string name;
		double fovx;
		ss >> name;
		ss >> fovx;

		if(count_words(ss.str()) == 4)
		{
			Camera * camera = new Camera(name,fovx);
			return std::make_pair(name,std::shared_ptr<Camera>(camera));
		}

		else
		{
			double pos[3],dir[3],up[3];
			ss >> pos[0];
			ss >> pos[1];
			ss >> pos[2];
			ss >> dir[0];
			ss >> dir[1];
			ss >> dir[2];
			ss >> up[0];
			ss >> up[1];
			ss >> up[2];
			math3d::Point p(pos[0],pos[1],pos[2]);
			math3d::Vector d(dir[0],dir[1],dir[2]),u(up[0],up[1],up[2]);
			
			Camera * camera = new Camera(name,fovx,p,d,u);
			return std::make_pair(name,std::shared_ptr<Camera>(camera));			
		}
	}

	// transform shapes
	void Sdf_parser::
	transform(std::stringstream & ss,
				 std::map<std::string, std::shared_ptr<Shape> > & shapes,
				 std::map<std::string, std::shared_ptr<Camera> > & cameras,
				 unsigned short line,bool shape) const
	{
		std::string name,transformation;

		ss >> name;

		if (shape && shapes.find(name) == shapes.end())
		{	
			parsing_exception("unknown shape",line);			
		}

		else if(!shape && cameras.find(name) == cameras.end())
		{
			parsing_exception("unknown camera",line);	
		}

		ss >> transformation;

		if(transformation == "rotatex")
		{
			double angle;
			ss >> angle;

			if(shape)
			shapes.find(name)->second->rotate_x(angle);
			else
			cameras.find(name)->second->rotate_x(angle);
		}

		else if(transformation == "rotatey")
		{
			double angle;
			ss >> angle;

			if(shape)
			shapes.find(name)->second->rotate_y(angle);
			else
			cameras.find(name)->second->rotate_y(angle);
		}

		else if(transformation == "rotatez")
		{
			double angle;
			ss >> angle;
		
			if(shape)
			shapes.find(name)->second->rotate_z(angle);
			else
			cameras.find(name)->second->rotate_z(angle);
		}

		else if(transformation == "scale")
		{
			double value[3];
			ss >> value[0];
			ss >> value[1];
			ss >> value[2];
			math3d::Vector v(value[0],value[1],value[2]);

			if(shape)
			shapes.find(name)->second->scale(v);
			else
			cameras.find(name)->second->scale(v);
		}

		else if(transformation == "translate")
		{
			double value[3];
			ss >> value[0];
			ss >> value[1];
			ss >> value[2];
			math3d::Vector v(value[0],value[1],value[2]);

			if(shape)
			shapes.find(name)->second->translate(v);
			else
			cameras.find(name)->second->translate(v);
		}

		else
		{
			parsing_exception("unknown transformation",line);
		}
	}

	Scene const 
	Sdf_parser::parse_scene() const
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


		// open filestream
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

			// define objects
			if (command == "define")
			{
				ss >> command;
				if (command == "material")
				{						
					materials.insert(parse_material(ss,number));
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

					else if (command == "triangle")
					{
						shapes.insert(parse_triangle(ss,materials,number));
					}

					else if (command == "cone")
					{
						shapes.insert(parse_cone(ss,materials,number));
					}

					else if (command == "cylinder")
					{
						shapes.insert(parse_cylinder(ss,materials,number));
					}
				
					else 
					{
						parsing_exception("unknown shape",number);
					}
				
				}

				else if (command == "light")
				{					
					lights.insert(parse_light(ss,number));
				}

				else if (command == "camera")
				{
					cameras.insert(parse_camera(ss,number));
				}

				else 
				{
					parsing_exception("unknown type",number);
				}

			}

			// transform objects
			else if (command == "transform")
			{
				transform(ss,shapes,cameras,number,true);
			}

			// transform camera
			else if (command == "view")
			{
				transform(ss,shapes,cameras,number,false);
			}

			// render image
			else if (command == "render")
			{
				if(count_words(ss.str()) != 5)
					parsing_exception(syntax_render(),number);

				std::string cam_name;	
				ss >> cam_name;			
				ss >> filename;
				ss >> xres;
				ss >> yres;

				if (cameras.find(cam_name) == cameras.end())
				{	
					parsing_exception("unknown camera",number);
				}

			   rcam = cameras.find(cam_name)->second;		
			}

			else if (command[0] == '#' || command == "")
			{}

			else 
			{
				parsing_exception("unknown command",number);
			}

			number++;	
		}

		// close filestream
		in.close();

		// generate parsed scene
		return Scene(cameras,lights,materials,shapes,rcam,filename,xres,yres); 
	}

	// return syntax for defining a material
	std::string const syntax_material()
	{
		std::string syntax;
		syntax.insert(0,"define material <name> <amb_red> ");
		syntax.insert(syntax.length()-1,"<amb_green> <amb_blue> <dif_red> ");
		syntax.insert(syntax.length()-1,"<dif_green> <dif_blue> <spec_red> ");
		syntax.insert(syntax.length()-1,"<spec_green> <spec_blue> <spec_exp>\n");

		return syntax;
	}

	// return syntax for defining a box
	std::string const syntax_box()
	{
		std::string syntax;
		syntax.insert(0,"define shape box <name> <min_x> <min_y> <min_z>");
		syntax.insert(syntax.length()-1,"<max_x> <max_y> <max_z> <mat_name>\n");

		return syntax;
	}

	// return syntax for defining a sphere
	std::string const syntax_sphere()
	{
		std::string syntax;
		syntax.insert(0,"define shape sphere <name> <pos_x> <pos_y> <pos_z>");
		syntax.insert(syntax.length()-1,"<radius> <matname>\n");

		return syntax;
	}

	// return syntax for defining a triangle
	std::string const syntax_triangle()
	{
		std::string syntax;
		syntax.insert(0,"define shape triangle <name> <A_pos_x> <A_pos_y> <A_pos_z>");
		syntax.insert(syntax.length()-1,"<B_pos_x> <B_pos_y> <B_pos_z>\n");
		syntax.insert(syntax.length()-1,"<C_pos_x> <C_pos_y> <C_pos_z>\n");

		return syntax;
	}

	// return syntax for defining a cone
	std::string const syntax_cone()
	{
		std::string syntax;
		syntax.insert(0,"define shape cone <name> <end_x> <end_y> <end_z>");
		syntax.insert(syntax.length()-1,"<top_x> <top_y> <top_z> <mat_name>\n");

		return syntax;
	}

	// return syntax for defining a cylinder
	std::string const syntax_cylinder()
	{
		std::string syntax;
		syntax.insert(0,"define shape cylinder <name> <min_x> <min_y> <min_z>");
		syntax.insert(syntax.length()-1,"<max_x> <max_y> <max_z> <mat_name>\n");

		return syntax;
	}

	// return syntax for defining a light
	std::string const syntax_light()
	{
		std::string syntax;
		syntax.insert(0,"define light <name> <pos_x> <pos_y> <pos_z> <amb_red>");
		syntax.insert(syntax.length()-1,"<amb_green> <amb_blue> <dif_red> ");
		syntax.insert(syntax.length()-1,"<dif_green> <dif_blue>\n");

		return syntax;
	}

	// return syntax for defining a camera
	std::string const syntax_camera()
	{
		std::string syntax;
		syntax.insert(0,"define camera <name> <fov_x>\n");

		return syntax;
	}

	// return syntax for rendering the image
	std::string const syntax_render()
	{
		std::string syntax;
		syntax.insert(0,"render <cam_name> <image_name> <xres> <yres>\n");

		return syntax;
	}

	// count words separated by tab or space of a std::string
	unsigned short count_words(std::string const& s)
	{
		unsigned short num_words(0);
		bool behind_space(true);		
		
		// for every sign in the string		
		for(unsigned short index = 0 ; index < s.length() ; index++)
		{
			// if sign at index is tab or space			
			if(s[index] == ' ' || s[index] == '\t') behind_space = true;

			// new word begins
			else if(behind_space && s[index] != '\n' && s[index] != '\0')
			{
				num_words++;
				behind_space = false;
			}
		}		
	
		return num_words;
	}
}
