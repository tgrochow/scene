// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2013 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  matrix.hpp                                                                      */
/*  project    :  lectures in programming && software engineering                                 */
/*  description:  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(BUW_MATH3D_Matrix_HPP)
#define BUW_MATH3D_Matrix_HPP

#include <iosfwd> // fwd. decl: std::ostream
#include "vector.hpp"

namespace math3d 
{

	class Point;

	class Matrix 
	{

		public:
	  	Matrix();
	  	Matrix(double const [16]);

	  	void swap(Matrix&);
  
	  
	  	double const& operator[](unsigned) const;
	  	double&       operator[](unsigned);
	  	Matrix& operator*=(Matrix const&);
	  	Matrix& operator*=(double);
	  	Matrix& operator/=(double);
  
	  	double determinant() const;
	  	double trace() const;

	  	bool invert();
	  	void transpose();

	  	bool is_invertible() const; // det(M) != 0

	  	static Matrix const& null();     
		// m[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
 	 	static Matrix const& identity(); 
		// m[[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]]
  
		private:
	  	double data_[16];
	};

	// variables, exported (extern)

	// functions, inlined (inline)

	// functions, exported (extern)

	Matrix operator-(Matrix const&);

	Matrix operator*(Matrix const&, Matrix const&);
	Matrix operator*(Matrix const&, double);
	Matrix operator*(double, Matrix const&);
	Matrix operator/(Matrix const&, double);

	Point  operator*(Matrix const&, Point const&);
	Vector operator*(Matrix const&, Vector const&);

	bool operator==(Matrix const&, Matrix const&);

	Matrix make_translation(double, double, double);
	Matrix make_translation(Vector const&);

	Matrix make_scale(double, double, double);
	Matrix make_scale(Vector const&);

	Matrix make_rotation_x(double);
	Matrix make_rotation_y(double);
	Matrix make_rotation_z(double);

	double determinant(Matrix const&);
	double trace(Matrix const&);
	Matrix inverse(Matrix const&);
	Matrix transpose(Matrix const&);

	bool is_invertible(Matrix const&);

	std::ostream& operator<<(std::ostream&, Matrix const&);

} // namespace math3d {

#endif // #if !defined(BUW_MATH3D_Matrix_HPP)
