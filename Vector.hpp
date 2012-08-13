/**
*	@file	Vector.hpp
*	@brief	
*	@date	2011.6.13(Mon) 11:34
*/

#ifndef INCLUDED_VECTOR_HPP
#define INCLUDED_VECTOR_HPP


template < typename Type >
class Vector2
{
public:
	union
	{
		struct
		{
			Type		m_X;
			Type		m_Y;
		};
		Type	m_Elm[ 2 ];
	};

	//Constructer(1)
	Vector2();
	//Constructer(2)
	Vector2( Type x, Type y );
	//Constructer(3)
	Vector2( const Vector2 < Type >& v );
	//Destructer
	~Vector2();
	//Add / Ternary operator (Overload of + operator)
	Vector2 operator+( const Vector2 < Type >& v );
	//Subtract / Ternary operator (Overload of - operator)
	Vector2 operator-( const Vector2 < Type >& v );
	//Substitute (Overload of = operator)
	//Vector2& operator=( const Vector2 < Type >& v );
	//Equivalence (Overload of == operator)
	bool operator==( const Vector2 < Type >& v );
	//Add / Binary operator (Overload of += operator)
	Vector2& operator+=( const Vector2 < Type >& v );
	//Subtract / Binary operator (Overload of -= operator)
	Vector2& operator-=( const Vector2 < Type >& v );
	//Add
	void Add( const Vector2 < Type >& v );
	//Subtract
	void Sub( const Vector2 < Type >& v );
	//Multiply constant
	void MulConst( Type num );
	//Rotate
	void Rot( Type angle );
	//Get sum of square
	Type GetSumSquare() const;
	//Get norm
	Type GetNorm() const;
	//Normalize
	void Normalize();
	//Get inner product
	Type GetInnerProduct( const Vector2 < Type >& v ) const;
	//Get outer product
	Type GetOuterProduct( const Vector2 < Type >& v ) const;
};

//Constructer(1)
template < typename Type >
Vector2 < Type > ::Vector2() : m_X( 0 ), m_Y( 0 )
{
}

//Constructer(2)
template < typename Type >
Vector2 < Type > ::Vector2( Type x, Type y ) : m_X( x ), m_Y( y )
{
}

//Constructer(3)
template < typename Type >
Vector2 < Type > ::Vector2( const Vector2 < Type >& v ) : m_X( v.m_X ), m_Y( v.m_Y )
{
}

//Destructer
template < typename Type >
Vector2 < Type > ::~Vector2()
{
}

//Add / Ternary operator (Overload of + operator)
template < typename Type >
Vector2 < Type > Vector2 < Type > ::operator+( const Vector2 < Type >& v )
{
	Vector2 < Type > vTmp;

	vTmp.m_X = m_X + v.m_X;
	vTmp.m_Y = m_Y + v.m_Y;

	return vTmp;
}

//Subtract / Ternary operator (Overload of - operator)
template < typename Type >
Vector2 < Type > Vector2 < Type > ::operator-( const Vector2 < Type >& v )
{
	Vector2 < Type > vTmp;

	vTmp.m_X = m_X - v.m_X;
	vTmp.m_Y = m_Y - v.m_Y;

	return vTmp;
}

//Equivalence (Overload of == operator)
template < typename Type >
bool Vector2 < Type > ::operator==( const Vector2 < Type >& v )
{
	return ( ( m_X == v.m_X ) && ( m_Y == v.m_Y ) );
}

//Add / Binary operator (Overload of += operator)
template < typename Type >
Vector2 < Type >& Vector2 < Type > ::operator+=( const Vector2 < Type >& v )
{
	m_X += v.m_X;
	m_Y += v.m_Y;

	return *this;
}

//Subtract / Binary operator (Overload of -= operator)
template < typename Type >
Vector2 < Type >& Vector2 < Type > ::operator-=( const Vector2 < Type >& v )
{
	m_X -= v.m_X;
	m_Y -= v.m_Y;

	return *this;
}

//Add
template < typename Type >
void Vector2 < Type > ::Add( const Vector2 < Type >& v )
{
	m_X += v.m_X;
	m_Y += v.m_Y;
}

//Subtract
template < typename Type >
void Vector2 < Type > ::Sub( const Vector2 < Type >& v )
{
	m_X -= v.m_X;
	m_Y -= v.m_Y;
}

