/**
*	@file	Matrix.hpp
*	@brief	
*	@date	2011.6.13(Mon) 11:38
*/

#ifndef INCLUDED_MATRIX_HPP
#define INCLUDED_MATRIX_HPP

#include <math.h>
#include "Vector.hpp"


template < typename Type >
class Matrix2x2
{
public:
	union
	{
		struct
		{
			Type		m_11;
			Type		m_12;
			Type		m_21;
			Type		m_22;
		};
		Type	m_Elm[ 2 ][ 2 ];
	};

	//Constructor (1)
	Matrix2x2();
	//Constructor (2)
	Matrix2x2( const Matrix2x2 < Type >& m );
	//Destructor
	~Matrix2x2();
	//Add / Ternary operator (Overload of + operator)
	Matrix2x2 operator+( const Matrix2x2 < Type >& m );
	//Subtract / Ternary operator (Overload of - operator)
	Matrix2x2 operator-( const Matrix2x2 < Type >& m );
	//Multiply / Ternary operator (Overload of * operator)
	Matrix2x2 operator*( const Matrix2x2 < Type >& m );
	Matrix2x2& operator=( const Matrix2x2 < Type >& m );
	//Equivalence (Overload of = operator)
	bool operator==( const Matrix2x2 < Type >& m );
	//Add / Binary operator (Overload of += operator)
	Matrix2x2& operator+=( const Matrix2x2 < Type >& m );
	//Subtract / Binary operator (Overload of -= operator)
	Matrix2x2& operator-=( const Matrix2x2 < Type >& m );
	//Multiply / Binary operator (Overload of *= operator)
	Matrix2x2& operator*=( const Matrix2x2 < Type >& m );
	//Add
	void Add( const Matrix2x2 < Type >& m );
	//Subtract
	void Sub( const Matrix2x2 < Type >& m );
	//Multiply
	void Mul( const Matrix2x2 < Type >& m );

};

//Constructor (1)
template < typename Type >
Matrix2x2 < Type > ::Matrix2x2() : m_11( 0 ), m_12( 0 ), m_21( 0 ), m_22( 0 )
{
}

//Constructor (2)
template < typename Type >
Matrix2x2 < Type > ::Matrix2x2( const Matrix2x2 < Type >& m ) : m_11( m.m_11 ), m_12( m.m_12 ), m_21( m.m_21 ), m_22( m.m_22 )
{
}

//Destructor
template < typename Type >
Matrix2x2 < Type > ::~Matrix2x2()
{
	m_11 = 0;
	m_12 = 0;
	m_21 = 0;
	m_22 = 0;
}

//Add / Ternary operator (Overload of + operator)
template < typename Type >
Matrix2x2 < Type > Matrix2x2 < Type > ::operator+( const Matrix2x2 < Type >& m )
{
	Matrix2x2 < Type > matTmp;

	matTmp.m_11 = m_11 + m.m_11;
	matTmp.m_12 = m_12 + m.m_12;
	matTmp.m_21 = m_21 + m.m_21;
	matTmp.m_22 = m_22 + m.m_22;

	return matTmp;
}

//Subtract / Ternary operator (Overload of - operator)
template < typename Type >
Matrix2x2 < Type > Matrix2x2 < Type > ::operator-( const Matrix2x2 < Type >& m )
{
	Matrix2x2 < Type > matTmp;

	matTmp.m_11 = m_11 - m.m_11;
	matTmp.m_12 = m_12 - m.m_12;
	matTmp.m_21 = m_21 - m.m_21;
	matTmp.m_22 = m_22 - m.m_22;

	return matTmp;
}

//Multiply / Ternary operator (Overload of * operator)
template < typename Type >
Matrix2x2 < Type > Matrix2x2 < Type > ::operator*( const Matrix2x2 < Type >& m )
{
	Matrix2x2 < Type > matTmp;

	matTmp.m_11 = m_11 * m.m_11 + m_12 * m.m_21;
	matTmp.m_12 = m_11 * m.m_12 + m_12 * m.m_22;
	matTmp.m_21 = m_21 * m.m_11 + m_22 * m.m_21;
	matTmp.m_22 = m_21 * m.m_12 + m_22 * m.m_22;

	return matTmp;
}

template < typename Type >
Matrix2x2 < Type >& Matrix2x2 < Type > ::operator=( const Matrix2x2 < Type >& m )
{
	this->m_11 = m.m_11;
	this->m_12 = m.m_12;
	this->m_21 = m.m_21;
	this->m_22 = m.m_22;

	return *this;
}

//Equivalence (Overload of = operator)
template < typename Type >
bool Matrix2x2 < Type > ::operator==( const Matrix2x2 < Type >& m )
{
	int result = 1;

	result &= ( m_11 == m.m_11 );
	result &= ( m_12 == m.m_12 );
	result &= ( m_21 == m.m_21 );
	result &= ( m_22 == m.m_22 );

	return result ? true : false;
}

//Add / Binary operator (Overload of += operator)
template < typename Type >
Matrix2x2 < Type >& Matrix2x2 < Type > ::operator+=( const Matrix2x2 < Type >& m )
{
	m_11 += m.m_11;
	m_12 += m.m_12;
	m_21 += m.m_21;
	m_22 += m.m_22;

	return *this;
}

//Subtract / Binary operator (Overload of -= operator)
template < typename Type >
Matrix2x2 < Type >& Matrix2x2 < Type > ::operator-=( const Matrix2x2 < Type >& m )
{
	m_11 -= m.m_11;
	m_12 -= m.m_12;
	m_21 -= m.m_21;
	m_22 -= m.m_22;

	return *this;
}

//Multiply / Binary operator (Overload of *= operator)
template < typename Type >
Matrix2x2 < Type >& Matrix2x2 < Type > ::operator*=( const Matrix2x2 < Type >& m )
{
	Matrix2x2 < Type > matTmp = *this;

	m_11 = matTmp.m_11 * m.m_11 + matTmp.m_12 * m.m_21;
	m_12 = matTmp.m_11 * m.m_12 + matTmp.m_12 * m.m_22;
	m_21 = matTmp.m_21 * m.m_11 + matTmp.m_22 * m.m_21;
	m_22 = matTmp.m_21 * m.m_12 + matTmp.m_22 * m.m_22;

	return *this;
}

//Add
template < typename Type >
void Matrix2x2 < Type > ::Add( const Matrix2x2 < Type >& m )
{
	m_11 += m.m_11;
	m_12 += m.m_12;
	m_21 += m.m_21;
	m_22 += m.m_22;
}

//Subtract
template < typename Type >
void Matrix2x2 < Type > ::Sub( const Matrix2x2 < Type >& m )
{
	m_11 -= m.m_11;
	m_12 -= m.m_12;
	m_21 -= m.m_21;
	m_22 -= m.m_22;
}

//Multiply
template < typename Type >
void Matrix2x2 < Type > ::Mul( const Matrix2x2 < Type >& m )
{
	Matrix2x2 < Type > matTmp = *this;

	m_11 = matTmp.m_11 * m.m_11 + matTmp.m_12 * m.m_21;
	m_12 = matTmp.m_11 * m.m_12 + matTmp.m_12 * m.m_22;
	m_21 = matTmp.m_21 * m.m_11 + matTmp.m_22 * m.m_21;
	m_22 = matTmp.m_21 * m.m_12 + matTmp.m_22 * m.m_22;
}

template < typename Type >
class Matrix3x3
{
public:
	union
	{
		struct
		{
			Type		m_11;
			Type		m_12;
			Type		m_13;
			Type		m_21;
			Type		m_22;
			Type		m_23;
			Type		m_31;
			Type		m_32;
			Type		m_33;
		};
		Type	m_Elm[ 3 ][ 3 ];
	};

