#include "Util.h"


namespace RTG
{

	void DrawString2D( MAPIL::ISprite s, MAPIL::IGraphicsFont f, float x, float y, const char* pStr )
	{
		TCHAR tstr[ 1024 ];
		MAPIL::ConvertToTChar( pStr, 1024, tstr, 1024 );

		s->DrawString(	f,
						tstr,
						MAPIL::IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE,
						MAPIL::Vector2 < float > ( x, y ),
						0xFFFFFFFF );
	}

	void DrawString2D( MAPIL::ISprite s, MAPIL::IGraphicsFont f, float x, float y, int color, const char* pStr )
	{
		TCHAR tstr[ 1024 ];
		MAPIL::ConvertToTChar( pStr, 1024, tstr, 1024 );

		s->DrawString(	f,
						tstr,
						MAPIL::IMAGE_TRANSFORMATION_METHOD_CENTER_MOVE,
						MAPIL::Vector2 < float > ( x, y ),
						color );
	}

	MAPIL::MapilTChar* ToTCHAR( const char* pStr )
	{
		static TCHAR tstr[ 1024 ];
		MAPIL::ConvertToTChar( pStr, 1024, tstr, 1024 );

		return tstr;
	}
}