//Multiply constant
template < typename Type >
void Vector2 < Type > ::MulConst( Type num )
{
	m_X *= num;
	m_Y *= num;
}

//Rotate
template < typename Type >
void Vector2 < Type > ::Rot( Type angle )
{
	Type tmpX = m_X;			//Speed-up / Only m_X will be changed in first expression

	m_X = m_X * cos( angle ) - m_Y * sin( angle );
	m_Y = tmpX * sin( angle ) + m_Y * cos( angle );
}

//Get sum of square
template < typename Type >
Type Vector2 < Type > ::GetSumSquare() const
{
	return ( m_X * m_X + m_Y * m_Y );
}

//Get norm
template < typename Type >
Type Vector2 < Type > ::GetNorm() const
{
	return sqrt( m_X * m_X + m_Y * m_Y );
}

//Normalize
template < typename Type >
void Vector2 < Type > ::Normalize()
{
	Type mulConst = 1 / sqrt( m_X * m_X + m_Y * m_Y );

	m_X *= mulConst;
	m_Y *= mulConst;
}

//Get inner product
template < typename Type >
Type Vector2 < Type > ::GetInnerProduct( const Vector2 < Type >& v ) const
{
	return ( m_X * v.m_X + m_Y * v.m_Y );
}

//Get outer product
template < typename Type >
Type Vector2 < Type > ::GetOuterProduct( const Vector2 < Type >& v ) const
{
	return ( m_X * v.m_Y - m_Y * v.m_X );
}

template < typename Type >
class Vector3
{
public:
	union
	{
		struct
		{
			Type		m_X;
			Type		m_Y;
			Type		m_Z;
		};
		Type	m_Elm[ 3 ];
	};

	//Constructer(1)
	Vector3();
	//Constructer(2)
	Vector3( Type x, Type y, Type z );
	//Constructer(3)
	Vector3( const Vector3 < Type >& v );
	//Destructer
	~Vector3();
	// Sign inversion / Unary operator. ( Overload of - operator )
	Vector3 operator-();
	//Add / Ternary operator (Overload of + operator)
	Vector3 operator+( const Vector3 < Type >& v );
	//Subtract / Ternary operator (Overload of - operator)
	Vector3 operator-( const Vector3 < Type >& v );
	// Multiply / Ternary operator. ( Overload of * operator )
	Vector3 operator*( Type n );
	//Substitute (Overload of = operator)
	Vector3& operator=( const Vector3 < Type >& v );
	//Equivalence (Overload of == operator)
	bool operator==( const Vector3 < Type >& v );
	//Add / Binary operator (Overload of += operator)
	Vector3& operator+=( const Vector3 < Type >& v );
	//Subtract / Binary operator (Overload of -= operator)
	Vector3& operator-=( const Vector3 < Type >& v );
	//Add
	void Add( const Vector3 < Type >& v );
	//Subtract
	void Sub( const Vector3 < Type >& v );
	//Multiply constant
	void MulConst( Type num );
	//Rotate around the x axis
	void RotX( Type angle );
	//Rotate around the y axis
	void RotY( Type angle );
	//Rotate around the z axis
	void RotZ( Type angle );
	//Rotate around the x axis at first, and rotate around the y axis next
	void RotXY( Type angleX, Type angleY );
	//Rotate around the y axis at first, and rotate around the x axis next
	void RotYX( Type angleY, Type angleX );
	//Get sum of square
	Type GetSumSquare() const;
	//Get norm
	Type GetNorm() const;
	//Normalize
	void Normalize();
	//Get inner product
	Type GetInnerProduct( const Vector3 < Type >& v ) const;
	//Get outer product
	Vector3 GetOuterProduct( const Vector3 < Type >& v ) const;
};

//Constructer(1)
template < typename Type >
Vector3 < Type > ::Vector3() : m_X( 0 ), m_Y( 0 ), m_Z( 0 )
{
}

//Constructer(2)
template < typename Type >
Vector3 < Type > ::Vector3( Type x, Type y, Type z ) : m_X( x ), m_Y( y ), m_Z( z )
{
}

//Constructer(3)
template < typename Type >
Vector3 < Type > ::Vector3( const Vector3 < Type >& v ) : m_X( v.m_X ), m_Y( v.m_Y ), m_Z( v.m_Z )
{
}

