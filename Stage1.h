#ifndef INCLUDED_RTG_STAGE1_H
#define INCLUDED_RTG_STAGE1_H

#include "Defines.h"

#include "Scene.h"
#include "TaskList.hpp"
#include "CirclePlayer.h"
#include "CircleEnemy.h"
#include "CircleEnemyShot.h"
#include "CircleReflectedShot.h"
#include "Effect2D.h"
#include "Stage1Effect1.h"
#include "Loading.h"

//#include "Keyboard.h"

namespace RTG
{
	enum PlayMode
	{
		PLAY_MODE_REPLAY	= 0,
		PLAY_MODE_NORMAL	= 1,
	};

	class Stage1 : public Scene
	{
		

		int									m_Frame;
		TaskList < CirclePlayer >*			m_pPlayerList;
		TaskList < CircleEnemy >*			m_pEnemyList;
		TaskList < CircleEnemyShot >*		m_pEnemyShotList;
		TaskList < CircleReflectedShot >*	m_pReflectedShotList;
		TaskList < Effect2D >*				m_pEffect2DList;
		TaskList < Stage1Effect1 >*			m_pStage1Effect1List;
		MAPIL::Vector3 < float >			m_Pos;
		MAPIL::IPointSprite					m_PointSprite;
		MAPIL::ICamera						m_PointSpriteCamera;
		MAPIL::IStreamingBuffer				m_BossBGM;
		MAPIL::ITexture						m_PlayerEnergyBar;
		MAPIL::ITexture						m_PlayerHPBar;

		bool								m_Cleared;
		bool								m_IsGameOver;
		int									m_ClearedCounter;

		int									m_KillTotal;
		int									m_ReflectTotal;
		int									m_HitTotal;

		bool								m_Paused;

		PlayMode							m_Mode;

		Loading								m_Loading;

		void ProcessPause();


	public:
		Stage1( PlayMode mode );
		~Stage1();
		void Update();
		void Draw();
		void Sequence();
		void Init();
		bool IsLoading() const;
	};
}

#endif