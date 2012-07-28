#ifndef INCLUDED_RTG_KEYBOARD_H
#define INCLUDED_RTG_KEYBOARD_H

#include "Defines.h"

namespace RTG
{
	class Keyboard
	{
		enum KeyState
		{
			KEY_STATE_NO_PUSHED	= 0,
			KEY_STATE_ONCE		= 1,
			KEY_STATE_KEEP		= 2,
		};
		char					m_PrevKeys[ 256 ];
		MAPIL::IKeyboard		m_Keyboard;
		unsigned char			m_Keys[ 256 ];
	public:
		Keyboard( MAPIL::IKeyboard keyboard );
		~Keyboard();
		void Update();
		bool IsPushedOnce( int key ) const;
		bool IsPushed( int key ) const;
		int GetKeyPushedOnce() const;
	};
}

#endif