#ifndef INCLUDED_RTG_MENU_H
#define INCLUDED_RTG_MENU_H

#include "Defines.h"
#include "TaskList.hpp"
#include "MenuEffect1.h"
#include "NameEntry.h"

#include "Scene.h"

namespace RTG
{
	class Menu : public Scene
	{
		enum MenuItem
		{
			MENU_ITEM_PLAY_GAME		= 0,
			MENU_ITEM_REPLAY		= 1,
			MENU_ITEM_SCORE			= 2,
			MENU_ITEM_CONFIG		= 3,
			MENU_ITEM_EXIT			= 4,
		};

		MAPIL::IPointSprite			m_PointSprite;
		MAPIL::ITexture				m_Texture[ 2 ];
		MAPIL::ICamera				m_Camera2D;
		MAPIL::ICamera				m_Camera3D;
		int							m_Counter;
		TaskList < MenuEffect1 >*	m_pEffect3DList;
		MAPIL::IStreamingBuffer		m_BGM;
		MAPIL::IStaticBuffer		m_SelectSE;
		MAPIL::IStaticBuffer		m_MoveSE;
		int							m_SelectedMenuItem;
		NameEntry					m_NameEntry;
		int							m_StateChangeCounter;			// 状態遷移専用カウンター
		int							m_NextMenuItem;					// 次に遷移するシーン
	public:
		Menu();
		~Menu();
		void Update();
		void Draw();
		void Init();
		bool IsLoading() const;
	};
}

#endif