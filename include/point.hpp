// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2011 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  point.hpp                                                                       */
/*  project    :  lectures in programming && software engineering                                 */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(BUW_MATH3D_POINT_HPP)
#define BUW_MATH3D_POINT_HPP

#include <iosfwd>
#include "vector.hpp"

namespace math3d 
{

	class Point
	{
		public:
		Point();
		Point(double, double, double, double = 1.0); // x, y, z, w

		double const& operator[](unsigned) const;
		double & operator[](unsigned);

		Point & operator+=(Vector const&);
 		Point & operator-=(Vector const&);

		static Point const& origin();     // p[0,0,0,1]

		private:
		double data_[4];
	};

	Point operator-(Point const&);
	Point operator+(Point const&, Vector const&);
	Point operator-(Point const&, Vector const&);
	bool operator==(Point const&, Point const&);
	double distance(Point const&, Point const&);

	std::ostream& operator<<(std::ostream&, Point const&);
} // namespace math3d {

#endif // #if !defined(BUW_MATH3D_POINT_HPP)
