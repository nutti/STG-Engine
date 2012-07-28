#include "Config.h"
#include "Menu.h"

#include "ResourceHandler.h"
#include "GeneralButtonManager.h"
#include "GameManager.h"

#include "Util.h"

namespace RTG
{
	Config::Config() :	m_CurMenu( CONFIG_MENU_SE_VOLUME ),
						m_CurButtonSelectMenu( BUTTON_SELECT_NONE )
	{
	}

	Config::~Config()
	{
	}

	void Config::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		const char* pButtons[ 10 ] = {	"UP",
										"DOWN",
										"RIGHT",
										"LEFT",
										"BARRIER",
										"ROT_CW",
										"ROT_CCW",
										"CANCEL",
										"PAUSE",
										"ENTER" };

		// 2D描画開始
		MAPIL::BeginRendering2DGraphics();

		// メニュー画面表示
		if( m_CurMenu == CONFIG_MENU_SE_VOLUME ){
			MAPIL::DrawString( 100.0f, 100.0f, 0xFFFFFFFF, "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			MAPIL::DrawString( 100.0f, 120.0f, 0xAAAAAAFF, "BGM Volume        %d", p->m_pGameManager->GetBGMVolume() );
			MAPIL::DrawString( 100.0f, 140.0f, 0xAAAAAAFF, "Button Configuration" );
			MAPIL::DrawString( 100.0f, 300.0f, 0xAAAAAAFF, "Exit" );
		}
		else if( m_CurMenu == CONFIG_MENU_BGM_VOLUME ){
			MAPIL::DrawString( 100.0f, 100.0f, 0xAAAAAAFF, "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			MAPIL::DrawString( 100.0f, 120.0f, 0xFFFFFFFF, "BGM Volume        %d", p->m_pGameManager->GetBGMVolume() );
			MAPIL::DrawString( 100.0f, 140.0f, 0xAAAAAAFF, "Button Configuration" );
			MAPIL::DrawString( 100.0f, 300.0f, 0xAAAAAAFF, "Exit" );
		}
		else if( m_CurMenu == CONFIG_MENU_BUTTON ){
			MAPIL::DrawString( 100.0f, 100.0f, 0xAAAAAAFF, "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			MAPIL::DrawString( 100.0f, 120.0f, 0xAAAAAAFF, "BGM Volume        %d", p->m_pGameManager->GetBGMVolume() );
			MAPIL::DrawString( 100.0f, 140.0f, 0xFFFFFFFF, "Button Configuration" );
			if( m_CurButtonSelectMenu != BUTTON_SELECT_NONE ){
				MAPIL::DrawString( 100.0f, 160.0f, 0xFFFFFFFF, "%s : %c", pButtons[ m_CurButtonSelectMenu ], p->m_pGBManager->GetAssignedDevButton( m_CurButtonSelectMenu ) );
			}
			MAPIL::DrawString( 100.0f, 300.0f, 0xAAAAAAFF, "Exit" );
		}
		else if( m_CurMenu == CONFIG_MENU_EXIT ){
			MAPIL::DrawString( 100.0f, 100.0f, 0xAAAAAAFF, "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			MAPIL::DrawString( 100.0f, 120.0f, 0xAAAAAAFF, "BGM Volume        %d", p->m_pGameManager->GetBGMVolume() );
			MAPIL::DrawString( 100.0f, 140.0f, 0xAAAAAAFF, "Button Configuration" );
			MAPIL::DrawString( 100.0f, 300.0f, 0xFFFFFFFF, "Exit" );
		}

		// 2D描画終了
		MAPIL::EndRendering2DGraphics();
	}

	void Config::Update()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		// ボタン変更の時は、特別モードに入る
		if( m_CurButtonSelectMenu != BUTTON_SELECT_NONE ){
			if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_LEFT ) ){
				++m_CurButtonSelectMenu;
				if( m_CurButtonSelectMenu > BUTTON_SELECT_ROT_CCW ){
					m_CurButtonSelectMenu = BUTTON_SELECT_UP;
				}
			}
			else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_RIGHT ) ){
				--m_CurButtonSelectMenu;
				if( m_CurButtonSelectMenu < BUTTON_SELECT_UP ){
					m_CurButtonSelectMenu = BUTTON_SELECT_ROT_CCW;
				}
			}
			else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
				m_CurButtonSelectMenu = BUTTON_SELECT_NONE;
			}
			return;
		}

		// カーソルの変更
		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_DOWN ) ){
			++m_CurMenu;
			if( m_CurMenu > CONFIG_MENU_EXIT ){
				m_CurMenu = CONFIG_MENU_SE_VOLUME;
			}
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_UP ) ){
			--m_CurMenu;
			if( m_CurMenu < CONFIG_MENU_SE_VOLUME ){
				m_CurMenu = CONFIG_MENU_EXIT;
			}
		}

		// 音量の調節
		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_RIGHT ) ){
			if( m_CurMenu == CONFIG_MENU_SE_VOLUME ){
				int volume = p->m_pGameManager->GetSEVolume() + 5;
				p->m_pGameManager->SetSEVolume( volume > 100 ? 100 : volume );
			}
			else if( m_CurMenu == CONFIG_MENU_BGM_VOLUME ){
				int volume = p->m_pGameManager->GetBGMVolume() + 5;
				p->m_pGameManager->SetBGMVolume( volume > 100 ? 100 : volume );
			}
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_LEFT ) ){
			if( m_CurMenu == CONFIG_MENU_SE_VOLUME ){
				int volume = p->m_pGameManager->GetSEVolume() - 5;
				p->m_pGameManager->SetSEVolume( volume < 0 ? 0 : volume );
			}
			else if( m_CurMenu == CONFIG_MENU_BGM_VOLUME ){
				int volume = p->m_pGameManager->GetBGMVolume() - 5;
				p->m_pGameManager->SetBGMVolume( volume < 0 ? 0 : volume );
			}
		}

		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_BARRIER ) ){
			// 設定終了
			if( m_CurMenu == CONFIG_MENU_EXIT ){
				p->m_pGameManager->SaveConfigFile( "config/config.dat" );
				SetNextScene( new Menu() );
			}
			else if( m_CurMenu == CONFIG_MENU_BUTTON ){
				m_CurButtonSelectMenu = BUTTON_SELECT_BARRIER;
			}
		}
	}

	void Config::Init()
	{
	}

	bool Config::IsLoading() const
	{
		return false;
	}

}