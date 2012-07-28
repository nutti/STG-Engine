#include "NameEntry.h"

namespace RTG
{
	NameEntry::NameEntry() : m_CurPos( 0 ), m_EffectiveCharTotal( 0 )
	{
		MAPIL::ZeroObject( m_NameChar, sizeof( m_NameChar ) );
	}

	NameEntry::~NameEntry()
	{
		m_CurPos = 0;
		m_EffectiveCharTotal = 0;
		MAPIL::ZeroObject( m_NameChar, sizeof( m_NameChar ) );
	}

	void NameEntry::SetEffectiveChar( const char* pStr )
	{
		int len = ::strlen( pStr );

		if( len >= NAME_CHAR_BUF_SIZE ){
			return;
		}
		else{
			strcpy( m_NameChar, pStr );
			m_EffectiveCharTotal = len;
		}
	}

	char NameEntry::GetCurChar() const
	{
		return m_NameChar[ m_CurPos ];
	}

	void NameEntry::Advance( int offset )
	{
		m_CurPos += offset;

		if( m_CurPos < 0 ){
			m_CurPos = m_EffectiveCharTotal - 1;
		}
		else if( m_CurPos >= m_EffectiveCharTotal ){
			m_CurPos = 0;
		}
	}

	const char* GetEffectiveChar()
	{
		const char* EFFECTIVE_CHAR = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

		return EFFECTIVE_CHAR;
	}
}