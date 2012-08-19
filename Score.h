#ifndef INCLUDED_RTG_SCORE_H
#define INCLUDED_RTG_SCORE_H

#include "Defines.h"

#include "MAPILString.h"

namespace RTG
{
	class Score
	{
		MAPILString				m_MAPILString;	// MAPIL String.
		int						m_Score;
		int						m_RestScore;
	public:
		Score();
		~Score();
		void Display( float x, float y, float offset, int digit ) const;
		void Add( int score );
		void Set( int score );
		int Get() const;
		void Update();
	};
}

#endif