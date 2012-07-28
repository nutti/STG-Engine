#include "Defines.h"

#include "ScreenShot.h"

#include <string>
#include <tchar.h>
#include <Shlwapi.h>

#pragma comment ( lib, "shlwapi.lib" )

namespace RTG
{
	static int GetDigit( int num )
	{
		int digit = 1;
		int value = num / 10;
		
		while( value ){
			value /= 10;
			++digit;
		}

		return digit;
	}

	void ScreenShot( const char* pDirPath, const char* pFileName )
	{

		for( int i = 0; i < MAXIMUM_SCREEN_SHOT; ++i ){
			int digit = GetDigit( i );
			std::basic_string < char > s( pDirPath );
			char buf[ 20 ];
			sprintf( buf, "%d", i );
			s += "/";
			s += pFileName;
			s += "_";
			for( int di = 5; di > digit; --di ){
				s += "0";
			}
			s += buf;
			s += ".bmp";
			if( !::PathFileExistsA( s.c_str() ) ){
				MAPIL::CaptureScreen( s.c_str() ); 
				return;
			}
		}
	}
}