//Destructer
template < typename Type >
Vector3 < Type > ::~Vector3()
{
}

// Sign inversion / Unary operator. ( Overload of - operator )
template < typename Type >
Vector3 < Type > Vector3 < Type > ::operator-()
{
	Vector3 < Type > vTmp;

	vTmp.m_X = -m_X;
	vTmp.m_Y = -m_Y;
	vTmp.m_Z = -m_Z;

	return vTmp;
}

//Add / Ternary operator (Overload of + operator)
template < typename Type >
Vector3 < Type > Vector3 < Type > ::operator+( const Vector3 < Type >& v )
{
	Vector3 < Type > vTmp;

	vTmp.m_X = m_X + v.m_X;
	vTmp.m_Y = m_Y + v.m_Y;
	vTmp.m_Z = m_Z + v.m_Z;

	return vTmp;
}

//Subtract / Ternary operator (Overload of - operator)
template < typename Type >
Vector3 < Type > Vector3 < Type > ::operator-( const Vector3 < Type >& v )
{
	Vector3 < Type > vTmp;

	vTmp.m_X = m_X - v.m_X;
	vTmp.m_Y = m_Y - v.m_Y;
	vTmp.m_Z = m_Z - v.m_Z;

	return vTmp;
}

// Multiply / Ternary operator. ( Overload of * operator )
template < typename Type >
Vector3 < Type > Vector3 < Type > ::operator*( Type n )
{
	Vector3 < Type > vTmp;

	vTmp.m_X = m_X * n;
	vTmp.m_Y = m_Y * n;
	vTmp.m_Z = m_Z * n;

	return vTmp;
}

//Substitute (Overload of = operator)
template < typename Type >
Vector3 < Type >& Vector3 < Type > ::operator=( const Vector3 < Type >& v )
{
	m_X = v.m_X;
	m_Y = v.m_Y;
	m_Z = v.m_Z;

	return *this;
}

//Equivalence (Overload of == operator)
template < typename Type >
bool Vector3 < Type > ::operator==( const Vector3 < Type >& v )
{
	return ( ( m_X == v.m_X ) && ( m_Y == v.m_Y ) && ( m_Z == v.m_Z ) );
}

//Add / Binary operator (Overload of += operator)
template < typename Type >
Vector3 < Type >& Vector3 < Type > ::operator+=( const Vector3 < Type >& v )
{
	m_X += v.m_X;
	m_Y += v.m_Y;
	m_Z += v.m_Z;

	return *this;
}

//Subtract / Binary operator (Overload of -= operator)
template < typename Type >
Vector3 < Type >& Vector3 < Type > ::operator-=( const Vector3 < Type >& v )
{
	m_X -= v.m_X;
	m_Y -= v.m_Y;
	m_Z -= v.m_Z;

	return *this;
}

//Add
template < typename Type >
void Vector3 < Type > ::Add( const Vector3 < Type >& v )
{
	m_X += v.m_X;
	m_Y += v.m_Y;
	m_Z += v.m_Z;
}

//Subtract
template < typename Type >
void Vector3 < Type > ::Sub( const Vector3 < Type >& v )
{
	m_X -= v.m_X;
	m_Y -= v.m_Y;
	m_Z -= v.m_Z;
}

//Multiply constant
template < typename Type >
void Vector3 < Type > ::MulConst( Type num )
{
	m_X *= num;
	m_Y *= num;
	m_Z *= num;
}

//Rotate around the x axis
template < typename Type >
void Vector3 < Type > ::RotX( Type angle )
{
	Type tmpY = m_Y;				//Speed-up / Only m_Y will be changed in first expression

	m_Y = m_Y * cos( angle ) + m_Z * sin( angle );
	m_Z = -tmpY * sin( angle ) + m_Z * cos( angle );

	// RH
	//m_Y = m_Y * cos( angle ) - m_Z * sin( angle );
	//m_Z = tmpY * sin( angle ) + m_Z * cos( angle );
}

//Rotate around the y axis
template < typename Type >
void Vector3 < Type > ::RotY( Type angle )
{
	Type tmpZ = m_Z;				//Speed-up / Only m_Z will be changed in first expression

	m_Z = m_Z * cos( angle ) + m_X * sin( angle );
	m_X = -tmpZ * sin( angle ) + m_X * cos( angle );

	// RH
	// m_Z = m_Z * cos( angle ) - m_X * sin( angle );
	// m_X = tmpZ * sin( angle ) + m_X * cos( angle );
}

