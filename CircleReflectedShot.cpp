#include "CircleReflectedShot.h"

namespace RTG
{
	CircleReflectedShot::CircleReflectedShot(	const MAPIL::Vector2 < double >& vPos,
												double speed,
												double angle,
												double radius ) :	CircleObj( vPos, radius ),
																	m_Counter( 0 ),
																	m_Speed( speed ),
																	m_Angle( angle )
	{
	}

	CircleReflectedShot::~CircleReflectedShot()
	{
	}
}