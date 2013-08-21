#include "../include/pixel.hpp"
#include <ostream> 

namespace graphic
{
	// user constructor
	Pixel::Pixel(std::size_t a, std::size_t b) : 
	x(a),
   y(b),
   color()
	{}

	// print pixel in output-stream
	void 
	Pixel::print(std::ostream& os) const
	{
  		os << "Pixel[" << (int)x << ',' << (int)y << "](" 
     		<< color[0] << ',' 
     		<< color[1] << ',' 
     		<< color[2] << ')';
	}

	std::ostream& 
	operator<<(std::ostream& os, const Pixel& a)
	{
  		std::ostream::sentry cerberus (os);
  		if (cerberus) a.print(os);
  		return os;
	}
}
