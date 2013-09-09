#include "../include/raytracer.hpp"

#include <cmath>

namespace graphic
{
	// default constructor	
	Raytracer::Raytracer() :
	calc_depth_(5)
	{}

	// user constructor
	Raytracer::Raytracer(unsigned short calc_depth) :
	calc_depth_(calc_depth)
	{}

	// destructor
	Raytracer::~Raytracer()
	{}

	// find nearest intersection and initiate color calculation
	Color const Raytracer::
	trace(math3d::Ray const& r,
			std::map<std::string,std::shared_ptr<Shape> > const& shapes,
			std::map<std::string,Light> const& lights,
			std::string const& key_intersect,unsigned short depth) const
	{
		// nearest intersection		
		math3d::Intersection is1;
		// name of intersection shape	
		std::string key;

		// for every shape
		for(std::map<std::string,std::shared_ptr<Shape> >::const_iterator i = 
			 shapes.begin() ; i != shapes.end() ; i++)	
		{
			// reflection don't intersect with shape from the last intersection			
			if(i->first != key_intersect)
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
		}	

		// no hit
		if(!is1.hit_) return Color();

		// initiate phong color calculation
		return calc_phong(r,is1,shapes,lights,key,depth);
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
			 std::map<std::string,std::shared_ptr<Shape> > const& shapes,
			 std::string const& key_intersect) const
	{
		bool in_shadow(false);	

		// for every shape
		for(std::map<std::string,std::shared_ptr<Shape> >::const_iterator i = 
			 shapes.begin() ; i != shapes.end() ; i++)	
		{
			if(i->first != key_intersect)
			{			
				math3d::Intersection is(i->second->intersect(rl));
			
				if(is.hit_)
				{ 			
					in_shadow = true;
					break;
				}
			}
		}	

		return in_shadow;
	}

	// calc color
	Color const Raytracer::
	calc_phong(math3d::Ray const& r,math3d::Intersection const& is,
				  std::map<std::string,std::shared_ptr<Shape> > const& shapes,
				  std::map<std::string,Light> const& lights,
				  std::string const& key_intersect,unsigned short depth) const
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
			// normalize vector
			vl = math3d::normalize(vl);
			// calc vector to viewpoint (ray origin)
			math3d::Vector vo(r.origin_ - is.intersection_);
			vo = math3d::normalize(vo);	

			if(!shadow(math3d::Ray(is.intersection_,vl),shapes,key_intersect))
			{			
				// calc reflected light vector
				math3d::Vector vr(vl.reflected(n));
				// phong illumination
				total += l.dif_lum_ * (mat->diffuse_ * (math3d::dot(vl,n)) +
				mat->specular_ * (pow(math3d::dot(vr,vo),mat->spec_exp_)));
				// reflection
				if(depth <= calc_depth_)
				{		
					// reflection					
					// if material reflects specular light					
					if(mat->specular_[0] > 0.0 || mat->specular_[1] > 0.0 ||
						mat->specular_[2] > 0.0)
					{				
					// calc reflected ray
					math3d::Vector ref(r.direction_ -
						  2 * math3d::dot(is.normal_,r.direction_) * is.normal_);
					math3d::Ray reflected_ray(is.intersection_,ref);
					// add reflection
					total += mat->specular_ *
					trace(reflected_ray,shapes,lights,key_intersect,depth+1);
					}
			
					// refraction
					// if material is transparent
					if(mat->opacity_ < 1.0)
					{
						// refraction in vacuum
						double refr_rate(1.0 / mat->refraction_);
						double w(math3d::dot(r.direction_,is.normal_));
						w = -w * refr_rate;
						double k(1 + (w - refr_rate) * (w + refr_rate));
						math3d::Vector refr_vector(refr_rate * r.direction_);
						refr_vector += (w - k) * is.normal_;
						math3d::Ray refr_ray(is.intersection_,refr_vector);
						math3d::Intersection refr_intersection
						(shapes.find(key_intersect)->second->
						intersect(refr_ray));

						if(refr_intersection.hit_)
						{
							refr_rate = mat->refraction_;
							w = math3d::dot(refr_ray.direction_,
												 -refr_intersection.normal_);
							w = -w * refr_rate;
							k = 1 + (w - refr_rate) * (w + refr_rate);
							refr_vector = refr_rate * refr_ray.direction_;
							refr_vector += (w - k) * refr_intersection.normal_;
							refr_ray.origin_ = refr_intersection.intersection_;
							refr_ray.direction_ = math3d::normalize(refr_vector);
						}

						total = total * mat->opacity_;
						total += 
						trace(refr_ray,shapes,lights,key_intersect,depth+1) *
						(1.0 - mat->opacity_);
					}
				}
			}
		}

		return total;
	}
}
