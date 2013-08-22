#include "../include/raytracer.hpp"

#include <cmath>

namespace graphic
{
	// default constructor	
	Raytracer::Raytracer() :
	refl_depth_(10),
	refr_depth_(10)
	{}

	// user constructor
	Raytracer::Raytracer(unsigned short refl_depth,unsigned short refr_depth) :
	refl_depth_(refl_depth),
	refr_depth_(refr_depth)
	{}

	// destructor
	Raytracer::~Raytracer()
	{}

	// find nearest intersection and initiate color calculation
	Color const Raytracer::
	trace(math3d::Ray const& r,
			std::map<std::string,std::shared_ptr<Shape> > const& shapes,
			std::map<std::string,Light> const& lights) const
	{
		// nearest intersection		
		math3d::Intersection is1;
		// name of intersection shape	
		std::string key;

		// for every shape
		for(std::map<std::string,std::shared_ptr<Shape> >::const_iterator i = 
			 shapes.begin() ; i != shapes.end() ; i++)	
		{
			// actual intersection			
			math3d::Intersection is2(i->second->intersect(r));

			/* if nearest intersection isn't set or the actual intersection 
				is closer to viewpoint */		
			if(!is1.hit_ || (is2.hit_ && 
				math3d::distance(r.origin_,is2.intersection_) <
				math3d::distance(r.origin_,is1.intersection_)))
			{				
				is1 = is2;
				key = i->first;
			}
		}	

		// no hit
		if(!is1.hit_) return Color();

		// calc vector to viewpoint
		math3d::Vector origin(r.origin_ - is1.intersection_);
		origin = math3d::normalize(origin);

		// shapes for color calculation
		std::map<std::string,std::shared_ptr<Shape> > calc_shapes(shapes);
		// remove shape with nearest intersection
		calc_shapes.erase(key);		

		// initiate phong color calculation
		return calc_phong(origin,is1,calc_shapes,lights);
	}

	// calc the total ambient lumination
	Color const Raytracer::
	ambient_lum(std::map<std::string,Light> const& lights) const
	{
		Color amb;		

		// for every lightsource
		for(std::map<std::string,Light>::const_iterator i = lights.begin() ;
			 i != lights.end() ; i++)
		{
			// sum ambient lumination			
			amb += i->second.amb_lum_;
		}

		return amb;
	}

	// check if intersection is in the shadow of another shape
	bool Raytracer::
	shadow(math3d::Ray const& rl,
			 std::map<std::string,std::shared_ptr<Shape> > const& shapes) const
	{
		bool in_shadow(false);	

		// for every shape
		for(std::map<std::string,std::shared_ptr<Shape> >::const_iterator i = 
			 shapes.begin() ; i != shapes.end() ; i++)	
		{
			math3d::Intersection is(i->second->intersect(rl));
			
			if(is.hit_)
			{ 			
				in_shadow = true;
				break;
			}
		}	

		return in_shadow;
	}

	// calc color
	Color const Raytracer::
	calc_phong(math3d::Vector const& origin,math3d::Intersection const& is,
				  std::map<std::string,std::shared_ptr<Shape> > const& shapes,
				  std::map<std::string,Light> const& lights) const
	{
		std::shared_ptr<Material> mat(is.material_);	
		math3d::Vector n(is.normal_);	
		Color total(mat->ambient_);
		
		// calc the reflected ambient light
		total =  total * ambient_lum(lights);

		for(std::map<std::string,Light>::const_iterator i = lights.begin() ;
			 i != lights.end() ; i++)
		{
			Light	l(i->second);
			// calc vector to actual light source		
			math3d::Vector vl(l.position_ - is.intersection_);

			if(!shadow(math3d::Ray(is.intersection_,vl),shapes))
			{
				// calc reflected vector
				math3d::Vector vr(vl.reflected(n));
				// normalize vector to light source
				vl = math3d::normalize(vl);
				// phong illumination
				total += l.dif_lum_ * (mat->diffuse_ * (math3d::dot(vl,n)) +
				mat->specular_ * (pow(math3d::dot(vr,n),mat->spec_exp_)));
			}
		}

		return total;
	}
}
