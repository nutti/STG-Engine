#ifndef INCLUDED_RTG_CIRCLEOBJ_H
#define INCLUDED_RTG_CIRCLEOBJ_H

#include "Defines.h"
#include "CollisionObj.h"

namespace RTG
{
	class CircleObj : public CollisionObj
	{
	public:
		MAPIL::Vector2 < double >		m_Pos;
		double							m_Radius;
	public:
		CircleObj( const MAPIL::Vector2 < double >& vPos, double radius );
		virtual ~CircleObj();
		virtual MAPIL::Vector2 < double > GetPos() const;
	};
}

#endif