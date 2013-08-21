#ifndef BUW_RGB_HPP
#define BUW_RGB_HPP

// header, system
#include <iosfwd>

namespace graphic
{
    class Color
    {
        public : // enums, typedefs

        typedef float value_t;

        Color();
        Color(value_t r, value_t g, value_t b);
		  ~Color();

		  void validate();
        void print (std::ostream& os) const;
        value_t & operator[](unsigned short component);
        const value_t& operator[](unsigned short component) const;
        void operator+=(const Color&);
			
        private:
        value_t data_[3]; // rgb
    };

    Color const operator+(const Color& a, const Color& b);
	 Color const operator*(Color const& c1,Color const& c2);
	 Color const operator*(Color const& c,double factor);
    std::ostream& operator<<(std::ostream& os, Color const&);
}

#endif // BUW_RGB_HPP
