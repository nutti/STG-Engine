#ifndef INCLUDED_RTG_CIRCLEPLAYER_H
#define INCLUDED_RTG_CIRCLEPLAYER_H

#include "CircleObj.h"

namespace RTG
{
	class CirclePlayer : public CircleObj
	{
	protected:
		int		m_Counter;
		int		m_HP;
	public:
		CirclePlayer( const MAPIL::Vector2 < double >& vPos, double radius );
		virtual ~CirclePlayer();
		virtual void Draw() = 0;
		virtual bool Move() = 0;
	};
}

#endif