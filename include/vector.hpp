// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2011 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  vector.hpp                                                                      */
/*  project    :  lectures in programming && software engineering                                 */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(BUW_MATH3D_VECTOR_HPP)

#define BUW_MATH3D_VECTOR_HPP

// includes, system
#include <iosfwd> // fwd. decl: std::ostream

// includes, project
//#include <>

namespace math3d 
{

	// types, exported (class, enum, struct, union, typedef)

	class Point;

	class Vector 
	{
		public:
  		Vector();
  		Vector(Point const&, Point const&);           // second - first
  		Vector(double, double, double, double = 0.0); // x, y, z, w
  
  		void swap(Vector&);
  
  		double const& operator[](unsigned) const;
  		double&       operator[](unsigned);
  
  		Vector& operator+=(Vector const&);
  		Vector& operator-=(Vector const&);
  		Vector& operator*=(double);
  		Vector& operator/=(double);
  
  		double length() const;
  		double length_square() const;
		Vector const reflected(Vector const& normal) const;
  
  		static Vector const& null();   // v[0,0,0,0]
  		static Vector const& unit_x(); // v[1,0,0,0]
  		static Vector const& unit_y(); // v[0,1,0,0]
 		static Vector const& unit_z(); // v[0,0,1,0]

  		Vector& normalize();

		private:
  		double data_[4];
	};

	// variables, exported (extern)

	// functions, inlined (inline)

	// functions, exported (extern)

	Vector operator-(Vector const&);

	Vector operator+(Vector const&, Vector const&);
	Vector operator-(Point const&, Point const&);
	Vector operator-(Vector const&, Vector const&);
	Vector operator*(Vector const&, double);
	Vector operator*(double, Vector const&);
	Vector operator/(Vector const&, double);
	bool   operator==(Vector const&, Vector const&);

	double length(Vector const&);
	double length_square(Vector const&);
	double dot(Vector const&, Vector const&);
	Vector cross(Vector const&, Vector const&);
	Vector normalize(Vector const&);

	std::ostream& operator<<(std::ostream&, Vector const&);

} // namespace math3d {

#endif // #if !defined(BUW_MATH3D_VECTOR_HPP)
