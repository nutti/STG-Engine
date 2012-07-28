#include "GameManager.h"

#include "ConfigManager.h"

namespace RTG
{
	GameManager::GameManager() : m_pConfigManager( NULL ), m_HasTermSig( false )
	{
	}

	GameManager::~GameManager()
	{
		MAPIL::SafeDelete( m_pConfigManager );
		m_HasTermSig = false;
	}

	void GameManager::Init()
	{
		m_pConfigManager = new ConfigManager();
	}

	bool GameManager::HasTermSig() const		// 終了シグナルを受信しているか
	{
		return m_HasTermSig;
	}

	void GameManager::SetTermSig()				// 終了シグナルをセットする
	{
		m_HasTermSig = true;
	}

	void GameManager::LoadConfigFile( const char* pFileName )
	{
		m_pConfigManager->Load( pFileName );
	}

	void GameManager::SaveConfigFile( const char* pFileName )
	{
		m_pConfigManager->Save( pFileName );
	}

	char GameManager::IsWndMode() const
	{
		return m_pConfigManager->IsWndMode();
	}

	int GameManager::GetWndWidth() const
	{
		return m_pConfigManager->GetWidth();
	}

	void GameManager::SetWndWidth( int width )
	{
		m_pConfigManager->SetWidth( width );
	}

	int GameManager::GetWndHeight() const
	{
		return m_pConfigManager->GetHeight();
	}

	void GameManager::SetWndHeight( int height )
	{
		m_pConfigManager->SetHeight( height );
	}

	void GameManager::GetButtonMaps( unsigned short* pButtonMap ) const
	{
		m_pConfigManager->GetButtonMaps( pButtonMap );
	}

	void GameManager::SetButtonMaps( unsigned short* pButtonMap )
	{
		m_pConfigManager->SetButtonMaps( pButtonMap );
	}

	int GameManager::GetSEVolume() const
	{
		return m_pConfigManager->GetSEVolume();
	}

	void GameManager::SetSEVolume( int volume )
	{
		m_pConfigManager->SetSEVolume( volume );
	}

	int GameManager::GetBGMVolume() const
	{
		return m_pConfigManager->GetBGMVolume();
	}

	void GameManager::SetBGMVolume( int volume )
	{
		m_pConfigManager->SetBGMVolume( volume );
	}
}