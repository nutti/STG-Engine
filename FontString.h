#ifndef INCLUDED_RTG_FONTSTRING_H
#define INCLUDED_RTG_FONTSTRING_H

#include <string>

namespace RTG
{
	class FontString
	{
	private:
		std::string				m_Str;
	public:
		FontString();
		~FontString();
		void Set( const char* pStr, ... );
		void Set( const std::string& str );
		void Draw( float x, float y, int color = 0xFFFFFFFF );
		void Draw( float x, float y, float scale, int color );
	};
}

#endif