	//Constructor (1)
	Matrix3x3();
	//Constructor (2)
	Matrix3x3( const Matrix3x3 < Type >& m );
	//Destructor
	~Matrix3x3();
	//Add / Ternary operator (Overload of + operator)
	Matrix3x3 operator+( const Matrix3x3 < Type >& m );
	//Subtract / Ternary operator (Overload of - operator)
	Matrix3x3 operator-( const Matrix3x3 < Type >& m );
	//Multiply / Ternary operator (Overload of * operator)
	Matrix3x3 operator*( const Matrix3x3 < Type >& m );
	Matrix3x3& operator=( const Matrix3x3 < Type >& m );
	//Equivalence (Overload of = operator)
	bool operator==( const Matrix3x3 < Type >& m );
	//Add / Binary operator (Overload of += operator)
	Matrix3x3& operator+=( const Matrix3x3 < Type >& m );
	//Subtract / Binary operator (Overload of -= operator)
	Matrix3x3& operator-=( const Matrix3x3 < Type >& m );
	//Multiply / Binary operator (Overload of * operator)
	Matrix3x3& operator*=( const Matrix3x3 < Type >& m );
	//Add
	void Add( const Matrix3x3 < Type >& m );
	//Subtract
	void Sub( const Matrix3x3 < Type >& m );
	//Multiply
	void Mul( const Matrix3x3 < Type >& m );

};

//Constructor (1)
template < typename Type >
Matrix3x3 < Type > ::Matrix3x3() :	m_11( 0 ), m_12( 0 ), m_13( 0 ),
									m_21( 0 ), m_22( 0 ), m_23( 0 ),
									m_31( 0 ), m_32( 0 ), m_33( 0 )
{
}

//Constructor (2)
template < typename Type >
Matrix3x3 < Type > ::Matrix3x3( const Matrix3x3 < Type >& m ) :	m_11( m.m_11 ), m_12( m.m_12 ), m_13( m.m_13 ),
																m_21( m.m_21 ), m_22( m.m_22 ), m_23( m.m_23 ),
																m_31( m.m_31 ), m_32( m.m_32 ), m_33( m.m_33 )
{
}

//Destructor
template < typename Type >
Matrix3x3 < Type > ::~Matrix3x3()
{
	m_11 = 0;
	m_12 = 0;
	m_13 = 0;
	m_21 = 0;
	m_22 = 0;
	m_23 = 0;
	m_31 = 0;
	m_32 = 0;
	m_33 = 0;
}

//Add / Ternary operator (Overload of + operator)
template < typename Type >
Matrix3x3 < Type > Matrix3x3 < Type > ::operator+( const Matrix3x3 < Type >& m )
{
	Matrix3x3 < Type > matTmp;

	matTmp.m_11 = m_11 + m.m_11;
	matTmp.m_12 = m_12 + m.m_12;
	matTmp.m_13 = m_13 + m.m_13;
	matTmp.m_21 = m_21 + m.m_21;
	matTmp.m_22 = m_22 + m.m_22;
	matTmp.m_23 = m_23 + m.m_23;
	matTmp.m_31 = m_31 + m.m_31;
	matTmp.m_32 = m_32 + m.m_32;
	matTmp.m_33 = m_33 + m.m_33;

	return matTmp;
}

//Subtract / Ternary operator (Overload of - operator)
template < typename Type >
Matrix3x3 < Type > Matrix3x3 < Type > ::operator-( const Matrix3x3 < Type >& m )
{
	Matrix3x3 < Type > matTmp;

	matTmp.m_11 = m_11 - m.m_11;
	matTmp.m_12 = m_12 - m.m_12;
	matTmp.m_13 = m_13 - m.m_13;
	matTmp.m_21 = m_21 - m.m_21;
	matTmp.m_22 = m_22 - m.m_22;
	matTmp.m_23 = m_23 - m.m_23;
	matTmp.m_31 = m_31 - m.m_31;
	matTmp.m_32 = m_32 - m.m_32;
	matTmp.m_33 = m_33 - m.m_33;

	return matTmp;
}

//Multiply / Ternary operator (Overload of * operator)
template < typename Type >
Matrix3x3 < Type > Matrix3x3 < Type > ::operator*( const Matrix3x3 < Type >& m )
{
	Matrix3x3 < Type > matTmp;

	matTmp.m_11 = m_11 * m.m_11 + m_12 * m.m_21 + m_13 * m.m_31;
	matTmp.m_12 = m_11 * m.m_12 + m_12 * m.m_22 + m_13 * m.m_32;
	matTmp.m_13 = m_11 * m.m_13 + m_12 * m.m_23 + m_13 * m.m_33;

	matTmp.m_21 = m_21 * m.m_11 + m_22 * m.m_21 + m_23 * m.m_31;
	matTmp.m_22 = m_21 * m.m_12 + m_22 * m.m_22 + m_23 * m.m_32;
	matTmp.m_23 = m_21 * m.m_13 + m_22 * m.m_23 + m_23 * m.m_33;

	matTmp.m_31 = m_31 * m.m_11 + m_32 * m.m_21 + m_33 * m.m_31;
	matTmp.m_32 = m_31 * m.m_12 + m_32 * m.m_22 + m_33 * m.m_32;
	matTmp.m_33 = m_31 * m.m_13 + m_32 * m.m_23 + m_33 * m.m_33;

	return matTmp;
}

template < typename Type >
Matrix3x3 < Type >& Matrix3x3 < Type > ::operator=( const Matrix3x3 < Type >& m )
{
	this->m_11 = m.m_11;
	this->m_12 = m.m_12;
	this->m_13 = m.m_13;
	this->m_21 = m.m_21;
	this->m_22 = m.m_22;
	this->m_23 = m.m_23;
	this->m_31 = m.m_31;
	this->m_32 = m.m_32;
	this->m_33 = m.m_33;

	return *this;
}

//Equivalence (Overload of = operator)
template < typename Type >
bool Matrix3x3 < Type > ::operator==( const Matrix3x3 < Type >& m )
{
	int result = 1;

	result &= ( m_11 == m.m_11 );
	result &= ( m_12 == m.m_12 );
	result &= ( m_13 == m.m_13 );
	result &= ( m_21 == m.m_21 );
	result &= ( m_22 == m.m_22 );
	result &= ( m_23 == m.m_23 );
	result &= ( m_31 == m.m_31 );
	result &= ( m_32 == m.m_32 );
	result &= ( m_33 == m.m_33 );

	return result ? true : false;
}

//Add / Binary operator (Overload of += operator)
template < typename Type >
Matrix3x3 < Type >& Matrix3x3 < Type > ::operator+=( const Matrix3x3 < Type >& m )
{
	m_11 += m.m_11;
	m_12 += m.m_12;
	m_13 += m.m_13;
	m_21 += m.m_21;
	m_22 += m.m_22;
	m_23 += m.m_23;
	m_31 += m.m_31;
	m_32 += m.m_32;
	m_33 += m.m_33;

	return *this;
}

//Subtract / Binary operator (Overload of -= operator)
template < typename Type >
Matrix3x3 < Type >& Matrix3x3 < Type > ::operator-=( const Matrix3x3 < Type >& m )
{
	m_11 -= m.m_11;
	m_12 -= m.m_12;
	m_13 -= m.m_13;
	m_21 -= m.m_21;
	m_22 -= m.m_22;
	m_23 -= m.m_23;
	m_31 -= m.m_31;
	m_32 -= m.m_32;
	m_33 -= m.m_33;

	return *this;
}

//Multiply / Binary operator (Overload of * operator)
template < typename Type >
Matrix3x3 < Type >& Matrix3x3 < Type > ::operator*=( const Matrix3x3 < Type >& m )
{
	Matrix3x3 < Type > matTmp = *this;

	m_11 = matTmp.m_11 * m.m_11 + matTmp.m_12 * m.m_21 + matTmp.m_13 * m.m_31;
	m_12 = matTmp.m_11 * m.m_12 + matTmp.m_12 * m.m_22 + matTmp.m_13 * m.m_32;
	m_13 = matTmp.m_11 * m.m_13 + matTmp.m_12 * m.m_23 + matTmp.m_13 * m.m_33;

	m_21 = matTmp.m_21 * m.m_11 + matTmp.m_22 * m.m_21 + matTmp.m_23 * m.m_31;
	m_22 = matTmp.m_21 * m.m_12 + matTmp.m_22 * m.m_22 + matTmp.m_23 * m.m_32;
	m_23 = matTmp.m_21 * m.m_13 + matTmp.m_22 * m.m_23 + matTmp.m_23 * m.m_33;

	m_31 = matTmp.m_31 * m.m_11 + matTmp.m_32 * m.m_21 + matTmp.m_33 * m.m_31;
	m_32 = matTmp.m_31 * m.m_12 + matTmp.m_32 * m.m_22 + matTmp.m_33 * m.m_32;
	m_33 = matTmp.m_31 * m.m_13 + matTmp.m_32 * m.m_23 + matTmp.m_33 * m.m_33;

	return *this;
}

