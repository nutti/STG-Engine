#ifndef INCLUDED_RTG_BUMBEDEFFECT1_H
#define INCLUDED_RTG_BUMBEDEFFECT1_H

#include "Effect2D.h"

namespace RTG
{
	class BombedEffect1 : public Effect2D
	{
		MAPIL::Vector2 < float >		m_Pos;
		float							m_Radius;
		int								m_Count;
		double							m_Speed;
		int								m_ImgID;
	public:
		BombedEffect1(	MAPIL::Vector2 < float >& vPos,
						float radius,
						double speed,
						int imgID );
		~BombedEffect1();
		bool Update();
		void Draw();
		bool Move();
	};
}

#endif