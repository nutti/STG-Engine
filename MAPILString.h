#ifndef INCLUDED_RTG_MAPILSTRING_H
#define INCLUDED_RTG_MAPILSTRING_H

#include "Defines.h"

namespace RTG
{
	class MAPILString
	{
		int			m_Textures[ 16 ];
	public:
		MAPILString();
		~MAPILString();
		void Display( char c, float x, float y ) const;
	};
}

#endif