#include "../include/graphic_exception.hpp"

namespace graphic
{
	// default constructor	
	Graphic_exception::Graphic_exception() :
	message_(std::string("no error message defined"))
	{}

	// user constructor
	Graphic_exception::Graphic_exception(std::string const& message) :
	message_(message)
	{}

	// destructor
	Graphic_exception::~Graphic_exception() throw()
	{}

	// get error message
	char const* Graphic_exception::what() const throw()
	{
		return message_.c_str();
	}
}
