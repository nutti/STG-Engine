#ifndef INCLUDED_RTG_CIRCLEREFLECTEDSHOT_H
#define INCLUDED_RTG_CIRCLEREFLECTEDSHOT_H

#include "CircleObj.h"

namespace RTG
{
	class CircleReflectedShot : public CircleObj
	{
	protected:
		int			m_Counter;
		double		m_Speed;
		double		m_Angle;
	public:
		CircleReflectedShot(	const MAPIL::Vector2 < double >& vPos,
								double speed,
								double angle,
								double radius );
		virtual ~CircleReflectedShot();
		virtual void Draw() = 0;
		virtual bool Move() = 0;
	};
}

#endif