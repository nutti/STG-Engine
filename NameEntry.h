#ifndef INCLUDED_RTG_NAMEENTRY_H
#define INCLUDED_RTG_NAMEENTRY_H

#include "Defines.h"

namespace RTG
{

	const int NAME_CHAR_BUF_SIZE = 128;
	

	class NameEntry
	{
	private:
		int			m_CurPos;							// 現在選択中の文字
		int			m_EffectiveCharTotal;				// 有効な文字数
		char		m_NameChar[ NAME_CHAR_BUF_SIZE ];		// 名前に使用できる文字
	public:
		NameEntry();
		~NameEntry();
		void SetEffectiveChar( const char* pStr );
		char GetCurChar() const;
		void Advance( int offset );
	};

	const char* GetEffectiveChar();
}

#endif