//Add
template < typename Type >
void Matrix3x3 < Type > ::Add( const Matrix3x3 < Type >& m )
{
	m_11 += m.m_11;
	m_12 += m.m_12;
	m_13 += m.m_13;
	m_21 += m.m_21;
	m_22 += m.m_22;
	m_23 += m.m_23;
	m_31 += m.m_31;
	m_32 += m.m_32;
	m_33 += m.m_33;
}

//Subtract
template < typename Type >
void Matrix3x3 < Type > ::Sub( const Matrix3x3 < Type >& m )
{
	m_11 -= m.m_11;
	m_12 -= m.m_12;
	m_13 -= m.m_13;
	m_21 -= m.m_21;
	m_22 -= m.m_22;
	m_23 -= m.m_23;
	m_31 -= m.m_31;
	m_32 -= m.m_32;
	m_33 -= m.m_33;
}

//Multiply
template < typename Type >
void Matrix3x3 < Type > ::Mul( const Matrix3x3 < Type >& m )
{
	Matrix3x3 < Type > matTmp = *this;

	m_11 = matTmp.m_11 * m.m_11 + matTmp.m_12 * m.m_21 + matTmp.m_13 * m.m_31;
	m_12 = matTmp.m_11 * m.m_12 + matTmp.m_12 * m.m_22 + matTmp.m_13 * m.m_32;
	m_13 = matTmp.m_11 * m.m_13 + matTmp.m_12 * m.m_23 + matTmp.m_13 * m.m_33;

	m_21 = matTmp.m_21 * m.m_11 + matTmp.m_22 * m.m_21 + matTmp.m_23 * m.m_31;
	m_22 = matTmp.m_21 * m.m_12 + matTmp.m_22 * m.m_22 + matTmp.m_23 * m.m_32;
	m_23 = matTmp.m_21 * m.m_13 + matTmp.m_22 * m.m_23 + matTmp.m_23 * m.m_33;

	m_31 = matTmp.m_31 * m.m_11 + matTmp.m_32 * m.m_21 + matTmp.m_33 * m.m_31;
	m_32 = matTmp.m_31 * m.m_12 + matTmp.m_32 * m.m_22 + matTmp.m_33 * m.m_32;
	m_33 = matTmp.m_31 * m.m_13 + matTmp.m_32 * m.m_23 + matTmp.m_33 * m.m_33;
}


template < typename Type >
class Matrix4x4
{
public:
	union
	{
		struct{
			Type		m_11;
			Type		m_12;
			Type		m_13;
			Type		m_14;
			Type		m_21;
			Type		m_22;
			Type		m_23;
			Type		m_24;
			Type		m_31;
			Type		m_32;
			Type		m_33;
			Type		m_34;
			Type		m_41;
			Type		m_42;
			Type		m_43;
			Type		m_44;
		};
		Type	m_Elm[ 4 ][ 4 ];
		Type	m_Elm1[ 16 ];
	};

	//Constructor (1)
	Matrix4x4();
	//Constructor (2)
	Matrix4x4( const Matrix4x4 < Type >& m );
	//Destructor
	~Matrix4x4();
	//Add / Ternary operator (Overload of + operator)
	Matrix4x4 operator+( const Matrix4x4 < Type >& m );
	//Subtract / Ternary operator (Overload of - operator)
	Matrix4x4 operator-( const Matrix4x4 < Type >& m );
	//Multiply / Ternary operator (Overload of * operator)
	Matrix4x4 operator*( const Matrix4x4 < Type >& m );
	// Multiply / Ternary operator ( Overload of * operator ) (2).
	Matrix4x4 operator*( Type f );
	Matrix4x4& operator=( const Matrix4x4 < Type >& m );
	//Equivalence (Overload of = operator)
	bool operator==( const Matrix4x4 < Type >& m );
	//Add / Binary operator (Overload of += operator)
	Matrix4x4& operator+=( const Matrix4x4 < Type >& m );
	//Subtract / Binary operator (Overload of -= operator)
	Matrix4x4& operator-=( const Matrix4x4 < Type >& m );
	//Multiply / Binary operator (Overload of * operator)
	Matrix4x4& operator*=( const Matrix4x4 < Type >& m );
	// Multiply / Binary operator ( Overload of * operator ) (2).
	Matrix4x4& operator*=( float f );
	//Add
	void Add( const Matrix4x4 < Type >& m );
	//Subtract
	void Sub( const Matrix4x4 < Type >& m );
	//Multiply
	void Mul( const Matrix4x4 < Type >& m );
	// Multiply (2).
	void Mul( float f );

};

//Constructor (1)
template < typename Type >
Matrix4x4 < Type > ::Matrix4x4() :	m_11( 0 ), m_12( 0 ), m_13( 0 ), m_14( 0 ),
									m_21( 0 ), m_22( 0 ), m_23( 0 ), m_24( 0 ),
									m_31( 0 ), m_32( 0 ), m_33( 0 ), m_34( 0 ),
									m_41( 0 ), m_42( 0 ), m_43( 0 ), m_44( 0 )
{
}

//Constructor (2)
template < typename Type >
Matrix4x4 < Type > ::Matrix4x4( const Matrix4x4 < Type >& m ) :	m_11( m.m_11 ), m_12( m.m_12 ), m_13( m.m_13 ), m_14( m.m_14 ),
																m_21( m.m_21 ), m_22( m.m_22 ), m_23( m.m_23 ), m_24( m.m_24 ),
																m_31( m.m_31 ), m_32( m.m_32 ), m_33( m.m_33 ), m_34( m.m_34 ),
																m_41( m.m_41 ), m_42( m.m_42 ), m_43( m.m_43 ), m_44( m.m_44 )
{
}

//Destructor
template < typename Type >
Matrix4x4 < Type > ::~Matrix4x4()
{
	m_11 = 0;
	m_12 = 0;
	m_13 = 0;
	m_14 = 0;
	m_21 = 0;
	m_22 = 0;
	m_23 = 0;
	m_24 = 0;
	m_31 = 0;
	m_32 = 0;
	m_33 = 0;
	m_34 = 0;
	m_41 = 0;
	m_42 = 0;
	m_43 = 0;
	m_44 = 0;
}

//Add / Ternary operator (Overload of + operator)
template < typename Type >
Matrix4x4 < Type > Matrix4x4 < Type > ::operator+( const Matrix4x4 < Type >& m )
{
	Matrix4x4 < Type > matTmp;

	matTmp.m_11 = m_11 + m.m_11;
	matTmp.m_12 = m_12 + m.m_12;
	matTmp.m_13 = m_13 + m.m_13;
	matTmp.m_14 = m_14 + m.m_14;
	matTmp.m_21 = m_21 + m.m_21;
	matTmp.m_22 = m_22 + m.m_22;
	matTmp.m_23 = m_23 + m.m_23;
	matTmp.m_24 = m_24 + m.m_24;
	matTmp.m_31 = m_31 + m.m_31;
	matTmp.m_32 = m_32 + m.m_32;
	matTmp.m_33 = m_33 + m.m_33;
	matTmp.m_34 = m_34 + m.m_34;
	matTmp.m_41 = m_41 + m.m_41;
	matTmp.m_42 = m_42 + m.m_42;
	matTmp.m_43 = m_43 + m.m_43;
	matTmp.m_44 = m_44 + m.m_44;

	return matTmp;
}

