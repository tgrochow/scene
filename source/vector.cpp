// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2008 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  Vector.cpp                                                                      */
/*  project    :  lectures in programming && software engineering, winter 08/09                   */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "../include/vector.hpp"

// includes, system

#include <algorithm> // std::swap_ranges
#include <cmath>     // std::sqrt
#include <limits>    // std::numeric_limits
#include <ostream>   // std::ostream

// includes, project

#include "../include/point.hpp"

// internal unnamed namespace

namespace 
{
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace math3d 
{
  
  // variables, exported

  // functions, exported
  
  Vector::Vector()
  {
    data_[0] = data_[1] = data_[2] = data_[3] = 0.0;
  }
  
  Vector::Vector(Point const& a, Point const& b)
  {
    data_[0] = b[0] - a[0];
    data_[1] = b[1] - a[1];
    data_[2] = b[2] - a[2];
    data_[3] = 0.0;
  }
  
  Vector::Vector(double a, double b, double c, double d)
  {
    data_[0] = a;
    data_[1] = b;
    data_[2] = c;
    data_[3] = d;
  }

  void
  Vector::swap(Vector& rhs)
  {
    std::swap_ranges(data_, data_+4, rhs.data_);
  }

  double const&
  Vector::operator[](unsigned idx) const
  {
    return data_[idx];
  }

  double&
  Vector::operator[](unsigned idx)
  {
    return data_[idx];
  }

  Vector&
  Vector::operator+=(Vector const& rhs)
  {
    data_[0] += rhs.data_[0];
    data_[1] += rhs.data_[1];
    data_[2] += rhs.data_[2];
    // data_[3] += rhs.data_[3];
    
    return *this;
  }

  Vector&
  Vector::operator-=(Vector const& rhs)
  {
    data_[0] -= rhs.data_[0];
    data_[1] -= rhs.data_[1];
    data_[2] -= rhs.data_[2];
    // data_[3] -= rhs.data_[3];
    
    return *this;
  }

  Vector&
  Vector::operator*=(double rhs)
  {
    data_[0] *= rhs;
    data_[1] *= rhs;
    data_[2] *= rhs;
    data_[3] *= rhs;
    
    return *this;
  }

  Vector&
  Vector::operator/=(double rhs)
  {
    data_[0] /= rhs;
    data_[1] /= rhs;
    data_[2] /= rhs;
    data_[3] /= rhs;
    
    return *this;
  }

  double
  Vector::length() const
  {
    return std::sqrt(length_square());
  }

  double
  Vector::length_square() const
  {
    return dot(*this, *this);
  }

	Vector const
	Vector::reflected(Vector const& normal) const
	{
		Vector r(2*math3d::dot(normal,*this)*normal-*this);

		return r.normalize();
	}
  
  Vector&
  Vector::normalize()
  {
    Vector tmp(*this);

    tmp /= length();

    swap(tmp);
    return *this;
  }
  
  Vector
  operator-(Vector const& rhs)
  {
    return Vector(rhs) *= -1.0;
  }
  
  Vector
  operator+(Vector const& lhs, Vector const& rhs)
  {
    return Vector(lhs) += rhs;
  }

  Vector
  operator-(Point const& lhs, Point const& rhs)
  {
    return Vector(rhs, lhs);
  }
  
  Vector
  operator-(Vector const& lhs, Vector const& rhs)
  {
    return Vector(lhs) -= rhs;
  }

  Vector
  operator*(Vector const& lhs, double rhs)
  {
    return Vector(lhs) *= rhs;
  }

  Vector
  operator*(double lhs, Vector const& rhs)
  {
    return Vector(rhs) *= lhs;
  }

  Vector
  operator/(Vector const& lhs, double rhs)
  {
    return Vector(lhs) /= rhs;
  }
  
  double
  length(Vector const& a)
  {
    return a.length();
  }

  double
  length_square(Vector const& a)
  {
    return a.length_square();
  }
	
  
  /* static */ Vector const&
  Vector::null() 
  {
    static Vector null_(0.0, 0.0, 0.0);
    return null_;
  }

  /* static */ Vector const&
  Vector::unit_x()
  {
    static Vector unit_x_(1.0, 0.0, 0.0); 
    return unit_x_;
  }

  /* static */ Vector const&
  Vector::unit_y()
  {
    static Vector unit_y_(0.0, 1.0, 0.0); 
    return unit_y_;
  }

  /* static */ Vector const&
  Vector::unit_z()
  {
    static Vector unit_z_(0.0, 0.0, 1.0); 
    return unit_z_;
  }

  double
  dot(Vector const& lhs, Vector const& rhs)
  {
    return ((lhs[0] * rhs[0]) +
            (lhs[1] * rhs[1]) +
            (lhs[2] * rhs[2]));
  }

  Vector
  cross(Vector const& lhs, Vector const& rhs)
  {
    return Vector(((lhs[1] * rhs[2]) - (lhs[2] * rhs[1])),
                  ((lhs[2] * rhs[0]) - (lhs[0] * rhs[2])),
                  ((lhs[0] * rhs[1]) - (lhs[1] * rhs[0])));
  }

  Vector
  normalize(Vector const& a)
  {
    Vector tmp(a);

    tmp.normalize();
    
    return tmp;
  }
  
  std::ostream&
  operator<<(std::ostream& os, Vector const& a)
  {
    std::ostream::sentry const cerberus(os);

    if (cerberus) {
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
  operator==(Vector const& lhs, Vector const& rhs) 
  {
  		return (std::fabs(rhs[0] - lhs[0]) < 
				  std::numeric_limits<double>::epsilon() && 
          	  std::fabs(rhs[1] - lhs[1]) < 
				  std::numeric_limits<double>::epsilon() && 
          	  std::fabs(rhs[2] - lhs[2]) < 
				  std::numeric_limits<double>::epsilon());          
  }
  
} // namespace math3d {

