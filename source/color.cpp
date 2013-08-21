// header i/f
#include "../include/color.hpp"
#include "../include/graphic_exception.hpp"

// header, system
#include <iostream>

namespace graphic
{
   // default constructor 
	Color::Color()
    {
    	data_[0] = 0.0;
    	data_[1] = 0.0;
    	data_[2] = 0.0;
    }

	// user constructor
    Color::Color(float r, float g, float b)
    {
    	data_[0] = r;
    	data_[1] = g;
		data_[2] = b;

		if(data_[0] < 0.0 || data_[0] > 1.0 || 
			data_[1] < 0.0 || data_[1] > 1.0 ||
			data_[2] < 0.0 || data_[2] > 1.0)
		{
			std::cout << r << " " << g << " " << b;			
			throw Graphic_exception
			(std::string("violated color value interval(0.0-1.0)"));
		}
    }
	
	// destructor
	Color::~Color()
	{}

	// validate color values
	void
	Color::validate()
	{
		if(data_[0] < 0.0) data_[0] = 0.0;
		if(data_[1] < 0.0) data_[1] = 0.0;
		if(data_[2] < 0.0) data_[2] = 0.0;
		if(data_[0] > 1.0) data_[0] = 1.0;
		if(data_[1] > 1.0) data_[1] = 1.0;
		if(data_[2] > 1.0) data_[2] = 1.0;
	}

	// print color values in output-stream
    void
    Color::print(std::ostream& os) const
    {
        os << '(' << data_[0] << '|' << data_[1] << '|' 
			  << data_[2] << ')' << std::endl;
    }

	// set color value
    Color::value_t&
    Color::operator[](unsigned short c)
    {
        return data_[c];
    }

	// get color value
    const Color::value_t&
    Color::operator[](unsigned short c) const
    {
        return data_[c];
    }

	// sum colors
    void
    Color::operator+=(Color const& a)
    {
        data_[0]+=a.data_[0];
        data_[1]+=a.data_[1];
        data_[2]+=a.data_[2];
		  validate();
    }

	// sum colors
    Color const
    operator+(Color const& a, Color const& b)
    {
        Color result(a);
        result += b;
        return result;
    }

	// product colors
	 Color const
	 operator*(Color const& c1, Color const& c2)
	 {
		 Color c;		 

		 c[0] = c1[0] * c2[0];
		 c[1] = c1[1] * c2[1];
		 c[2] = c1[2] * c2[2];

		 return c;
	 }

	// product color,factor
	Color const 
	operator*(Color const& c,double factor)
	{
		Color color(c);
		color[0] = color[0] * factor;
		color[1] = color[1] * factor;
		color[2] = color[2] * factor;
		color.validate();

		return color;
	}

	// print color in output-stream
    std::ostream&
    operator<<(std::ostream& os, Color const& Color)
    {
        Color.print(os);
        return os;
    }
}
