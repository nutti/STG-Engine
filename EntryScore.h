#ifndef INCLUDED_RTG_ENTRYSCORE_H
#define INCLUDED_RTG_ENTRYSCORE_H

#include "Defines.h"

#include "Scene.h"
#include "NameEntry.h"

namespace RTG
{
	class EntryScore : public Scene
	{
		int							m_Score;
		char						m_Name[ 16 ];
		int							m_Date;
		int							m_Progress;
		int							m_NameLen;
		NameEntry					m_NameEntry;
	public:
		EntryScore( int score, int progress );
		~EntryScore();
		void Update();
		void Draw();
		void Init();
		bool IsLoading() const;
	};
}

#endif