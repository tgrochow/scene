// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2008 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  Point.cpp                                                                       */
/*  project    :  lectures in programming && software engineering, winter 08/09                   */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "../include/point.hpp"

// includes, system

#include <algorithm> // std::swap_ranges
#include <cmath>     // std::abs
#include <limits>    // std::numeric_limits
#include <ostream>   // std::ostream

namespace math3d
{
	Point::Point()
	{
		data_[0] = data_[1] = data_[2] = 0.0; data_[3] = 1.0;
	}

	Point::Point(double a, double b, double c, double d)
	{
  		data_[0] = a;
  		data_[1] = b;
  		data_[2] = c;
  		data_[3] = d;
	}

	double const&
	Point::operator[](unsigned idx) const
	{
  		return data_[idx];
	}

	double&
	Point::operator[](unsigned idx)
	{
  		return data_[idx];
	}

	Point&
	Point::operator+=(Vector const& rhs)
	{
  		data_[0] += rhs[0];
  		data_[1] += rhs[1];
  		data_[2] += rhs[2];
  		// data_[3] += rhs[3];

  		return *this;
	}

	Point&
	Point::operator-=(Vector const& rhs)
	{
 		data_[0] -= rhs[0];
		data_[1] -= rhs[1];
 		data_[2] -= rhs[2];
 		// data_[3] -= rhs[3];

		return *this;
	}

	/* static */ Point const&
	Point::origin()
	{
  		static Point origin_(0.0, 0.0, 0.0);
  		return origin_;
	}

	Point
	operator-(Point const& rhs)
	{
  		return Point(-rhs[0], -rhs[1], -rhs[2], rhs[3]);
	}

	Point
	operator+(Point const& lhs, Vector const& rhs)
	{
  		return Point(lhs) += rhs;
	}

	Point
	operator-(Point const& lhs, Vector const& rhs)
	{
 		return Point(lhs) -= rhs;
	}

	double
	distance(Point const& a, Point const& b)
	{
  		return std::abs(length(Vector(a, b)));
	}

	std::ostream&
	operator<<(std::ostream& os, Point const& a)
	{
  		std::ostream::sentry const cerberus(os);

  		if (cerberus) 
		{
    		os << '['
       		<< a[0] << ','
       		<< a[1] << ','
       		<< a[2] << ','
       		<< a[3]
       		<< ']';
  		}

  		return os;
	}

	bool
	operator==(Point const& lhs, Point const& rhs)
	{
		return (std::fabs(rhs[0] - lhs[0]) < 
				  std::numeric_limits<double>::epsilon() &&
        		  std::fabs(rhs[1] - lhs[1]) < 
				  std::numeric_limits<double>::epsilon() &&
        		  std::fabs(rhs[2] - lhs[2]) < 
				  std::numeric_limits<double>::epsilon());
	}

} // namespace math3d {