//Subtract / Ternary operator (Overload of - operator)
template < typename Type >
Matrix4x4 < Type > Matrix4x4 < Type > ::operator-( const Matrix4x4 < Type >& m )
{
	Matrix4x4 < Type > matTmp;

	matTmp.m_11 = m_11 - m.m_11;
	matTmp.m_12 = m_12 - m.m_12;
	matTmp.m_13 = m_13 - m.m_13;
	matTmp.m_14 = m_14 - m.m_14;
	matTmp.m_21 = m_21 - m.m_21;
	matTmp.m_22 = m_22 - m.m_22;
	matTmp.m_23 = m_23 - m.m_23;
	matTmp.m_24 = m_24 - m.m_24;
	matTmp.m_31 = m_31 - m.m_31;
	matTmp.m_32 = m_32 - m.m_32;
	matTmp.m_33 = m_33 - m.m_33;
	matTmp.m_34 = m_34 - m.m_34;
	matTmp.m_41 = m_41 - m.m_41;
	matTmp.m_42 = m_42 - m.m_42;
	matTmp.m_43 = m_43 - m.m_43;
	matTmp.m_44 = m_44 - m.m_44;

	return matTmp;
}

//Multiply / Ternary operator (Overload of * operator)
template < typename Type >
Matrix4x4 < Type > Matrix4x4 < Type > ::operator*( const Matrix4x4 < Type >& m )
{
	Matrix4x4 < Type > matTmp;

	matTmp.m_11 = m_11 * m.m_11 + m_12 * m.m_21 + m_13 * m.m_31 + m_14 * m.m_41;
	matTmp.m_12 = m_11 * m.m_12 + m_12 * m.m_22 + m_13 * m.m_32 + m_14 * m.m_42;
	matTmp.m_13 = m_11 * m.m_13 + m_12 * m.m_23 + m_13 * m.m_33 + m_14 * m.m_43;
	matTmp.m_14 = m_11 * m.m_14 + m_12 * m.m_24 + m_13 * m.m_34 + m_14 * m.m_44;

	matTmp.m_21 = m_21 * m.m_11 + m_22 * m.m_21 + m_23 * m.m_31 + m_24 * m.m_41;
	matTmp.m_22 = m_21 * m.m_12 + m_22 * m.m_22 + m_23 * m.m_32 + m_24 * m.m_42;
	matTmp.m_23 = m_21 * m.m_13 + m_22 * m.m_23 + m_23 * m.m_33 + m_24 * m.m_43;
	matTmp.m_24 = m_21 * m.m_14 + m_22 * m.m_24 + m_23 * m.m_34 + m_24 * m.m_44;

	matTmp.m_31 = m_31 * m.m_11 + m_32 * m.m_21 + m_33 * m.m_31 + m_34 * m.m_41;
	matTmp.m_32 = m_31 * m.m_12 + m_32 * m.m_22 + m_33 * m.m_32 + m_34 * m.m_42;
	matTmp.m_33 = m_31 * m.m_13 + m_32 * m.m_23 + m_33 * m.m_33 + m_34 * m.m_43;
	matTmp.m_34 = m_31 * m.m_14 + m_32 * m.m_24 + m_33 * m.m_34 + m_34 * m.m_44;

	matTmp.m_41 = m_41 * m.m_11 + m_42 * m.m_21 + m_43 * m.m_31 + m_44 * m.m_41;
	matTmp.m_42 = m_41 * m.m_12 + m_42 * m.m_22 + m_43 * m.m_32 + m_44 * m.m_42;
	matTmp.m_43 = m_41 * m.m_13 + m_42 * m.m_23 + m_43 * m.m_33 + m_44 * m.m_43;
	matTmp.m_44 = m_41 * m.m_14 + m_42 * m.m_24 + m_43 * m.m_34 + m_44 * m.m_44;

	return matTmp;
}

// Multiply / Ternary operator ( Overload of * operator ) (2).
template < typename Type >
Matrix4x4 < Type > Matrix4x4 < Type > ::operator*( Type f )
{
	m_11 = m_11 * f;
	m_12 = m_12 * f;
	m_13 = m_13 * f;
	m_14 = m_14 * f;
	m_21 = m_21 * f;
	m_22 = m_22 * f;
	m_23 = m_23 * f;
	m_24 = m_24 * f;
	m_31 = m_31 * f;
	m_32 = m_32 * f;
	m_33 = m_33 * f;
	m_34 = m_34 * f;
	m_41 = m_41 * f;
	m_42 = m_42 * f;
	m_43 = m_43 * f;
	m_44 = m_44 * f;
}

template < typename Type >
Matrix4x4 < Type >& Matrix4x4 < Type > ::operator=( const Matrix4x4 < Type >& m )
{
	this->m_11 = m.m_11;
	this->m_12 = m.m_12;
	this->m_13 = m.m_13;
	this->m_14 = m.m_14;
	this->m_21 = m.m_21;
	this->m_22 = m.m_22;
	this->m_23 = m.m_23;
	this->m_24 = m.m_24;
	this->m_31 = m.m_31;
	this->m_32 = m.m_32;
	this->m_33 = m.m_33;
	this->m_34 = m.m_34;
	this->m_41 = m.m_41;
	this->m_42 = m.m_42;
	this->m_43 = m.m_43;
	this->m_44 = m.m_44;

	return *this;
}

//Equivalence (Overload of = operator)
template < typename Type >
bool Matrix4x4 < Type > ::operator==( const Matrix4x4 < Type >& m )
{
	int result = 1;

	result &= ( m_11 == m.m_11 );
	result &= ( m_12 == m.m_12 );
	result &= ( m_13 == m.m_13 );
	result &= ( m_14 == m.m_14 );
	result &= ( m_21 == m.m_21 );
	result &= ( m_22 == m.m_22 );
	result &= ( m_23 == m.m_23 );
	result &= ( m_24 == m.m_24 );
	result &= ( m_31 == m.m_31 );
	result &= ( m_32 == m.m_32 );
	result &= ( m_33 == m.m_33 );
	result &= ( m_34 == m.m_34 );
	result &= ( m_41 == m.m_41 );
	result &= ( m_42 == m.m_42 );
	result &= ( m_43 == m.m_43 );
	result &= ( m_44 == m.m_44 );

	return result ? true : false;
}

//Add / Binary operator (Overload of += operator)
template < typename Type >
Matrix4x4 < Type >& Matrix4x4 < Type > ::operator+=( const Matrix4x4 < Type >& m )
{
	m_11 += m.m_11;
	m_12 += m.m_12;
	m_13 += m.m_13;
	m_14 += m.m_14;
	m_21 += m.m_21;
	m_22 += m.m_22;
	m_23 += m.m_23;
	m_24 += m.m_24;
	m_31 += m.m_31;
	m_32 += m.m_32;
	m_33 += m.m_33;
	m_34 += m.m_34;
	m_41 += m.m_41;
	m_42 += m.m_42;
	m_43 += m.m_43;
	m_44 += m.m_44;

	return *this;
}

//Subtract / Binary operator (Overload of -= operator)
template < typename Type >
Matrix4x4 < Type >& Matrix4x4 < Type > ::operator-=( const Matrix4x4 < Type >& m )
{
	m_11 -= m.m_11;
	m_12 -= m.m_12;
	m_13 -= m.m_13;
	m_14 -= m.m_14;
	m_21 -= m.m_21;
	m_22 -= m.m_22;
	m_23 -= m.m_23;
	m_24 -= m.m_24;
	m_31 -= m.m_31;
	m_32 -= m.m_32;
	m_33 -= m.m_33;
	m_34 -= m.m_34;
	m_41 -= m.m_41;
	m_42 -= m.m_42;
	m_43 -= m.m_43;
	m_44 -= m.m_44;

	return *this;
}

