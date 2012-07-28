#ifndef INCLUDED_RTG_MAPILSTRING_H
#define INCLUDED_RTG_MAPILSTRING_H

#include "Defines.h"

namespace RTG
{
	class MAPILString
	{
		MAPIL::ITexture			m_Texture;		// Texture for displaying the string.
		MAPIL::ISprite			m_Sprite;		// Sprite for displaying the string.
	public:
		MAPILString( MAPIL::ITexture texture, MAPIL::ISprite sprite );
		~MAPILString();
		void Display( char c, float x, float y ) const;
	};
}

#endif