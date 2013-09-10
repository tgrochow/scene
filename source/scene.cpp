#include "../include/scene.hpp"

#include "../include/graphic_exception.hpp"
#include "../include/ppmwriter.hpp"
#include "../include/raytracer.hpp"

namespace graphic
{
	Scene::
	Scene(std::map<std::string,std::shared_ptr<Camera> > const& cameras,
			std::map<std::string,Light> const& lights,
			std::map<std::string,std::shared_ptr<Material> > const& materials,
			std::map<std::string,std::shared_ptr<Shape> > const& shapes,
			std::shared_ptr<Camera> const& rcam,std::string const& filename,
			unsigned short resx,unsigned short resy) :
	cameras_(cameras),
	lights_(lights),
	materials_(materials),
	shapes_(shapes),
	rcam_(rcam),
	filename_(filename),
	resx_(resx),
	resy_(resy)
	{
		if(resx_ > 10000 || resy_ > 10000)
		{
			throw 
			Graphic_exception("violated resolution (max : 10000)");
		}
	}

	std::vector<Pixel> const 
	Scene::render() const
	{
		std::vector<Pixel> rendered;

		Raytracer rt;
		std::shared_ptr<Camera> rcam(rcam_);
		double d(rcam->calc_distance(resx_));

		for(unsigned short y = 0 ; y < resy_ ; y++)
		{			
			for(unsigned short x = 0 ; x < resx_ ; x++)
			{
				Pixel p(x,y);				
				double viewx,viewy;
				
				if(resx_ % 2 == 0) viewx = -resx_/2 + x;
				else viewx = (-resx_ + 1)/2 + x;
				if(resy_ % 2 == 0) viewy = -resy_/2 + y;
				else viewy = (-resy_ + 1)/2 + y;

				math3d::Ray r(rcam->cast_ray(viewx,viewy,d));
				p.color = rt.trace(r,shapes_,lights_);
				rendered.push_back(p);
			}
		}		

		return rendered;
	}
	
	void 
	Scene::save(std::string const& filename) const
	{
		std::string name(filename_);		
		if(filename != "") name = filename;

		Ppmwriter image (resx_,resy_,name);
		std::vector<Pixel> rendered(render());

		for(std::vector<Pixel>::iterator i = rendered.begin();
			 i != rendered.end();i++)
		{
			image.write(*i);
		}

		image.save();
	}

	void 
	Scene::rotate_x(std::string const& name,double angle,bool shape)
	{
		if(shape)
		{
			if (shapes_.find(name) == shapes_.end())
			{	
				throw 
				Graphic_exception("unknown shape");
			}	

			shapes_.find(name)->second->rotate_x(angle);
		}

		else
		{
			if (cameras_.find(name) == cameras_.end())
			{	
				throw 
				Graphic_exception("unknown camera");
			}	

			cameras_.find(name)->second->rotate_x(angle);
		}
	}

	void 
	Scene::rotate_y(std::string const& name,double angle,bool shape)
	{
		if(shape)
		{
			if (shapes_.find(name) == shapes_.end())
			{	
				throw 
				Graphic_exception("unknown shape");
			}	

			shapes_.find(name)->second->rotate_y(angle);
		}

		else
		{
			if (cameras_.find(name) == cameras_.end())
			{	
				throw 
				Graphic_exception("unknown camera");
			}	

			cameras_.find(name)->second->rotate_y(angle);
		}
	}

	void 
	Scene::rotate_z(std::string const& name,double angle,bool shape)
	{
		if(shape)
		{
			if (shapes_.find(name) == shapes_.end())
			{	
				throw 
				Graphic_exception("unknown shape");
			}	

			shapes_.find(name)->second->rotate_z(angle);
		}

		else
		{
			if (cameras_.find(name) == cameras_.end())
			{	
				throw 
				Graphic_exception("unknown camera");
			}	

			cameras_.find(name)->second->rotate_z(angle);
		}
	}

	void 
	Scene::scale(std::string const& name,math3d::Vector const& sv,bool shape)
	{
		if(shape)
		{
			if (shapes_.find(name) == shapes_.end())
			{	
				throw 
				Graphic_exception("unknown shape");
			}	

			shapes_.find(name)->second->scale(sv);
		}

		else
		{
			if (cameras_.find(name) == cameras_.end())
			{	
				throw 
				Graphic_exception("unknown camera");
			}	

			cameras_.find(name)->second->scale(sv);
		}
	}

	void 
	Scene::translate(std::string const& name,math3d::Vector const& tv,bool shape)
	{
		if(shape)
		{
			if (shapes_.find(name) == shapes_.end())
			{	
				throw 
				Graphic_exception("unknown shape");
			}	

			shapes_.find(name)->second->translate(tv);
		}

		else
		{
			if (cameras_.find(name) == cameras_.end())
			{	
				throw 
				Graphic_exception("unknown camera");
			}	

			cameras_.find(name)->second->translate(tv);
		}
	}
}
