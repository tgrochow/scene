#ifndef BUW_PIXEL_HPP
#define BUW_PIXEL_HPP

// header, system
#include <iosfwd>

// header, project
#include "color.hpp"

namespace graphic
{
	class Pixel 
	{
		public : // c'tor
   	Pixel(std::size_t = 0, std::size_t = 0);
   	void print(std::ostream&) const;

		std::size_t x;
		std::size_t y;
		Color color;
	};	

	std::ostream& operator<<(std::ostream&, const Pixel&);
}

#endif // BUW_PIXEL_HPP
