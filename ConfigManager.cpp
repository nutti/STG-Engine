#include "ConfigManager.h"

#include <fstream>

namespace RTG
{
	ConfigManager::ConfigManager()
	{
	}

	ConfigManager::~ConfigManager()
	{
	}

	void ConfigManager::Load( const char* pFileName )
	{
		std::ifstream fIn( pFileName, std::ios::binary | std::ios::in );

		fIn.read( &m_IsWndMode, sizeof( m_IsWndMode ) );
		fIn.read( (char*)&m_Width, sizeof( m_Width ) );
		fIn.read( (char*)&m_Height, sizeof( m_Height ) );
		fIn.read( (char*)m_ButtonMaps, sizeof( m_ButtonMaps ) );
		fIn.read( (char*)&m_SEVolume, sizeof( m_SEVolume ) );
		fIn.read( (char*)&m_BGMVolume, sizeof( m_BGMVolume ) );

		fIn.close();
	}

	void ConfigManager::Save( const char* pFileName )
	{
		std::ofstream fOut( pFileName, std::ios::binary | std::ios::out );

		fOut.write( &m_IsWndMode, sizeof( m_IsWndMode ) );
		fOut.write( (char*)&m_Width, sizeof( m_Width ) );
		fOut.write( (char*)&m_Height, sizeof( m_Height ) );
		fOut.write( (char*)m_ButtonMaps, sizeof( m_ButtonMaps ) );
		fOut.write( (char*)&m_SEVolume, sizeof( m_SEVolume ) );
		fOut.write( (char*)&m_BGMVolume, sizeof( m_BGMVolume ) );

		fOut.close();
	}

	char ConfigManager::IsWndMode() const
	{
		return m_IsWndMode;
	}

	void ConfigManager::SetWndMode( char wndMode )
	{
		m_IsWndMode = wndMode;
	}

	int ConfigManager::GetWidth() const
	{
		return m_Width;
	}

	void ConfigManager::SetWidth( int width )
	{
		m_Width = width;
	}

	int ConfigManager::GetHeight() const
	{
		return m_Height;
	}

	void ConfigManager::SetHeight( int height )
	{
		m_Height = height;
	}

	void ConfigManager::GetButtonMaps( unsigned short* pButtonMap ) const
	{
		::memcpy( pButtonMap, m_ButtonMaps, sizeof( m_ButtonMaps ) );
	}

	void ConfigManager::SetButtonMaps( unsigned short* pButtonMap )
	{
		::memcpy( m_ButtonMaps, pButtonMap, sizeof( m_ButtonMaps ) );
	}

	int ConfigManager::GetSEVolume() const
	{
		return m_SEVolume;
	}

	void ConfigManager::SetSEVolume( int volume )
	{
		m_SEVolume = volume;
	}

	int ConfigManager::GetBGMVolume() const
	{
		return m_BGMVolume;
	}

	void ConfigManager::SetBGMVolume( int volume )
	{
		m_BGMVolume = volume;
	}
}