#include "../include/triangle.hpp"
#include "../include/graphic_exception.hpp"


namespace graphic
{
	// default constructor	
	Triangle::Triangle() :
	Shape(),
	V0_(math3d::Point(-0.1,-0.1,-0.1)),
	V1_(math3d::Point(0.4,0.4,0.4)),
	V2_(math3d::Point(0.9,0.9,0.9))
	{}	

	// user constructor origin
	Triangle::Triangle(std::string const& name,std::shared_ptr<Material> const& mat) :
	Shape(name,mat),
	V0_(math3d::Point(-0.1,-0.1,-0.1)),
	V1_(math3d::Point(0.4,0.4,0.4)),
	V2_(math3d::Point(0.9,0.9,0.9))
	{}
	
	// user constructor
	Triangle::Triangle(std::string const& name,std::shared_ptr<Material> const& mat,
		 		math3d::Point const& V0,math3d::Point const& V1,math3d::Point const& V2) :
	Shape(name,mat),
	V0_(V0),
	V1_(V1),
	V2_(V2)
	{
		/*if(V0_[0] == V1_[0] (&&) V0_[0] == V2_[0] || V0_[1] == V1_[1] (&&) V0_[1] == V2_[1] || 
		   V0_[2] == V1_[2] (&&) V0_[2] == V2_[2])
		{
			throw Graphic_exception(std::string("coordinate - condition violated"));
		}*/
	}

	// destructor
	Triangle::~Triangle()
	{}


	math3d::Intersection const Triangle::intersect(math3d::Ray const& ray) const
	{
		math3d::Ray r(ray);
		r = transform(r);		
		math3d::Point origin(r.origin_), V0, V1, V2, I;
		math3d::Vector direction(r.direction_), normal;	
		math3d::Vector u, v, w, w0;                  // triangle and ray vectors
		double r0, a0, b0;              			 // params to calc ray-plane intersect
		
		// get triangle edge vectors and plane normal
		u = V1 - V0;
		v = V2 - V0;
		normal = math3d::cross(u, v);   			 // cross product
			
		w0 = r.origin_ - V0;
		a0 = - math3d::dot(normal, w0);
		b0 = math3d::dot(normal, r.direction_);
		
		// get intersect point of ray with triangle plane
		r0 = a0 / b0;
		//if (r0 < 0.0 || r0 > 1.0)       							 // ray goes away from triangle
			//return math3d::Intersection();                   // => no intersect

		
	   I = r.origin_ + r0 * r.direction_;            // intersect point of ray and plane

		// is I inside T?
		double uu, uv, vv, wu, wv, D;
		uu = math3d::dot(u,u);
		uv = math3d::dot(u,v);
		vv = math3d::dot(v,v);
		w = I - V0;
		wu = math3d::dot(w,u);
		wv = math3d::dot(w,v);
		D = (uv * uv) - (uu * vv);
		
		// get and test parametric coords
		double t1, t2;
		t1 = ((uv * wv) - (vv * wu)) / D;
		if (t1 < 0.0 || t1 > 1.0)         // I is outside T
			return math3d::Intersection();
		t2 = (uv * wu - uu * wv) / D;
		if (t2 < 0.0 || (t1 + t2) > 1.0)  // I is outside T
			return math3d::Intersection();


		origin = r.position(std::min(t1,t2));		
		
		return transform(math3d::Intersection(true,origin,normal,material_));		
	}
}
