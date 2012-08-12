#include "Score.h"

namespace RTG
{
	Score::Score( MAPIL::ITexture texture, MAPIL::ISprite sprite ) :	m_MAPILString( texture, sprite ),
																		m_Score( 0 ),
																		m_RestScore( 0 )
	{
	}

	Score::Score() :	m_MAPILString(),
						m_Score( 0 ),
						m_RestScore( 0 )
	{
	}

	Score::~Score()
	{
		m_Score = 0;
		m_RestScore = 0;
	}

	void Score::Display( float x, float y, float offset, int digit ) const
	{
		int dispScore = m_Score;
		for( int i = 0; i < digit; ++i ){
			m_MAPILString.Display( ( dispScore % 10 ) + '0', x - i * offset, y );
			dispScore /= 10;
		}
	}

	void Score::Add( int score )
	{
		m_RestScore += score;
	}

	void Score::Set( int score )
	{
		m_Score = score;
		m_RestScore = 0;
	}

	int Score::Get() const
	{
		return m_Score;
	}

	void Score::Update()
	{
		if( m_RestScore >= 50000 ){
			m_Score += 50000;
			m_RestScore -= 50000;
		}
		else if( m_RestScore >= 5000 ){
			m_Score += 5000;
			m_RestScore -= 5000;
		}
		else if( m_RestScore >= 50 ){
			m_Score += 50;
			m_RestScore -= 50;
		}
		else{
			m_Score += m_RestScore;
			m_RestScore = 0;
		}
	}
}