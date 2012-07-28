#ifndef INCLUDED_RTG_ENEMY2_H
#define INCLUDED_RTG_ENEMY2_H

#include "CircleEnemy.h"
#include "CirclePlayer.h"

namespace RTG
{
	class Enemy2 : public CircleEnemy
	{
		CirclePlayer*	m_pPlayer;			///< Player.
		int				m_TextureIndex;		///< Index number of texture.
	public:
		Enemy2(	CirclePlayer* pPlayer,
				TaskList < CircleEnemyShot >* pList,
				MAPIL::Vector2 < double >& vPos,
				double speed,
				double angle,
				double radius,
				int hp,
				int textureIndex,
				int score );
		~Enemy2();
		void Draw();
		bool Move();
	};
}

#endif	// INCLUDED_RTG_ENEMY2_H