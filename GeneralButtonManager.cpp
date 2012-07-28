#include "GeneralButtonManager.h"
#include "Defines.h"

namespace RTG
{
	inline int GetDevice( unsigned short c )
	{
		return ( c >> 8 ) & 0xFF;
	}

	inline int GetButton( unsigned short c )
	{
		return c & 0xFF;
	}

	GeneralButtonManager::GeneralButtonManager() :	m_pKeyboard( NULL ),
													m_pReplay( NULL ),
													m_CurFrame( 0 )
	{
		MAPIL::ZeroObject( m_ButtonMaps, sizeof( m_ButtonMaps ) );
		MAPIL::ZeroObject( m_IsPushedOnce, sizeof( m_IsPushedOnce ) );
		MAPIL::ZeroObject( m_IsPushed, sizeof( m_IsPushed ) );

		repmode = 0;
	}

	GeneralButtonManager::~GeneralButtonManager()
	{
		MAPIL::ZeroObject( m_ButtonMaps, sizeof( m_ButtonMaps ) );
		MAPIL::ZeroObject( m_IsPushedOnce, sizeof( m_IsPushedOnce ) );
		MAPIL::ZeroObject( m_IsPushed, sizeof( m_IsPushed ) );
		
		MAPIL::SafeDelete( m_pKeyboard );
		m_pReplay = NULL;
		m_CurFrame = 0;
	}

	void GeneralButtonManager::Init( ReplayEntry* pReplay )
	{
		m_pKeyboard = new Keyboard;
		m_pReplay = pReplay;
		m_CurFrame = 0;
	}

	void GeneralButtonManager::Assign( int button, int dev, int devButton )
	{
		m_ButtonMaps[ button ] = ( dev ) << 8 | devButton;
	}

	int GeneralButtonManager::GetAssignedDev( int button )
	{
		return ( m_ButtonMaps[ button ] >> 8 ) & 0xFF;
	}

	int GeneralButtonManager::GetAssignedDevButton( int button )
	{
		return m_ButtonMaps[ button ] & 0xFF;
	}

	void GeneralButtonManager::Update()
	{
		if( !m_pKeyboard ){
			return;
		}

		m_pKeyboard->Update();

		if( repmode == 1 ){
			int offset = REPLAY_BUTTON_TOTAL * m_CurFrame;
			for( int i = 0; i < 7; ++i ){
				m_IsPushed[ i ] = m_pReplay->m_Histories[ offset + i ];
			}
			++m_CurFrame;
		}
		else{
			for( int i = 0; i < GENERAL_BUTTON_TOTAL; ++i ){
				int dev = GetDevice( m_ButtonMaps[ i ] );			// Get device.
				int button = GetButton( m_ButtonMaps[ i ] );		// Get button.
				if( dev == INPUT_DEVICE_KEYBOARD ){
					m_IsPushed[ i ] = m_pKeyboard->IsPushed( button );
					m_IsPushedOnce[ i ] = m_pKeyboard->IsPushedOnce( button );
				}
			}
		}
	}

	void GeneralButtonManager::SetReplay( int set )
	{

		if( set == 1 ){
			for( int i = 0; i < GENERAL_BUTTON_TOTAL; ++i ){
				m_ButtonMaps[ i ] |= 0x300;
			}
			repmode = 1;
		}
		else{
			repmode = 0;
		}
	}

	bool GeneralButtonManager::IsPushedOnce( GeneralButton button ) const
	{
		return m_IsPushedOnce[ button ];
	}

	bool GeneralButtonManager::IsPushed( GeneralButton button ) const
	{
		return m_IsPushed[ button ];
	}

	void GeneralButtonManager::Reset()
	{
		m_CurFrame = 0;
	}

	void GeneralButtonManager::CopyCurState( char* pPushed ) const
	{
		for( int i = 0; i < GENERAL_BUTTON_TOTAL; ++i ){
			pPushed[ i ] = m_IsPushed[ i ];
		}
	}

}