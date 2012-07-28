#ifndef INCLUDED_RTG_ENEMY1_H
#define INCLUDED_RTG_ENEMY1_H

#include "CircleEnemy.h"
#include "CirclePlayer.h"

namespace RTG
{
	class Enemy1 : public CircleEnemy
	{
		CirclePlayer*	m_pPlayer;
		int				m_TextureIndex;
	public:
		Enemy1(	CirclePlayer* pPlayer,
				TaskList < CircleEnemyShot >* pList,
				MAPIL::Vector2 < double >& vPos,
				double speed,
				double angle,
				double radius,
				int hp,
				int textureIndex,
				int score );
		~Enemy1();
		void Draw();
		bool Move();
	};
}

#endif