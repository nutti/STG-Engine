#include "FontString.h"
#include "ResourceHandler.h"

#include <stdarg.h>
#include <stdio.h>

namespace RTG
{
	FontString::FontString() : m_Str()
	{
	}

	FontString::~FontString()
	{
	}

	void FontString::Set( const char* pStr, ... )
	{
		char buf[ 1024 ];
		::va_list list;
		va_start( list, pStr );
		if( vsprintf( buf, pStr, list ) + 1 > 1024 ){
			return;
		}
		va_end( list );

		m_Str = buf;
	}

	void FontString::Set( const std::string& str )
	{
		m_Str = str;
	}

	void FontString::Draw( float x, float y, int color )
	{
		ResourceHandler* p = ResourceHandler::GetInst();
		for( int i = 0; i < m_Str.size(); ++i ){
			if( ::isdigit( m_Str[ i ] ) ){
				MAPIL::DrawTexture( p->m_GameFont[ 'Z' - 'A' + 1 - '0' + m_Str[ i ] ], x + i * 13.0f, y, 0.4f, 0.4f, 0.0f, color );
			}
			else if( ::isalpha( m_Str[ i ] ) ){
				MAPIL::DrawTexture( p->m_GameFont[ ::toupper( m_Str[ i ] ) - 'A' ], x + i * 13.0f, y, 0.4f, 0.4f, 0.0f, color );
			}
		}
	}

	void FontString::Draw( float x, float y, float scale, int color )
	{
		ResourceHandler* p = ResourceHandler::GetInst();
		for( int i = 0; i < m_Str.size(); ++i ){
			if( ::isdigit( m_Str[ i ] ) ){
				MAPIL::DrawTexture( p->m_GameFont[ 'Z' - 'A' + 1 - '0' + m_Str[ i ] ], x + i * 32.0f * scale, y, scale, scale, 0.0f, color );
			}
			else if( ::isalpha( m_Str[ i ] ) ){
				MAPIL::DrawTexture( p->m_GameFont[ ::toupper( m_Str[ i ] ) - 'A' ], x + i * 32.0f, y, scale, scale, 0.0f, color );
			}
		}
	}

}