//Rotate around the z axis
template < typename Type >
void Vector3 < Type > ::RotZ( Type angle )
{
	Type tmpX = m_X;				//Speed-up / Only m_X will be changed in first expression

	m_X = m_X * cos( angle ) + m_Y * sin( angle );
	m_Y = -tmpX * sin( angle ) + m_Y * cos( angle );

	// RH
	//m_X = m_X * cos( angle ) - m_Y * sin( angle );
	//m_Y = tmpX * sin( angle ) + m_Y * cos( angle );
}

//Rotate around the x axis at first, and rotate around the y axis next
template < typename Type >
void Vector3 < Type > ::RotXY( Type angleX, Type angleY )
{
	Type tmpX = m_X;
	Type tmpY = m_Y;

	m_X = m_X * cos( angleY ) + m_Y * sin( angleX ) * sin( angleY ) + m_Z * cos( angleX ) * sin( angleY );
	m_Y = m_Y * cos( angleX ) - m_Z * sin( angleX );
	m_Z = -tmpX * sin( angleY ) + tmpY * sin( angleX ) * cos( angleY ) + m_Z * cos( angleX ) * cos( angleY );
}

//Rotate around the y axis at first, and rotate around the x axis next
template < typename Type >
void Vector3 < Type > ::RotYX( Type angleY, Type angleX )
{
	Type tmpX = m_X;
	Type tmpY = m_Y;

	m_X = m_X * cos( angleY ) + m_Z * sin( angleY );
	m_Y = tmpX * sin( angleX ) * sin( angleY ) + m_Y *cos( angleX ) - m_Z * sin( angleX ) * cos( angleY );
	m_Z = -tmpX * cos( angleX ) * sin( angleY ) + tmpY * sin( angleX ) + m_Z * cos( angleX ) * cos( angleY );
}

//Get sum of square
template < typename Type >
Type Vector3 < Type > ::GetSumSquare() const
{
	return ( m_X * m_X + m_Y * m_Y + m_Z * m_Z );
}

//Get norm
template < typename Type >
Type Vector3 < Type > ::GetNorm() const
{
	return sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z );
}

//Normalize
template < typename Type >
void Vector3 < Type > ::Normalize()
{
	Type mulConst = 1 / sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z );

	m_X *= mulConst;
	m_Y *= mulConst;
	m_Z *= mulConst;
}

//Get inner product
template < typename Type >
Type Vector3 < Type > ::GetInnerProduct( const Vector3 < Type >& v ) const
{
	return ( m_X * v.m_X + m_Y * v.m_Y + m_Z * v.m_Z );
}

//Get outer product
template < typename Type >
Vector3 < Type > Vector3 < Type > ::GetOuterProduct( const Vector3 < Type >& v ) const
{
	return Vector3 < Type > ( ( m_Y * v.m_Z - m_Z * v.m_Y ), ( m_Z * v.m_X - m_X * v.m_Z ), ( m_X * v.m_Y - m_Y * v.m_X ) );
}

template < typename Type >
class Vector4
{
public:
	union
	{
		struct
		{
			Type		m_X;
			Type		m_Y;
			Type		m_Z;
			Type		m_W;
		};
		Type	m_Elm[ 4 ];
	};

	//Constructer(1)
	Vector4();
	//Constructer(2)
	Vector4( Type x, Type y, Type z, Type w );
	//Constructer(3)
	Vector4( const Vector4 < Type >& v );
	//Destructer
	~Vector4();
	//Add / Ternary operator (Overload of + operator)
	Vector4 operator+( const Vector4 < Type >& v );
	//Subtract / Ternary operator (Overload of - operator)
	Vector4 operator-( const Vector4 < Type >& v );
	//Substitute (Overload of = operator)
	Vector4& operator=( const Vector4 < Type >& v );
	// Multiply / Ternary operator ( Overload of * operator ).
	//Vector4& operator*( const Matrix4x4 < Type >& m );
	//Equivalence (Overload of == operator)
	bool operator==( const Vector4 < Type >& v );
	//Add / Binary operator (Overload of += operator)
	Vector4& operator+=( const Vector4 < Type >& v );
	//Subtract / Binary operator (Overload of -= operator)
	Vector4& operator-=( const Vector4 < Type >& v );
	//Add
	void Add( const Vector4 < Type >& v );
	//Subtract
	void Sub( const Vector4 < Type >& v );
	//Multiply constant
	void MulConst( Type num );
	//Get sum of square
	Type GetSumSquare() const;
	//Get norm
	Type GetNorm() const;
	//Normalize
	void Normalize();
	//Get inner product
	Type GetInnerProduct( const Vector4 < Type >& v ) const;
};