//Multiply / Binary operator (Overload of * operator)
template < typename Type >
Matrix4x4 < Type >& Matrix4x4 < Type > ::operator*=( const Matrix4x4 < Type >& m )
{
	Matrix4x4 < Type > matTmp = *this;

	m_11 = matTmp.m_11 * m.m_11 + matTmp.m_12 * m.m_21 + matTmp.m_13 * m.m_31 + matTmp.m_14 * m.m_41;
	m_12 = matTmp.m_11 * m.m_12 + matTmp.m_12 * m.m_22 + matTmp.m_13 * m.m_32 + matTmp.m_14 * m.m_42;
	m_13 = matTmp.m_11 * m.m_13 + matTmp.m_12 * m.m_23 + matTmp.m_13 * m.m_33 + matTmp.m_14 * m.m_43;
	m_14 = matTmp.m_11 * m.m_14 + matTmp.m_12 * m.m_24 + matTmp.m_13 * m.m_34 + matTmp.m_14 * m.m_44;

	m_21 = matTmp.m_21 * m.m_11 + matTmp.m_22 * m.m_21 + matTmp.m_23 * m.m_31 + matTmp.m_24 * m.m_41;
	m_22 = matTmp.m_21 * m.m_12 + matTmp.m_22 * m.m_22 + matTmp.m_23 * m.m_32 + matTmp.m_24 * m.m_42;
	m_23 = matTmp.m_21 * m.m_13 + matTmp.m_22 * m.m_23 + matTmp.m_23 * m.m_33 + matTmp.m_24 * m.m_43;
	m_24 = matTmp.m_21 * m.m_14 + matTmp.m_22 * m.m_24 + matTmp.m_23 * m.m_34 + matTmp.m_24 * m.m_44;

	m_31 = matTmp.m_31 * m.m_11 + matTmp.m_32 * m.m_21 + matTmp.m_33 * m.m_31 + matTmp.m_34 * m.m_41;
	m_32 = matTmp.m_31 * m.m_12 + matTmp.m_32 * m.m_22 + matTmp.m_33 * m.m_32 + matTmp.m_34 * m.m_42;
	m_33 = matTmp.m_31 * m.m_13 + matTmp.m_32 * m.m_23 + matTmp.m_33 * m.m_33 + matTmp.m_34 * m.m_43;
	m_34 = matTmp.m_31 * m.m_14 + matTmp.m_32 * m.m_24 + matTmp.m_33 * m.m_34 + matTmp.m_34 * m.m_44;

	m_41 = matTmp.m_41 * m.m_11 + matTmp.m_42 * m.m_21 + matTmp.m_43 * m.m_31 + matTmp.m_44 * m.m_41;
	m_42 = matTmp.m_41 * m.m_12 + matTmp.m_42 * m.m_22 + matTmp.m_43 * m.m_32 + matTmp.m_44 * m.m_42;
	m_43 = matTmp.m_41 * m.m_13 + matTmp.m_42 * m.m_23 + matTmp.m_43 * m.m_33 + matTmp.m_44 * m.m_43;
	m_44 = matTmp.m_41 * m.m_14 + matTmp.m_42 * m.m_24 + matTmp.m_43 * m.m_34 + matTmp.m_44 * m.m_44;

	return *this;
}

// Multiply / Binary operator ( Overload of * operator ) (2).
template < typename Type >
Matrix4x4 < Type >& Matrix4x4 < Type > ::operator*=( float f )
{
	m_11 *= f;
	m_12 *= f;
	m_13 *= f;
	m_14 *= f;
	m_21 *= f;
	m_22 *= f;
	m_23 *= f;
	m_24 *= f;
	m_31 *= f;
	m_32 *= f;
	m_33 *= f;
	m_34 *= f;
	m_41 *= f;
	m_42 *= f;
	m_43 *= f;
	m_44 *= f;
}

//Add
template < typename Type >
void Matrix4x4 < Type > ::Add( const Matrix4x4 < Type >& m )
{
	m_11 += m.m_11;
	m_12 += m.m_12;
	m_13 += m.m_13;
	m_14 += m.m_14;
	m_21 += m.m_21;
	m_22 += m.m_22;
	m_23 += m.m_23;
	m_24 += m.m_24;
	m_31 += m.m_31;
	m_32 += m.m_32;
	m_33 += m.m_33;
	m_34 += m.m_34;
	m_41 += m.m_41;
	m_42 += m.m_42;
	m_43 += m.m_43;
	m_44 += m.m_44;
}

//Subtract
template < typename Type >
void Matrix4x4 < Type > ::Sub( const Matrix4x4 < Type >& m )
{
	m_11 -= m.m_11;
	m_12 -= m.m_12;
	m_13 -= m.m_13;
	m_14 -= m.m_14;
	m_21 -= m.m_21;
	m_22 -= m.m_22;
	m_23 -= m.m_23;
	m_24 -= m.m_24;
	m_31 -= m.m_31;
	m_32 -= m.m_32;
	m_33 -= m.m_33;
	m_34 -= m.m_34;
	m_41 -= m.m_41;
	m_42 -= m.m_42;
	m_43 -= m.m_43;
	m_44 -= m.m_44;
}

//Multiply
template < typename Type >
void Matrix4x4 < Type > ::Mul( const Matrix4x4 < Type >& m )
{
	Matrix4x4 < Type > matTmp = *this;

	m_11 = matTmp.m_11 * m.m_11 + matTmp.m_12 * m.m_21 + matTmp.m_13 * m.m_31 + matTmp.m_14 * m.m_41;
	m_12 = matTmp.m_11 * m.m_12 + matTmp.m_12 * m.m_22 + matTmp.m_13 * m.m_32 + matTmp.m_14 * m.m_42;
	m_13 = matTmp.m_11 * m.m_13 + matTmp.m_12 * m.m_23 + matTmp.m_13 * m.m_33 + matTmp.m_14 * m.m_43;
	m_14 = matTmp.m_11 * m.m_14 + matTmp.m_12 * m.m_24 + matTmp.m_13 * m.m_34 + matTmp.m_14 * m.m_44;

	m_21 = matTmp.m_21 * m.m_11 + matTmp.m_22 * m.m_21 + matTmp.m_23 * m.m_31 + matTmp.m_24 * m.m_41;
	m_22 = matTmp.m_21 * m.m_12 + matTmp.m_22 * m.m_22 + matTmp.m_23 * m.m_32 + matTmp.m_24 * m.m_42;
	m_23 = matTmp.m_21 * m.m_13 + matTmp.m_22 * m.m_23 + matTmp.m_23 * m.m_33 + matTmp.m_24 * m.m_43;
	m_24 = matTmp.m_21 * m.m_14 + matTmp.m_22 * m.m_24 + matTmp.m_23 * m.m_34 + matTmp.m_24 * m.m_44;

	m_31 = matTmp.m_31 * m.m_11 + matTmp.m_32 * m.m_21 + matTmp.m_33 * m.m_31 + matTmp.m_34 * m.m_41;
	m_32 = matTmp.m_31 * m.m_12 + matTmp.m_32 * m.m_22 + matTmp.m_33 * m.m_32 + matTmp.m_34 * m.m_42;
	m_33 = matTmp.m_31 * m.m_13 + matTmp.m_32 * m.m_23 + matTmp.m_33 * m.m_33 + matTmp.m_34 * m.m_43;
	m_34 = matTmp.m_31 * m.m_14 + matTmp.m_32 * m.m_24 + matTmp.m_33 * m.m_34 + matTmp.m_34 * m.m_44;

	m_41 = matTmp.m_41 * m.m_11 + matTmp.m_42 * m.m_21 + matTmp.m_43 * m.m_31 + matTmp.m_44 * m.m_41;
	m_42 = matTmp.m_41 * m.m_12 + matTmp.m_42 * m.m_22 + matTmp.m_43 * m.m_32 + matTmp.m_44 * m.m_42;
	m_43 = matTmp.m_41 * m.m_13 + matTmp.m_42 * m.m_23 + matTmp.m_43 * m.m_33 + matTmp.m_44 * m.m_43;
	m_44 = matTmp.m_41 * m.m_14 + matTmp.m_42 * m.m_24 + matTmp.m_43 * m.m_34 + matTmp.m_44 * m.m_44;
}

