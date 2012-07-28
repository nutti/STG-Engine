#ifndef INCLUDED_RTG_MAINFRAME_H
#define INCLUDED_RTG_MAINFRAME_H

#include "Defines.h"

namespace RTG
{
	class Scene;
	class MainFrame
	{
		Scene*				m_pScene;
		MAPIL::FPSManager	m_FPS;
	public:
		MainFrame();
		~MainFrame();
		void Init();
		void Run();
		void ShowLoading();
	};
}

#endif