//Constructer(1)
template < typename Type >
Vector4 < Type > ::Vector4() : m_X( 0 ), m_Y( 0 ), m_Z( 0 ), m_W( 0 )
{
}

//Constructer(2)
template < typename Type >
Vector4 < Type > ::Vector4( Type x, Type y, Type z, Type w ) : m_X( x ), m_Y( y ), m_Z( z ), m_W( w )
{
}

//Constructer(3)
template < typename Type >
Vector4 < Type > ::Vector4( const Vector4 < Type >& v ) : m_X( v.m_X ), m_Y( v.m_Y ), m_Z( v.m_Z ), m_W( v.m_W )
{
}

//Destructer
template < typename Type >
Vector4 < Type > ::~Vector4()
{
}

//Add / Ternary operator (Overload of + operator)
template < typename Type >
Vector4 < Type > Vector4 < Type > ::operator+( const Vector4 < Type >& v )
{
	Vector4 < Type > vTmp;

	vTmp.m_X = m_X + v.m_X;
	vTmp.m_Y = m_Y + v.m_Y;
	vTmp.m_Z = m_Z + v.m_Z;
	vTmp.m_W = m_W + v.m_W;

	return vTmp;
}

//Subtract / Ternary operator (Overload of - operator)
template < typename Type >
Vector4 < Type > Vector4 < Type > ::operator-( const Vector4 < Type >& v )
{
	Vector4 < Type > vTmp;

	vTmp.m_X = m_X - v.m_X;
	vTmp.m_Y = m_Y - v.m_Y;
	vTmp.m_Z = m_Z - v.m_Z;
	vTmp.m_W = m_W - v.m_W;

	return vTmp;
}

//Substitute (Overload of = operator)
template < typename Type >
Vector4 < Type >& Vector4 < Type > ::operator=( const Vector4 < Type >& v )
{
	m_X = v.m_X;
	m_Y = v.m_Y;
	m_Z = v.m_Z;
	m_W = v.m_W;

	return *this;
}

//Equivalence (Overload of == operator)
template < typename Type >
bool Vector4 < Type > ::operator==( const Vector4 < Type >& v )
{
	return ( ( m_X == v.m_X ) && ( m_Y == v.m_Y ) && ( m_Z == v.m_Z ) && ( m_W == v.m_W ) );
}

//Add / Binary operator (Overload of += operator)
template < typename Type >
Vector4 < Type >& Vector4 < Type > ::operator+=( const Vector4 < Type >& v )
{
	m_X += v.m_X;
	m_Y += v.m_Y;
	m_Z += v.m_Z;
	m_W += v.m_W;

	return *this;
}

//Subtract / Binary operator (Overload of -= operator)
template < typename Type >
Vector4 < Type >& Vector4 < Type > ::operator-=( const Vector4 < Type >& v )
{
	m_X -= v.m_X;
	m_Y -= v.m_Y;
	m_Z -= v.m_Z;
	m_W -= v.m_W;

	return *this;
}

//Add
template < typename Type >
void Vector4 < Type > ::Add( const Vector4 < Type >& v )
{
	m_X += v.m_X;
	m_Y += v.m_Y;
	m_Z += v.m_Z;
	m_W += v.m_W;
}

//Subtract
template < typename Type >
void Vector4 < Type > ::Sub( const Vector4 < Type >& v )
{
	m_X -= v.m_X;
	m_Y -= v.m_Y;
	m_Z -= v.m_Z;
	m_W -= v.m_W;
}

//Multiply constant
template < typename Type >
void Vector4 < Type > ::MulConst( Type num )
{
	m_X *= num;
	m_Y *= num;
	m_Z *= num;
	m_W *= num;
}

//Get sum of square
template < typename Type >
Type Vector4 < Type > ::GetSumSquare() const
{
	return ( m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W );
}