// Multiply (2).
template < typename Type >
void Matrix4x4 < Type > ::Mul( float f )
{
	m_11 *= f;
	m_12 *= f;
	m_13 *= f;
	m_14 *= f;
	m_21 *= f;
	m_22 *= f;
	m_23 *= f;
	m_24 *= f;
	m_31 *= f;
	m_32 *= f;
	m_33 *= f;
	m_34 *= f;
	m_41 *= f;
	m_42 *= f;
	m_43 *= f;
	m_44 *= f;
}





// Multiply matrix. ( 1 )
template < typename Type >
void MulMatrix(	Matrix2x2 < Type >* pOutMat,
									const Matrix2x2 < Type >& inMat1,
									const Matrix2x2 < Type >& inMat2 )
{
	pOutMat->m_11 = inMat1.m_11 * inMat2.m_11 + inMat1.m_12 * inMat2.m_21;
	pOutMat->m_12 = inMat1.m_11 * inMat2.m_12 + inMat1.m_12 * inMat2.m_22;
	pOutMat->m_21 = inMat1.m_21 * inMat2.m_11 + inMat1.m_22 * inMat2.m_21;
	pOutMat->m_22 = inMat1.m_21 * inMat2.m_12 + inMat1.m_22 * inMat2.m_22;
}

// Multiply matrix. ( 2 )
template < typename Type >
void MulMatrix(	Matrix3x3 < Type >* pOutMat,
									const Matrix3x3 < Type >& inMat1,
									const Matrix3x3 < Type >& inMat2 )
{
	pOutMat->m_11 = inMat1.m_11 * inMat2.m_11 + inMat1.m_12 * inMat2.m_21 + inMat1.m_13 * inMat2.m_31;
	pOutMat->m_12 = inMat1.m_11 * inMat2.m_12 + inMat1.m_12 * inMat2.m_22 + inMat1.m_13 * inMat2.m_32;
	pOutMat->m_13 = inMat1.m_11 * inMat2.m_13 + inMat1.m_12 * inMat2.m_23 + inMat1.m_13 * inMat2.m_33;

	pOutMat->m_21 = inMat1.m_21 * inMat2.m_11 + inMat1.m_22 * inMat2.m_21 + inMat1.m_23 * inMat2.m_31;
	pOutMat->m_22 = inMat1.m_21 * inMat2.m_12 + inMat1.m_22 * inMat2.m_22 + inMat1.m_23 * inMat2.m_32;
	pOutMat->m_23 = inMat1.m_21 * inMat2.m_13 + inMat1.m_22 * inMat2.m_23 + inMat1.m_23 * inMat2.m_33;

	pOutMat->m_31 = inMat1.m_31 * inMat2.m_11 + inMat1.m_32 * inMat2.m_21 + inMat1.m_33 * inMat2.m_31;
	pOutMat->m_32 = inMat1.m_31 * inMat2.m_12 + inMat1.m_32 * inMat2.m_22 + inMat1.m_33 * inMat2.m_32;
	pOutMat->m_33 = inMat1.m_31 * inMat2.m_13 + inMat1.m_32 * inMat2.m_23 + inMat1.m_33 * inMat2.m_33;
}

// Multiply matrix. ( 1 )
template < typename Type >
void MulMatrix(	Matrix4x4 < Type >* pOutMat,
									const Matrix4x4 < Type >& inMat1,
									const Matrix4x4 < Type >& inMat2 )
{
	pOutMat->m_11 = inMat1.m_11 * inMat2.m_11 + inMat1.m_12 * inMat2.m_21 + inMat1.m_13 * inMat2.m_31 + inMat1.m_14 * inMat2.m_41;
	pOutMat->m_12 = inMat1.m_11 * inMat2.m_12 + inMat1.m_12 * inMat2.m_22 + inMat1.m_13 * inMat2.m_32 + inMat1.m_14 * inMat2.m_42;
	pOutMat->m_13 = inMat1.m_11 * inMat2.m_13 + inMat1.m_12 * inMat2.m_23 + inMat1.m_13 * inMat2.m_33 + inMat1.m_14 * inMat2.m_43;
	pOutMat->m_14 = inMat1.m_11 * inMat2.m_14 + inMat1.m_12 * inMat2.m_24 + inMat1.m_13 * inMat2.m_34 + inMat1.m_14 * inMat2.m_44;

	pOutMat->m_21 = inMat1.m_21 * inMat2.m_11 + inMat1.m_22 * inMat2.m_21 + inMat1.m_23 * inMat2.m_31 + inMat1.m_24 * inMat2.m_41;
	pOutMat->m_22 = inMat1.m_21 * inMat2.m_12 + inMat1.m_22 * inMat2.m_22 + inMat1.m_23 * inMat2.m_32 + inMat1.m_24 * inMat2.m_42;
	pOutMat->m_23 = inMat1.m_21 * inMat2.m_13 + inMat1.m_22 * inMat2.m_23 + inMat1.m_23 * inMat2.m_33 + inMat1.m_24 * inMat2.m_43;
	pOutMat->m_24 = inMat1.m_21 * inMat2.m_14 + inMat1.m_22 * inMat2.m_24 + inMat1.m_23 * inMat2.m_34 + inMat1.m_24 * inMat2.m_44;

	pOutMat->m_31 = inMat1.m_31 * inMat2.m_11 + inMat1.m_32 * inMat2.m_21 + inMat1.m_33 * inMat2.m_31 + inMat1.m_34 * inMat2.m_41;
	pOutMat->m_32 = inMat1.m_31 * inMat2.m_12 + inMat1.m_32 * inMat2.m_22 + inMat1.m_33 * inMat2.m_32 + inMat1.m_34 * inMat2.m_42;
	pOutMat->m_33 = inMat1.m_31 * inMat2.m_13 + inMat1.m_32 * inMat2.m_23 + inMat1.m_33 * inMat2.m_33 + inMat1.m_34 * inMat2.m_43;
	pOutMat->m_34 = inMat1.m_31 * inMat2.m_14 + inMat1.m_32 * inMat2.m_24 + inMat1.m_33 * inMat2.m_34 + inMat1.m_34 * inMat2.m_44;

	pOutMat->m_41 = inMat1.m_41 * inMat2.m_11 + inMat1.m_42 * inMat2.m_21 + inMat1.m_43 * inMat2.m_31 + inMat1.m_44 * inMat2.m_41;
	pOutMat->m_42 = inMat1.m_41 * inMat2.m_12 + inMat1.m_42 * inMat2.m_22 + inMat1.m_43 * inMat2.m_32 + inMat1.m_44 * inMat2.m_42;
	pOutMat->m_43 = inMat1.m_41 * inMat2.m_13 + inMat1.m_42 * inMat2.m_23 + inMat1.m_43 * inMat2.m_33 + inMat1.m_44 * inMat2.m_43;
	pOutMat->m_44 = inMat1.m_41 * inMat2.m_14 + inMat1.m_42 * inMat2.m_24 + inMat1.m_43 * inMat2.m_34 + inMat1.m_44 * inMat2.m_44;
}

// Create indentity matrix.
template < typename Type >
void CreateIdentityMat( Matrix4x4 < Type >* pOutMat )
{
	for( int i = 0; i < 16; i++ ){
		pOutMat->m_Elm1[ i ] = 0;
	}

	for( int i = 0; i < 4; i++ ){
		pOutMat->m_Elm[ i ][ i ] = 1;
	}
}

// Create identity matrix.
template < typename Type >
void CreateIdentityMat( Matrix3x3 < Type >* pOutMat )
{
	for( int i = 0; i < 3; i++ ){
		for( int j = 0; j < 3; ++j ){
			pOutMat->m_Elm[ i ][ j ] = 0;
		}
	}

	for( int i = 0; i < 3; i++ ){
		pOutMat->m_Elm[ i ][ i ] = 1;
	}
}

// Create translation matrix. ( Right-handed coordinate system. )
template < typename Type >
void CreateTranslationMat( Matrix4x4 < Type >* pOutMat, Type x, Type y, Type z )
{
	CreateIdentityMat( pOutMat );
	pOutMat->m_41 = x;
	pOutMat->m_42 = y;
	pOutMat->m_43 = z;
}

