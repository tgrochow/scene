// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2011 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  matrix.cpp                                                                      */
/*  project    :  lectures in programming && software engineering                                 */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "../include/matrix.hpp"

// includes, system

#include <algorithm>              // std::copy, std::swap_ranges
#include <cmath>                  // std::cos, std::sin
#include <iomanip>                // std::fixed, std::setprecision
#include <ostream>                // std::ostream
#include <limits>                 // std::numeric_limits

// includes, project
#include "../include/point.hpp"

// internal unnamed namespace

namespace {
  
double const null_array16[16] = {
  0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0
};

double const ident_array16[16] = {
  1.0, 0.0, 0.0, 0.0,
  0.0, 1.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 1.0
};

// functions, internal

double
det3_helper(double a1, double a2, double a3,
            double b1, double b2, double b3,
            double c1, double c2, double c3)
{
  return ((a1 * b2 * c3) + (a2 * b3 * c1) + (a3 * b1 * c2) -
          (a1 * b3 * c2) - (a2 * b1 * c3) - (a3 * b2 * c1));
}

} // namespace {

namespace math3d {
  
Matrix::Matrix()
{
  std::copy(ident_array16, ident_array16+16, data_);
}

Matrix::Matrix(double const a[16])
{
  std::copy(a, a+16, data_);
}

void
Matrix::swap(Matrix& rhs)
{
  std::swap_ranges(data_, data_+16, rhs.data_);
}

double&
Matrix::operator[](unsigned component)
{
  return data_[component];
}

double const&
Matrix::operator[](unsigned component) const
{
  return data_[component];
}

Matrix&
Matrix::operator*=(Matrix const& rhs)
{
  Matrix tmp;
  
  tmp.data_[ 0] = (data_[ 0] * rhs.data_[ 0] +
                   data_[ 4] * rhs.data_[ 1] +
                   data_[ 8] * rhs.data_[ 2] +
                   data_[12] * rhs.data_[ 3]);
  tmp.data_[ 1] = (data_[ 1] * rhs.data_[ 0] +
                   data_[ 5] * rhs.data_[ 1] +
                   data_[ 9] * rhs.data_[ 2] +
                   data_[13] * rhs.data_[ 3]);
  tmp.data_[ 2] = (data_[ 2] * rhs.data_[ 0] +
                   data_[ 6] * rhs.data_[ 1] +
                   data_[10] * rhs.data_[ 2] +
                   data_[14] * rhs.data_[ 3]);
  tmp.data_[ 3] = (data_[ 3] * rhs.data_[ 0] +
                   data_[ 7] * rhs.data_[ 1] +
                   data_[11] * rhs.data_[ 2] +
                   data_[15] * rhs.data_[ 3]);
  tmp.data_[ 4] = (data_[ 0] * rhs.data_[ 4] +
                   data_[ 4] * rhs.data_[ 5] +
                   data_[ 8] * rhs.data_[ 6] +
                   data_[12] * rhs.data_[ 7]);
  tmp.data_[ 5] = (data_[ 1] * rhs.data_[ 4] +
                   data_[ 5] * rhs.data_[ 5] +
                   data_[ 9] * rhs.data_[ 6] +
                   data_[13] * rhs.data_[ 7]);
  tmp.data_[ 6] = (data_[ 2] * rhs.data_[ 4] +
                   data_[ 6] * rhs.data_[ 5] +
                   data_[10] * rhs.data_[ 6] +
                   data_[14] * rhs.data_[ 7]);
  tmp.data_[ 7] = (data_[ 3] * rhs.data_[ 4] +
                   data_[ 7] * rhs.data_[ 5] +
                   data_[11] * rhs.data_[ 6] +
                   data_[15] * rhs.data_[ 7]);
  tmp.data_[ 8] = (data_[ 0] * rhs.data_[ 8] +
                   data_[ 4] * rhs.data_[ 9] +
                   data_[ 8] * rhs.data_[10] +
                   data_[12] * rhs.data_[11]);
  tmp.data_[ 9] = (data_[ 1] * rhs.data_[ 8] +
                   data_[ 5] * rhs.data_[ 9] +
                   data_[ 9] * rhs.data_[10] +
                   data_[13] * rhs.data_[11]);
  tmp.data_[10] = (data_[ 2] * rhs.data_[ 8] +
                   data_[ 6] * rhs.data_[ 9] +
                   data_[10] * rhs.data_[10] +
                   data_[14] * rhs.data_[11]);
  tmp.data_[11] = (data_[ 3] * rhs.data_[ 8] +
                   data_[ 7] * rhs.data_[ 9] +
                   data_[11] * rhs.data_[10] +
                   data_[15] * rhs.data_[11]);
  tmp.data_[12] = (data_[ 0] * rhs.data_[12] +
                   data_[ 4] * rhs.data_[13] +
                   data_[ 8] * rhs.data_[14] +
                   data_[12] * rhs.data_[15]);
  tmp.data_[13] = (data_[ 1] * rhs.data_[12] +
                   data_[ 5] * rhs.data_[13] +
                   data_[ 9] * rhs.data_[14] +
                   data_[13] * rhs.data_[15]);
  tmp.data_[14] = (data_[ 2] * rhs.data_[12] +
                   data_[ 6] * rhs.data_[13] +
                   data_[10] * rhs.data_[14] +
                   data_[14] * rhs.data_[15]);
  tmp.data_[15] = (data_[ 3] * rhs.data_[12] +
                   data_[ 7] * rhs.data_[13] +
                   data_[11] * rhs.data_[14] +
                   data_[15] * rhs.data_[15]);
  swap(tmp);
  return *this;
}

Matrix&
Matrix::operator*=(double rhs)
{
  for (unsigned idx = 0; idx < 16; ++idx)
    data_[idx] *= rhs;
  return *this;
}

Matrix&
Matrix::operator/=(double rhs)
{
  for (unsigned idx = 0; idx < 16; ++idx)
    data_[idx] /= rhs;
  return *this;
}

double
Matrix::determinant() const
{
  double const& a1(data_[ 0]);
  double const& b1(data_[ 4]);
  double const& c1(data_[ 8]);
  double const& d1(data_[12]);
  
  double const& a2(data_[ 1]);
  double const& b2(data_[ 5]);
  double const& c2(data_[ 9]);
  double const& d2(data_[13]);
  
  double const& a3(data_[ 2]);
  double const& b3(data_[ 6]);
  double const& c3(data_[10]);
  double const& d3(data_[14]);
  
  double const& a4(data_[ 3]);
  double const& b4(data_[ 7]);
  double const& c4(data_[11]);
  double const& d4(data_[15]);
  
  return (a1 * det3_helper(b2, b3, b4, c2, c3, c4, d2, d3, d4) -
          b1 * det3_helper(a2, a3, a4, c2, c3, c4, d2, d3, d4) +
          c1 * det3_helper(a2, a3, a4, b2, b3, b4, d2, d3, d4) -
          d1 * det3_helper(a2, a3, a4, b2, b3, b4, c2, c3, c4));
}

double
Matrix::trace() const
{
  return data_[0] + data_[5] + data_[10] + data_[15];
}

bool
Matrix::invert()
{
  bool         result(false);
  double const d(determinant());
  
  if (0.0 != d) {
    double const& a1(data_[ 0]);
    double const& b1(data_[ 4]);
    double const& c1(data_[ 8]);
    double const& d1(data_[12]);
    double const& a2(data_[ 1]);
    double const& b2(data_[ 5]);
    double const& c2(data_[ 9]);
    double const& d2(data_[13]);
    double const& a3(data_[ 2]);
    double const& b3(data_[ 6]);
    double const& c3(data_[10]);
    double const& d3(data_[14]);
    double const& a4(data_[ 3]);
    double const& b4(data_[ 7]);
    double const& c4(data_[11]);
    double const& d4(data_[15]);
    
    double const di(1.0 / d);
    
    Matrix tmp;

    tmp.data_[ 0] =  det3_helper(b2, b3, b4, c2, c3, c4, d2, d3, d4) * di;
    tmp.data_[ 1] = -det3_helper(a2, a3, a4, c2, c3, c4, d2, d3, d4) * di;
    tmp.data_[ 2] =  det3_helper(a2, a3, a4, b2, b3, b4, d2, d3, d4) * di;
    tmp.data_[ 3] = -det3_helper(a2, a3, a4, b2, b3, b4, c2, c3, c4) * di;
    tmp.data_[ 4] = -det3_helper(b1, b3, b4, c1, c3, c4, d1, d3, d4) * di;
    tmp.data_[ 5] =  det3_helper(a1, a3, a4, c1, c3, c4, d1, d3, d4) * di;
    tmp.data_[ 6] = -det3_helper(a1, a3, a4, b1, b3, b4, d1, d3, d4) * di;
    tmp.data_[ 7] =  det3_helper(a1, a3, a4, b1, b3, b4, c1, c3, c4) * di;
    tmp.data_[ 8] =  det3_helper(b1, b2, b4, c1, c2, c4, d1, d2, d4) * di;
    tmp.data_[ 9] = -det3_helper(a1, a2, a4, c1, c2, c4, d1, d2, d4) * di;
    tmp.data_[10] =  det3_helper(a1, a2, a4, b1, b2, b4, d1, d2, d4) * di;
    tmp.data_[11] = -det3_helper(a1, a2, a4, b1, b2, b4, c1, c2, c4) * di;
    tmp.data_[12] = -det3_helper(b1, b2, b3, c1, c2, c3, d1, d2, d3) * di;
    tmp.data_[13] =  det3_helper(a1, a2, a3, c1, c2, c3, d1, d2, d3) * di;
    tmp.data_[14] = -det3_helper(a1, a2, a3, b1, b2, b3, d1, d2, d3) * di;
    tmp.data_[15] =  det3_helper(a1, a2, a3, b1, b2, b3, c1, c2, c3) * di;
    
    swap(tmp);
    
    result = true;
  }
  return result;
}

void
Matrix::transpose()
{
  Matrix tmp(*this);

  // data_[ 0] = tmp.data_[ 0];
  data_[ 1] = tmp.data_[ 4];
  data_[ 2] = tmp.data_[ 8];
  data_[ 3] = tmp.data_[12];
  data_[ 4] = tmp.data_[ 1];
  // data_[ 5] = tmp.data_[ 5];
  data_[ 6] = tmp.data_[ 9];
  data_[ 7] = tmp.data_[13];
  data_[ 8] = tmp.data_[ 2];
  data_[ 9] = tmp.data_[ 6];
  // data_[10] = tmp.data_[10];
  data_[11] = tmp.data_[14];
  data_[12] = tmp.data_[ 3];
  data_[13] = tmp.data_[ 7];
  data_[14] = tmp.data_[11];
  // data_[15] = tmp.data_[15];
}

bool
Matrix::is_invertible() const
{
  return 0 != determinant();
}

/* static */
Matrix const& 
Matrix::null()
{
  static Matrix null_(null_array16);
  return null_;
}

/* static */
Matrix const& 
Matrix::identity()
{
  static Matrix identity_(ident_array16);
  return identity_;
}

Matrix
operator-(Matrix const& rhs)
{
  return Matrix(rhs) *= -1.0;
}

Matrix
operator*(Matrix const& lhs, Matrix const& rhs)
{
  return Matrix(lhs) *= rhs;
}

Matrix
operator*(Matrix const& lhs, double rhs)
{
  return Matrix(lhs) *= rhs;
}

Matrix
operator*(double lhs, Matrix const& rhs)
{
  return Matrix(rhs) *= lhs;
}

Matrix
operator/(Matrix const& lhs, double rhs)
{
  return Matrix(lhs) /= rhs;
}

Point
operator*(Matrix const& lhs, const Point& rhs)
{
  return Point(lhs[0] * rhs[0] +
               lhs[4] * rhs[1] +
               lhs[8] * rhs[2] +
               lhs[12] * rhs[3],
               lhs[1] * rhs[0] +
               lhs[5] * rhs[1] +
               lhs[9] * rhs[2] +
               lhs[13] * rhs[3],
               lhs[2] * rhs[0] +
               lhs[6] * rhs[1] +
               lhs[10] * rhs[2] +
               lhs[14] * rhs[3],
               lhs[3] * rhs[0] +
               lhs[7] * rhs[1] +
               lhs[11] * rhs[2] +
               lhs[15] * rhs[3]);
}

Vector
operator*(Matrix const& lhs, const Vector& rhs)
{
  return Vector(lhs[0] * rhs[0] +
                lhs[4] * rhs[1] +
                lhs[8] * rhs[2] +
                lhs[12] * rhs[3],
                lhs[1] * rhs[0] +
                lhs[5] * rhs[1] +
                lhs[9] * rhs[2] +
                lhs[13] * rhs[3],
                lhs[2] * rhs[0] +
                lhs[6] * rhs[1] +
                lhs[10] * rhs[2] +
                lhs[14] * rhs[3],
                lhs[3] * rhs[0] +
                lhs[7] * rhs[1] +
                lhs[11] * rhs[2] +
                lhs[15] * rhs[3]);
}

bool 
operator==(Matrix const& lhs, Matrix const& rhs)
{
return (std::fabs(lhs[0] - rhs[0]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[4] - rhs[4]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[8] - rhs[8]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[12] - rhs[12]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[0] - rhs[0]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[4] - rhs[4]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[8] - rhs[8]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[12] - rhs[12]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[0] - rhs[0]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[4] - rhs[4]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[8] - rhs[8]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[12] - rhs[12]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[0] - rhs[0]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[4] - rhs[4]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[8] - rhs[8]) < std::numeric_limits<double>::epsilon() &&
        std::fabs(lhs[12] - rhs[12]) < std::numeric_limits<double>::epsilon());  
}

Matrix
make_translation(double a, double b, double c)
{
  Matrix tmp;
  tmp[12] = a;
  tmp[13] = b;
  tmp[14] = c;
  return tmp;
}

Matrix
make_translation(Vector const& a)
{
  return make_translation(a[0], a[1], a[2]);
}

Matrix
make_scale(double a, double b, double c)
{
  Matrix tmp;

  tmp[0] = a;
  tmp[5] = b;
  tmp[10] = c;
  
  return tmp;
}

Matrix
make_scale(Vector const& a)
{
  return make_scale(a[0], a[1], a[2]);
}

Matrix
make_rotation_x(double a)
{
  double const cos_a(std::cos(a));
  double const sin_a(std::sin(a));
  
  Matrix tmp;

  tmp[5] =  cos_a;
  tmp[9] =  sin_a;
  tmp[6] = -sin_a;
  tmp[10] =  cos_a;
  
  return tmp;
}

Matrix
make_rotation_y(double a)
{
  double const cos_a(std::cos(a));
  double const sin_a(std::sin(a));
  
  Matrix tmp;

  tmp[0] =  cos_a;
  tmp[8] = -sin_a;
  tmp[2] =  sin_a;
  tmp[10] =  cos_a;
  
  return tmp;
}

Matrix
make_rotation_z(double a)
{
  double const cos_a(std::cos(a));
  double const sin_a(std::sin(a));
  
  Matrix tmp;

  tmp[0] =  cos_a;
  tmp[4] =  sin_a;
  tmp[1] = -sin_a;
  tmp[5] =  cos_a;
  
  return tmp;
}

double
determinant(Matrix const& a)
{
  return a.determinant();
}

double
trace(Matrix const& a)
{
  return a.trace();
}

Matrix
inverse(Matrix const& a)
{
  Matrix tmp(a);

  tmp.invert();
  
  return tmp;
}

Matrix
transpose(Matrix const& a)
{
  Matrix tmp(a);

  tmp.transpose();
  
  return tmp;
}

bool
is_invertible(Matrix const& a)
{
  return a.is_invertible();
}

std::ostream&
operator<<(std::ostream& os, Matrix const& a)
{
  std::ostream::sentry const cerberus(os);

  if (cerberus) {
    os << std::fixed << std::setprecision(3)
       << '['
       << a[0] << ','
       << a[4] << ','
       << a[8] << ','
       << a[12] << ','
       << std::endl
       << ' '
       << a[1] << ','
       << a[5] << ','
       << a[9] << ','
       << a[13] << ','
       << std::endl
       << ' '
       << a[2] << ','
       << a[6] << ','
       << a[10] << ','
       << a[14] << ','
       << std::endl
       << ' '
       << a[3] << ','
       << a[7] << ','
       << a[11] << ','
       << a[15]
       << ']';
  }

  return os;
}

} // namespace math3d {