//Get norm
template < typename Type >
Type Vector4 < Type > ::GetNorm() const
{
	return sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W );
}

//Normalize
template < typename Type >
void Vector4 < Type > ::Normalize()
{
	Type mulConst = 1 / sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W );

	m_X *= mulConst;
	m_Y *= mulConst;
	m_Z *= mulConst;
	m_W *= mulConst;
}

//Get inner product
template < typename Type >
Type Vector4 < Type > ::GetInnerProduct( const Vector4 < Type >& v ) const
{
	return ( m_X * v.m_X + m_Y * v.m_Y + m_Z * v.m_Z + m_W * v.m_W );
}


template < typename Type, int DIM >
class Vector
{
public:
	Type			m_Elm[ DIM ];
	Vector();
	Vector( const Vector < Type, DIM >& v );
	Vector( Type arg0, ... );
	~Vector();
	//Add / Ternary operator (Overload of + operator)
	Vector < Type, DIM > operator+( const Vector < Type, DIM >& v );
	//Subtract / Ternary operator (Overload of - operator)
	Vector < Type, DIM > operator-( const Vector < Type, DIM >& v );
	//Substitute (Overload of = operator)
	Vector < Type, DIM >& operator=( const Vector < Type, DIM >& v );
	// Multiply / Ternary operator ( Overload of * operator ).
	Vector < Type, DIM > operator*( Type value );
	Vector < Type, DIM > operator/( Type value );
	//Equivalence (Overload of == operator)
	bool operator==( const Vector < Type, DIM >& v );
	//Add / Binary operator (Overload of += operator)
	Vector < Type, DIM >& operator+=( const Vector < Type, DIM >& v );
	//Subtract / Binary operator (Overload of -= operator)
	Vector < Type, DIM >& operator-=( const Vector < Type, DIM >& v );
	Vector < Type, DIM >& operator*=( Type value );
	Vector < Type, DIM >& operator/=( Type value );
	//Add
	void Add( const Vector < Type, DIM >& v );
	//Subtract
	void Sub( const Vector < Type, DIM >& v );
	//Multiply constant
	void Mul( Type num );
	void Div( Type num );
	//Get sum of square
	Type GetSumSquare() const;
	//Get norm
	Type GetNorm() const;
	//Normalize
	void Normalize();
	//Get inner product
	Type GetInnerProduct( const Vector < Type, DIM >& v ) const;
};

template < typename Type, int DIM >
Vector < Type, DIM > ::Vector()
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] = 0;
	}
}

template < typename Type, int DIM >
Vector < Type, DIM > ::Vector( const Vector < Type, DIM >& v )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] = v.m_Elm[ elm ];
	}
}

template < typename Type, int DIM >
Vector < Type, DIM > ::Vector( Type arg0, ... )
{
	Type* p = &arg0;
	int n = 0;
	while( n < DIM ){
		m_Elm[ n ] = *p++;
		++n;
	}
}

template < typename Type, int DIM >
Vector < Type, DIM > ::~Vector()
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] = 0;
	}
}

//Add / Ternary operator (Overload of + operator)
template < typename Type, int DIM >
Vector < Type, DIM > Vector < Type, DIM > ::operator+( const Vector < Type, DIM >& v )
{
	Vector < Type, DIM > vTmp;

	for( int elm = 0; elm < DIM; ++elm ){
		vTmp.m_Elm[ elm ] = m_Elm[ elm ] + v.m_Elm[ elm ];
	}

	return vTmp;
}

//Subtract / Ternary operator (Overload of - operator)
template < typename Type, int DIM >
Vector < Type, DIM > Vector < Type, DIM > ::operator-( const Vector < Type, DIM >& v )
{
	Vector < Type, DIM > vTmp;

	for( int elm = 0; elm < DIM; ++elm ){
		vTmp.m_Elm[ elm ] = m_Elm[ elm ] - v.m_Elm[ elm ];
	}

	return vTmp;
}

template < typename Type, int DIM >
Vector < Type, DIM > Vector < Type, DIM > ::operator*( Type value )
{
	Vector < Type, DIM > vTmp;

	for( int elm = 0; elm < DIM; ++elm ){
		vTmp.m_Elm[ elm ] = m_Elm[ elm ] * value;
	}

	return vTmp;
}

