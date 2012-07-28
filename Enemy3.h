#ifndef INCLUDED_RTG_ENEMY3_H
#define INCLUDED_RTG_ENEMY3_H

#include "CircleEnemy.h"
#include "CirclePlayer.h"

namespace RTG
{
	class Enemy3 : public CircleEnemy
	{
		CirclePlayer*	m_pPlayer;			///< Player.
		int				m_TextureIndex;		///< Index number of texture.
	public:
		Enemy3(	CirclePlayer* pPlayer,
				TaskList < CircleEnemyShot >* pList,
				MAPIL::Vector2 < double >& vPos,
				double speed,
				double angle,
				double radius,
				int hp,
				int textureIndex,
				int score );
		~Enemy3();
		void Draw();
		bool Move();
	};
}

#endif	// INCLUDED_RTG_ENEMY2_H