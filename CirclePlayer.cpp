#include "CirclePlayer.h"

namespace RTG
{
	CirclePlayer::CirclePlayer( const MAPIL::Vector2 < double >& vPos, double radius ) :	CircleObj( vPos, radius ),
																							m_Counter( 0 ),
																							m_HP( 0 )
	{
	}

	CirclePlayer::~CirclePlayer()
	{
		m_Counter = 0;
		m_HP = 0;
	}
}