#include "include/scene.hpp"
#include "include/sdf_parser.hpp"

int main(int argc,char * argv[])
{
   graphic::Sdf_parser parser("refraction.sdf");
	graphic::Scene scene(parser.parse_scene());
	scene.save();
	
	return 0;
}