template < typename Type, int DIM >
Vector < Type, DIM > Vector < Type, DIM > ::operator/( Type value )
{
	Vector < Type, DIM > vTmp;

	for( int elm = 0; elm < DIM; ++elm ){
		vTmp.m_Elm[ elm ] = m_Elm[ elm ] / value;
	}

	return vTmp;
}

//Substitute (Overload of = operator)
template < typename Type, int DIM >
Vector < Type, DIM >& Vector < Type, DIM > ::operator=( const Vector < Type, DIM >& v )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] = v.m_Elm[ elm ];
	}

	return *this;
}

template < typename Type, int DIM >
bool Vector < Type, DIM > ::operator==( const Vector < Type, DIM >& v )
{
	bool result = true;

	for( int elm = 0; elm < DIM; ++elm ){
		if( m_Elm[ elm ] != v.m_Elm[ elm ] ){
			result = false;
			break;
		}
	}

	return result;
}

//Add / Binary operator (Overload of += operator)
template < typename Type, int DIM >
Vector < Type, DIM >& Vector < Type, DIM > ::operator+=( const Vector < Type, DIM >& v )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] += v.m_Elm[ elm ];
	}

	return *this;
}

//Subtract / Binary operator (Overload of -= operator)
template < typename Type, int DIM >
Vector < Type, DIM >& Vector < Type, DIM > ::operator-=( const Vector < Type, DIM >& v )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] -= v.m_Elm[ elm ];
	}

	return *this;
}

template < typename Type, int DIM >
Vector < Type, DIM >& Vector < Type, DIM > ::operator*=( Type value )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] *= value;
	}

	return *this;
}

template < typename Type, int DIM >
Vector < Type, DIM >& Vector < Type, DIM > ::operator/=( Type value )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] /= value;
	}

	return *this;
}

//Add
template < typename Type, int DIM >
void Vector < Type, DIM > ::Add( const Vector < Type, DIM >& v )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] += v.m_Elm[ elm ];
	}
}

//Subtract
template < typename Type, int DIM >
void Vector < Type, DIM > ::Sub( const Vector < Type, DIM >& v )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] -= v.m_Elm[ elm ];
	}
}

//Multiply constant
template < typename Type, int DIM >
void Vector < Type, DIM > ::Mul( Type num )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] *= num;
	}
}

template < typename Type, int DIM >
void Vector < Type, DIM > ::Div( Type num )
{
	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] /= num;
	}
}

//Get sum of square
template < typename Type, int DIM >
Type Vector < Type, DIM > ::GetSumSquare() const
{
	Type result = 0;

	for( int elm = 0; elm < DIM; ++elm ){
		result += m_Elm[ elm ] * m_Elm[ elm ];
	}

	return result;
}

//Get norm
template < typename Type, int DIM >
Type Vector < Type, DIM > ::GetNorm() const
{
	return ::sqrt( GetSumSquare() );
}

//Normalize
template < typename Type, int DIM >
void Vector < Type, DIM > ::Normalize()
{
	Type norm = GetNorm();

	for( int elm = 0; elm < DIM; ++elm ){
		m_Elm[ elm ] /= norm;
	}
}

//Get inner product
template < typename Type, int DIM >
Type Vector < Type, DIM > ::GetInnerProduct( const Vector < Type, DIM >& v ) const
{
	Type result = 0;

	for( int elm = 0; elm < DIM; ++elm ){
		result = m_Elm[ elm ] * v.m_Elm[ elm ];
	}

	return result;
}

typedef Vector < float, 2 >	Vector2f;
typedef Vector < double, 2 >	Vector2d;
typedef Vector < float, 3 >	Vector3f;
typedef Vector < double, 3 >	Vector3d;
typedef Vector < float, 4 >	Vector4f;
typedef Vector < double, 4 >	Vector4d;

template < typename Type >
Type CalcDeterminant(	const Vector3 < Type >& v0,
						const Vector3 < Type >& v1,
						const Vector3 < Type >& v2 )
{
	return	v0.m_X * v1.m_Y * v2.m_Z + v1.m_X * v2.m_Y * v0.m_Z + v2.m_X * v0.m_Y * v1.m_Z
			- v0.m_X * v2.m_Y * v1.m_Z - v1.m_X * v0.m_Y * v2.m_Z - v2.m_X * v1.m_Y * v0.m_Z;
}

#endif
