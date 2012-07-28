#include "ScreenShot.h"
#include "ResourceHandler.h"

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

	void ScreenShot( const TCHAR* pDirPath, const TCHAR* pFileName )
	{

		for( int i = 0; i < MAXIMUM_SCREEN_SHOT; ++i ){
			int digit = GetDigit( i );
			std::basic_string < TCHAR > s( pDirPath );
			TCHAR buf[ 20 ];
			_stprintf_s( buf, TEXT( "%d" ), i );
			s += TEXT( "/" );
			s += pFileName;
			s += TEXT( "_" );
			for( int di = 5; di > digit; --di ){
				s += TEXT( "0" );
			}
			s += buf;
			s += TEXT( ".bmp" );
			if( !::PathFileExists( s.c_str() ) ){
				ResourceHandler* p = ResourceHandler::GetInst();
				p->m_GraphicsCtrl->CaptureScreen( s.c_str() );
				return;
			}
		}
	}
}