#include "../include/box.hpp"
#include "../include/graphic_exception.hpp"
#include <iostream>
namespace graphic
{
	// default constructor	
	Box::Box() :
	Shape(),
	min_(math3d::Point(-0.5,-0.5,-0.5)),
	max_(math3d::Point(0.5,0.5,0.5))
	{}	

	// user constructor origin
	Box::Box(std::string const& name,std::shared_ptr<Material> const& mat) :
	Shape(name,mat),
	min_(math3d::Point(-0.5,-0.5,-0.5)),
	max_(math3d::Point(0.5,0.5,0.5))
	{}
	
	// user constructor
	Box::Box(std::string const& name,std::shared_ptr<Material> const& mat,
		 		math3d::Point const& min,math3d::Point const& max) :
	Shape(name,mat),
	min_(min),
	max_(max)
	{
		if(min_[0] >= max_[0] || min_[1] >= max_[1] || min_[2] >= max_[2])
		{
			throw Graphic_exception(std::string("min,max-condition violated"));
		}
	}

	// destructor
	Box::~Box()
	{}

	bool 
	Box::inside(math3d::Point const& p) const
	{		
		double const tolerance = 0.00001;		

		return p[0] >= std::min(min_[0],max_[0]) - tolerance && 
				 p[0] <= std::max(min_[0],max_[0]) + tolerance && 
				 p[1] >= std::min(min_[1],max_[1]) - tolerance && 
				 p[1] <= std::max(min_[1],max_[1]) + tolerance && 
				 p[2] >= std::min(min_[2],max_[2]) - tolerance && 
				 p[2] <= std::max(min_[2],max_[2]) + tolerance;
	}

	math3d::Intersection const 
	Box::intersect(math3d::Ray const& r) const
	{		
		math3d::Point origin(r.origin_);	
		math3d::Vector direction(r.direction_);	
		math3d::Intersection is;
		 	
		// for every dimension
		for(unsigned short i = 0 ; i < 3 ; i++)
		{	
			// basis vector			
			math3d::Vector u,v;			
	
			switch(i)
			{
				// calc basis vector for actual dimension				
				case 0 : u = math3d::Point(min_[0],min_[1],max_[2]) - min_;
							v = math3d::Point(min_[0],max_[1],min_[2]) - min_;
							break;
				case 1 : u = math3d::Point(max_[0],min_[1],min_[2]) - min_;
							v = math3d::Point(min_[0],min_[1],max_[2]) - min_;
							break;
				case 2 : u = math3d::Point(min_[0],max_[1],min_[2]) - min_;
							v = math3d::Point(max_[0],min_[1],min_[2]) - min_;
							break;
			}		

			// for min and max
			for(unsigned short j = 0 ; j < 2 ; j++)
			{
				double t(0);				
				switch(j)
				{
					// calc intersection value					
					case 0 : t = (min_[i]-origin[i])/direction[i];
								break;
					case 1 : t = (max_[i]-origin[i])/direction[i];
								break;
				}

				// calc intersection
				math3d::Point p(r.position(t));

				// check if intersection is on box and compare with second intersect
				if(inside(p) && (!is.hit_ || math3d::distance(origin,p) < 
					math3d::distance(origin,is.intersection_)))
				{													
					is.hit_ = true;
					is.intersection_ = p;
					// calc normal
					switch(j)
					{
						case 0 : is.normal_ = math3d::cross(u,v);
									break;
						case 1 : is.normal_ = math3d::cross(v,u);
									break;
					}
					is.normal_ = math3d::normalize(is.normal_);
					is.material_ = material_;
				}
			}	
		}
		
		return is;
	}
}
