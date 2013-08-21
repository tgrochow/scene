#ifndef GRAPHIC_EXCEPTION_HPP
#define GRAPHIC_EXCEPTION_HPP

#include <exception>
#include <string>

namespace graphic
{
	class Graphic_exception : public std::exception
	{
		public :
		Graphic_exception();
		Graphic_exception(std::string const&);
		~Graphic_exception() throw();
	
		char const* what() const throw();

		private :
		std::string message_;
	};
}

#endif
