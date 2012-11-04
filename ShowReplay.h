#ifndef INCLUDED_RTG_SHOWREPLAY_H
#define INCLUDED_RTG_SHOWREPLAY_H

#include "Defines.h"

#include "Scene.h"

namespace RTG
{
	struct DispReplayEntry
	{
		std::string		m_Name;
		int				m_Score;
		int				m_Progress;
		int				m_Year;
		int				m_Mon;
		int				m_Day;
		int				m_Hour;
		int				m_Min;
		int				m_Sec;
	};

	class ShowReplay : public Scene
	{
		char						m_Name[ 16 ];
		int							m_FileNo;
		//char						m_EntryStr[ 25 ][ 256 ];
		DispReplayEntry				m_Entry[ 25 ];
	public:
		ShowReplay();
		~ShowReplay();
		void Update();
		void Draw();
		void Init();
		bool IsLoading() const;
	};
}

#endif