#include "CircleObj.h"

namespace RTG
{
	CircleObj::CircleObj( const MAPIL::Vector2 < double >& vPos, double radius ) :	CollisionObj(),
																					m_Pos( vPos ),
																					m_Radius( radius )
	{
	}

	CircleObj::~CircleObj()
	{
		m_Radius = 0;
	}

	MAPIL::Vector2 < double > CircleObj::GetPos() const
	{
		return m_Pos;
	}

	//bool Circle::DoesCollide( Circle* obj )
	//{
	//	MAPIL::Vector2 < double > diff = m_Pos - obj->m_Pos;
	//	if( diff.GetNorm() < obj->m_Radius + m_Radius ){
	//		return true;
	//	}

	//	return false;
	//}

	//bool Circle::DoesCollide( CollisionObj2D* obj )
	//{
	//	return obj->DoesCollide( this );
	//}
}