// Create translation matrix. ( Right-handed coordinate system. )
template < typename Type >
void CreateTranslationMat( Matrix4x4 < Type >* pOutMat, Type x, Type y )
{
	CreateIdentityMat( pOutMat );
	pOutMat->m_41 = x;
	pOutMat->m_42 = y;
}

// Create scaling matrix.
template < typename Type >
void CreateScalingMat( Matrix4x4 < Type >* pOutMat, Type x, Type y, Type z )
{
	CreateIdentityMat( pOutMat );
	pOutMat->m_11 = x;
	pOutMat->m_22 = y;
	pOutMat->m_33 = z;
}

// Create scaling matrix.
template < typename Type >
void CreateScalingMat( Matrix4x4 < Type >* pOutMat, Type x, Type y )
{
	CreateIdentityMat( pOutMat );
	pOutMat->m_11 = x;
	pOutMat->m_22 = y;
}


// Create rotation around the x axis.  ( Right-handed coordinate system. )
template < typename Type >
void CreateRotationXMat( Matrix4x4 < Type >* pOutMat, Type angle )
{
	CreateIdentityMat( pOutMat );
	pOutMat->m_22 = cos( angle );
	pOutMat->m_23 = -sin( angle );
	pOutMat->m_32 = sin( angle );
	pOutMat->m_33 = cos( angle );
}

// Create zero matrix.
template < typename Type >
void CreateZeroMat( Matrix4x4 < Type >* pOutMat )
{
	ZeroObject( pOutMat->m_Elm1, sizeof( pOutMat->m_Elm1 ) );
}

// Create rotation around the y axis. ( Right-handed coordinate system. )
template < typename Type >
void CreateRotationYMat( Matrix4x4 < Type >* pOutMat, Type angle )
{
	CreateIdentityMat( pOutMat );
	pOutMat->m_11 = cos( angle );
	pOutMat->m_13 = sin( angle );
	pOutMat->m_31 = -sin( angle );
	pOutMat->m_33 = cos( angle );
}

// Create rotation around the z axis. ( Right-handed coordinate system. )
template < typename Type >
void CreateRotationZMat( Matrix4x4 < Type >* pOutMat, Type angle )
{
	CreateIdentityMat( pOutMat );
	pOutMat->m_11 = cos( angle );
	pOutMat->m_12 = -sin( angle );
	pOutMat->m_21 = sin( angle );
	pOutMat->m_22 = cos( angle );
}

// Create perspective projection transformation matrix.
template < typename Type >
void CreatePersProjMat( Matrix4x4 < Type >* pOutMat, Type fovy, Type aspect, Type nearClip, Type farClip )
{
	CreateZeroMat( pOutMat );
	Type f = 1.0f / ::tan( fovy / 2.0f );
	pOutMat->m_11 = f;
	pOutMat->m_22 = f * aspect;
	pOutMat->m_33 = - ( farClip + nearClip ) / ( farClip - nearClip );
	pOutMat->m_34 = - 2 * nearClip * farClip / ( farClip - nearClip );
	pOutMat->m_43 = -1;
}

// Create view transformation matrix.
template < typename Type >
void CreateViewMat(	Matrix4x4 < Type >* pOutMat,
							Type eyeX,
							Type eyeY,
							Type eyeZ,
							Type lookX,
							Type lookY,
							Type lookZ,
							Type upX,
							Type upY,
							Type upZ )
{
	CreateZeroMat( pOutMat );
	
	// z = eye - look.
	Type lx = eyeX - lookX;
	Type ly = eyeY - lookY;
	Type lz = eyeZ - lookZ;
	Type l = ::sqrt( lx * lx + ly * ly + lz * lz );
	pOutMat->m_31 = lx / l;
	pOutMat->m_32 = ly / l;
	pOutMat->m_33 = lz / l;

	// x = u * z.
	lx = upY * pOutMat->m_33 - upZ * pOutMat->m_32;
	ly = upZ * pOutMat->m_31 - upX * pOutMat->m_33;
	lz = upX * pOutMat->m_32 - upY * pOutMat->m_31;
	l = ::sqrt( lx * lx + ly * ly + lz * lz );
	pOutMat->m_11 = lx / l;
	pOutMat->m_12 = ly / l;
	pOutMat->m_13 = lz / l;

	// y = z * x.
	pOutMat->m_21 = pOutMat->m_32 * pOutMat->m_13 - pOutMat->m_33 * pOutMat->m_12;
	pOutMat->m_22 = pOutMat->m_33 * pOutMat->m_11 - pOutMat->m_31 * pOutMat->m_13;
	pOutMat->m_23 = pOutMat->m_31 * pOutMat->m_12 - pOutMat->m_32 * pOutMat->m_11;

	pOutMat->m_14 = -( eyeX * pOutMat->m_11 + eyeY * pOutMat->m_12 + eyeZ * pOutMat->m_13 );
	pOutMat->m_24 = -( eyeX * pOutMat->m_21 + eyeY * pOutMat->m_22 + eyeZ * pOutMat->m_23 );
	pOutMat->m_34 = -( eyeX * pOutMat->m_31 + eyeY * pOutMat->m_32 + eyeZ * pOutMat->m_33 );
	pOutMat->m_44 = 1;
}


// Create transverse matrix.
template < typename Type >
void CreateTransverseMat( const Matrix4x4 < Type >& in, Matrix4x4 < Type >* pOut )
{
	pOut->m_11 = in.m_11;
	pOut->m_12 = in.m_21;
	pOut->m_13 = in.m_31;
	pOut->m_14 = in.m_41;
	pOut->m_21 = in.m_12;
	pOut->m_22 = in.m_22;
	pOut->m_23 = in.m_32;
	pOut->m_24 = in.m_42;
	pOut->m_31 = in.m_13;
	pOut->m_32 = in.m_23;
	pOut->m_33 = in.m_33;
	pOut->m_34 = in.m_43;
	pOut->m_41 = in.m_14;
	pOut->m_42 = in.m_24;
	pOut->m_43 = in.m_34;
	pOut->m_44 = in.m_44;
}




