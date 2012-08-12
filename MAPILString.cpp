#include "MAPILString.h"

namespace RTG
{
	MAPILString::MAPILString( MAPIL::ITexture texture, MAPIL::ISprite sprite ) :	m_Texture( texture ),
																					m_Sprite( sprite )
	{
	}

	MAPILString::MAPILString() :	m_Texture(),
									m_Sprite()
	{
	}

	MAPILString::~MAPILString()
	{
	}

	void MAPILString::Display( char c, float x, float y ) const
	{
		if( c >= '0' && c <= '9' ){
			m_Texture->SetSplitIndex( c - '0' );
			m_Sprite->DrawTexture(	m_Texture,
									MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE,
									MAPIL::Vector2 < float > ( x, y ) );
		}
	}
}