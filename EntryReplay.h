#ifndef INCLUDED_RTG_ENTRYREPLAY_H
#define INCLUDED_RTG_ENTRYREPLAY_H

#include "Defines.h"

#include "Scene.h"
#include "NameEntry.h"
#include "ShowReplay.h"


namespace RTG
{
	class EntryReplay : public Scene
	{
		int							m_Score;
		char						m_Name[ 16 ];
		int							m_Date;
		int							m_Progress;
		int							m_NameLen;
		int							m_FileNo;
		bool						m_Selected;
		//char						m_EntryStr[ 25 ][ 256 ];
		DispReplayEntry				m_Entry[ 25 ];
		NameEntry					m_NameEntry;
	public:
		EntryReplay( int score, int progress );
		~EntryReplay();
		void Update();
		void Draw();
		void Init();
		bool IsLoading() const;
	};
}

#endif