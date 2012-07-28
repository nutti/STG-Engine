#include "Keyboard.h"
#include "Defines.h"

namespace RTG
{
	Keyboard::Keyboard( MAPIL::IKeyboard keyboard ) : m_Keyboard( keyboard )
	{
		MAPIL::ZeroObject( m_PrevKeys, sizeof( m_PrevKeys ) );
		MAPIL::ZeroObject( m_Keys, sizeof( m_Keys ) );
	}

	Keyboard::~Keyboard()
	{
		MAPIL::ZeroObject( m_PrevKeys, sizeof( m_PrevKeys ) );
		MAPIL::ZeroObject( m_Keys, sizeof( m_Keys ) );
	}

	void Keyboard::Update()
	{
		m_Keyboard->GetKeyMap( m_Keys );

		for( int i = 0; i < 256; ++i ){
			if( MAPIL::IsKeyPushed( m_Keys[ i ] ) ){
				if( m_PrevKeys[ i ] == KEY_STATE_ONCE ){
					m_PrevKeys[ i ] = KEY_STATE_KEEP;
				}
				else if( m_PrevKeys[ i ] == KEY_STATE_NO_PUSHED ){
					m_PrevKeys[ i ] = KEY_STATE_ONCE;
				}
			}
			else{
				m_PrevKeys[ i ] = KEY_STATE_NO_PUSHED;
			}
		}
	}

	bool Keyboard::IsPushedOnce( int key ) const
	{
		return m_PrevKeys[ key ] == KEY_STATE_ONCE ? true : false;
	}

	bool Keyboard::IsPushed( int key ) const
	{
		return m_PrevKeys[ key ] == KEY_STATE_NO_PUSHED ? false : true;
	}

	int Keyboard::GetKeyPushedOnce() const
	{
		for( int i = 0; i < 256; ++i ){
			if( m_PrevKeys[ i ] == KEY_STATE_ONCE ){
				return i;
			}
		}

		return -1;
	}
}