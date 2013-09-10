#include "include/scene.hpp"
#include "include/sdf_parser.hpp"
#include <sstream>

int main(int argc,char * argv[])
{
   graphic::Sdf_parser parser("animation.sdf");
	graphic::Scene scene(parser.parse_scene());

	const unsigned short total(120);
	const double angle(90.0);

	for(unsigned short number = 0 ; number < total ; number++)
	{
		std::stringstream name;
		name << "animation/";
		name << number;
		name << ".ppm";	
		scene.rotate_x("testbox",angle/total);	
		scene.rotate_z("testbox",angle/total);	
		scene.save(name.str());
	}
	
	return 0;
}
