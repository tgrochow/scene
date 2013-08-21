#include "../include/shape.hpp"

namespace graphic
{
	Shape::Shape() :
   name_(std::string("default")),
   material_(std::shared_ptr<Material>(new Material()))
   {}

	Shape::Shape(std::string const& name,std::shared_ptr<Material> const& mat) :
   name_(name),
   material_(mat)
   {}

   Shape::~Shape()
   {}
}
