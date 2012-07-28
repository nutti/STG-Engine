#ifndef INCLUDED_RTG_REPLAYSAVER_H
#define INCLUDED_RTG_REPLAYSAVER_H

#include "ReplayLoader.h"

namespace RTG
{
	class ReplaySaver
	{
	private:
		ReplayEntry			m_Entry;
		int					m_CurFrame;
		char				m_Name[ 16 ];
		int					m_Score;
		int					m_Progress;
		::time_t			m_Date;
	public:
		ReplaySaver();
		~ReplaySaver();
		void Save(	const char* pFileName,
					const char* pName,
					int score,
					int progress);
		void Add( char* pEntry );
		void Reset();
	};
}

#endif