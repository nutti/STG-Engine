#ifndef INCLUDED_RTG_UTIL_H
#define INCLUDED_RTG_UTIL_H

#include "Defines.h"

namespace RTG
{
	void DrawString2D( MAPIL::ISprite s, MAPIL::IGraphicsFont f, float x, float y, const char* pStr );

	void DrawString2D( MAPIL::ISprite s, MAPIL::IGraphicsFont f, float x, float y, int color, const char* pStr );

	MAPIL::MapilTChar* ToTCHAR( const char* pStr );
}

#endif