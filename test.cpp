#include "include/scene.hpp"
#include "include/sdf_parser.hpp"

int main(int argc,char * argv[])
{
<<<<<<< HEAD
   graphic::Sdf_parser parser("shadow.sdf");
=======
   graphic::Sdf_parser parser("reflection.sdf");
>>>>>>> af452788970f8a67c4429383cdc16f3704368779
	graphic::Scene scene(parser.parse_scene());
	scene.save();
	
	return 0;
}
