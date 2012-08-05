#ifndef INCLUDED_RTG_CIRCLEENEMYSHOT_H
#define INCLUDED_RTG_CIRCLEENEMYSHOT_H

#include "CircleObj.h"

namespace RTG
{
	class CircleEnemyShot : public CircleObj
	{
	public:
		int		m_ImgID;
		int							m_Counter;
		double						m_Speed;
		double						m_Angle;
	public:
		CircleEnemyShot(	const MAPIL::Vector2 < double >& vPos,
							double speed,
							double angle,
							double radius );
		virtual ~CircleEnemyShot();
		virtual void Draw() = 0;
		virtual bool Move() = 0;
		void Reflect();
		int GetImgID();
	};
}

#endif