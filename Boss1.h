#ifndef INCLUDED_RTG_BOSS1_H
#define INCLUDED_RTG_BOSS1_H

#include "CircleEnemy.h"
#include "CirclePlayer.h"

namespace RTG
{
	class Boss1 : public CircleEnemy
	{
		CirclePlayer*			m_pPlayer;
		int						m_TextureIndex;
		int						m_Stage;
		MAPIL::ITexture			m_HPBar;
	public:
		Boss1(	CirclePlayer* pPlayer,
				TaskList < CircleEnemyShot >* pList,
				int textureIndex,
				MAPIL::ITexture hpBar );
		~Boss1();
		void Draw();
		bool Move();
	};
}

#endif