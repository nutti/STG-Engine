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
		MAPIL::ISprite					m_Sprite;
		MAPIL::ITexture					m_Texture;
	public:
		BombedEffect1(	MAPIL::ISprite sprite,
						MAPIL::ITexture texture,
						MAPIL::Vector2 < float >& vPos,
						float radius,
						double speed );
		~BombedEffect1();
		bool Update();
		void Draw();
		bool Move();
	};
}

#endif