template < typename Type, int ROW, int COLMUN >
class Matrix
{
public:
	union
	{
		Type		m_Elm[ ROW * COLMUN ];
		Type		m_Elms[ ROW ][ COLMUN ];
	};
	Matrix();
	~Matrix();
	Matrix( const Matrix < Type, ROW, COLMUN >& m );
	Matrix < Type, ROW, COLMUN > operator+( const Matrix < Type, ROW, COLMUN >& m );
	Matrix < Type, ROW, COLMUN > operator-( const Matrix < Type, ROW, COLMUN >& m );
	template < int COLUMN_B >
	Matrix < Type, ROW, COLUMN_B > operator*( const Matrix < Type, COLMUN, COLUMN_B >& m );
	Matrix < Type, ROW, COLMUN > operator*( Type value );
	Vector < Type, ROW > operator*( const Vector < Type, ROW >& v );
	Matrix < Type, ROW, COLMUN > operator/( Type value );
	Matrix < Type, ROW, COLMUN >& operator=( const Matrix < Type, ROW, COLMUN >& m );
	bool operator==( const Matrix < Type, ROW, COLMUN >& m );
	Matrix < Type, ROW, COLMUN >& operator+=( const Matrix < Type, ROW, COLMUN >& m );
	Matrix < Type, ROW, COLMUN >& operator-=( const Matrix < Type, ROW, COLMUN >& m );
	Matrix < Type, ROW, COLMUN >& operator*=( const Matrix < Type, ROW, COLMUN >& m );
	Matrix < Type, ROW, COLMUN >& operator*=( Type value );
	Matrix < Type, ROW, COLMUN >& operator/=( Type value );
	void Add( const Matrix < Type, ROW, COLMUN >& m );
	void Sub( const Matrix < Type, ROW, COLMUN >& m );
	void Mul( const Matrix < Type, ROW, COLMUN >& m );
	void Mul( Type value );
	void Div( Type value );
	void Set( int index, Type value );
	void Set( int row, int colmun, Type value );
	Type Get( int index ) const;
	Type Get( int row, int colmun ) const;
};

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN > ::Matrix()
{
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN > ::~Matrix()
{
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN > ::Matrix( const Matrix < Type, ROW, COLMUN >& m )
{
	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			m_Elms[ row ][ colmun ] = m.m_Elms[ row ][ colmun ];
		}
	}
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN > Matrix < Type, ROW, COLMUN >::operator+( const Matrix < Type, ROW, COLMUN >& m )
{
	Matrix < Type, ROW, COLMUN > matTmp;

	for( int row = 0; row < ROW; ++row ){
		for( int colmun = 0; colmun < COLMUN; ++ colmun ){
			matTmp.m_Elms[ row ][ colmun ] = this->m_Elms[ row ][ colmun ] + m.m_Elms[ row ][ colmun ];
		}
	}

	return matTmp;
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN > Matrix < Type, ROW, COLMUN >::operator-( const Matrix < Type, ROW, COLMUN >& m )
{
	Matrix < Type, ROW, COLMUN > matTmp;

	for( int row = 0; row < ROW; ++row ){
		for( int colmun = 0; colmun < COLMUN; ++ colmun ){
			matTmp.m_Elms[ row ][ colmun ] = this->m_Elms[ row ][ colmun ] - m.m_Elms[ row ][ colmun ];
		}
	}

	return matTmp;
}

template < typename Type, int ROW, int COLMUN >
template < int COLUMN_B >
Matrix < Type, ROW, COLUMN_B > Matrix < Type, ROW, COLMUN >::operator*( const Matrix < Type, COLMUN, COLUMN_B >& m )
{
	Matrix < Type, ROW, COLUMN_B > matTmp;

	for( int row = 0; row < ROW; ++row ){
		for( int colmun = 0; colmun < COLUMN_B; ++colmun ){
			matTmp.m_Elms[ row ][ colmun ] = 0;
			for( int i = 0; i < COLMUN; ++i ){
				matTmp.m_Elms[ row ][ colmun ] += this->m_Elms[ row ][ i ] * m.m_Elms[ i ][ colmun ];
			}
		}
	}

	return matTmp;
}

template < typename Type, int ROW, int COLMUN >
Vector < Type, ROW > Matrix < Type, ROW, COLMUN >::operator*( const Vector < Type, ROW >& v )
{
	Vector < Type, ROW > vTmp;

	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			vTmp.m_Elm[ colmun ] = m_Elms[ colmun ][ row ] * v.m_Elm[ row ];
		}
	}

	return vTmp;
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN > Matrix < Type, ROW, COLMUN >::operator*( Type value )
{
	Matrix < Type, ROW, COLMUN > matTmp;

	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			matTmp.m_Elms[ row ][ colmun ] *= value;
		}
	}

	return matTmp;
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN > Matrix < Type, ROW, COLMUN >::operator/( Type value )
{
	Matrix < Type, ROW, COLMUN > matTmp;

	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			matTmp.m_Elms[ row ][ colmun ] /= value;
		}
	}

	return matTmp;
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN >& Matrix < Type, ROW, COLMUN >::operator=( const Matrix < Type, ROW, COLMUN >& m )
{
	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			m_Elms[ row ][ colmun ] = m.m_Elms[ row ][ colmun ];
		}
	}

	return *this;
}

template < typename Type, int ROW, int COLMUN >
bool Matrix < Type, ROW, COLMUN >::operator==( const Matrix < Type, ROW, COLMUN >& m )
{
	bool result = true;

	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			if( m_Elms[ row ][ colmun ] != m.m_Elms[ row ][ colmun ] ){
				result = false;
				break;
			}
		}
	}

	return result;
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN >& Matrix < Type, ROW, COLMUN >::operator+=( const Matrix < Type, ROW, COLMUN >& m )
{
	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			m_Elms[ row ][ colmun ] += m.m_Elms[ row ][ colmun ];
		}
	}

	return *this;
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN >& Matrix < Type, ROW, COLMUN >::operator-=( const Matrix < Type, ROW, COLMUN >& m )
{
	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			m_Elms[ row ][ colmun ] -= m.m_Elms[ row ][ colmun ];
		}
	}

	return *this;
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN >& Matrix < Type, ROW, COLMUN >::operator*=( const Matrix < Type, ROW, COLMUN >& m )
{
	Matrix matTmp = *this;

	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			for( int i = 0; i < ROW; ++i ){
				m_Elms[ row ][ colmun ] = matTmp.m_Elms[ i ][ colmun ] * m.m_Elms[ row ][ i ];
			}
		}
	}

	return *this;
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN >& Matrix < Type, ROW, COLMUN >::operator*=( Type value )
{
	for( int row = 0; row < ROW; ++row ){
		for( int colmun = 0; colmun < COLMUN; ++colmun ){
			m_Elms[ row ][ colmun ] *= value;
		}
	}

	return *this;
}

template < typename Type, int ROW, int COLMUN >
Matrix < Type, ROW, COLMUN >& Matrix < Type, ROW, COLMUN >::operator/=( Type value )
{
	for( int row = 0; row < ROW; ++row ){
		for( int colmun = 0; colmun < COLMUN; ++colmun ){
			m_Elms[ row ][ colmun ] /= value;
		}
	}

	return *this;
}

template < typename Type, int ROW, int COLMUN >
void Matrix < Type, ROW, COLMUN >::Add( const Matrix < Type, ROW, COLMUN >& m )
{
	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			m_Elms[ row ][ colmun ] += m.m_Elms[ row ][ colmun ];
		}
	}
}

template < typename Type, int ROW, int COLMUN >
void Matrix < Type, ROW, COLMUN >::Sub( const Matrix < Type, ROW, COLMUN >& m )
{
	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			m_Elms[ row ][ colmun ] -= m.m_Elms[ row ][ colmun ];
		}
	}
}

template < typename Type, int ROW, int COLMUN >
void Matrix < Type, ROW, COLMUN >::Mul( const Matrix < Type, ROW, COLMUN >& m )
{
	Matrix matTmp = *this;

	for( int colmun = 0; colmun < COLMUN; ++colmun ){
		for( int row = 0; row < ROW; ++row ){
			for( int i = 0; i < ROW; ++i ){
				m_Elms[ row ][ colmun ] = matTmp.m_Elms[ i ][ colmun ] * m.m_Elms[ row ][ i ];
			}
		}
	}
}

template < typename Type, int ROW, int COLMUN >
void Matrix < Type, ROW, COLMUN >::Mul( Type value )
{
	for( int row = 0; row < ROW; ++row ){
		for( int colmun = 0; colmun < COLMUN; ++colmun ){
			m_Elms[ row ][ colmun ] *= value;
		}
	}
}

template < typename Type, int ROW, int COLMUN >
void Matrix < Type, ROW, COLMUN >::Div( Type value )
{
	for( int row = 0; row < ROW; ++row ){
		for( int colmun = 0; colmun < COLMUN; ++colmun ){
			m_Elms[ row ][ colmun ] /= value;
		}
	}
}

template < typename Type, int ROW, int COLMUN >
void Matrix < Type, ROW, COLMUN >::Set( int index, Type value )
{
	m_Elm[ index ] = value;
}

template < typename Type, int ROW, int COLMUN >
void Matrix < Type, ROW, COLMUN >::Set( int row, int colmun, Type value )
{
	m_Elms[ row ][ colmun ] = value;
}

template < typename Type, int ROW, int COLMUN >
Type Matrix < Type, ROW, COLMUN >::Get( int index ) const
{
	return m_Elm[ index ];
}

template < typename Type, int ROW, int COLMUN >
Type Matrix < Type, ROW, COLMUN >::Get( int row, int colmun ) const
{
	return m_Elms[ row ][ colmun ];
}

typedef Matrix < float, 2, 2 >	Matrix22f;
typedef Matrix < double, 2, 2 >	Marrix22d;
typedef Matrix < float, 3, 3 >	Matrix33f;
typedef Matrix < double, 3, 3 >	Matrix33d;
typedef Matrix < float, 4, 4 >	Matrix44f;
typedef Matrix < double, 4, 4 >	Matrix44d;


#endif
