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

		ResourceHandler* p = ResourceHandler::GetInst();

		// 2D描画開始
		p->BeginDraw2D();

		// メニュー画面表示
		if( m_CurMenu == CONFIG_MENU_SE_VOLUME ){
			p->DrawString2D( 100, 100, 0xFFFFFFFF, "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			p->DrawString2D( 100, 120, 0xAAAAAAFF, "BGM Volume       %d", p->m_pGameManager->GetBGMVolume() );
			p->DrawString2D( 100, 140, 0xAAAAAAFF, "Button Configuration" );
			p->DrawString2D( 100, 300, 0xAAAAAAFF, "Exit" );
		}
		else if( m_CurMenu == CONFIG_MENU_BGM_VOLUME ){
			p->DrawString2D( 100, 100, 0xAAAAAAFF, "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			p->DrawString2D( 100, 120, 0xFFFFFFFF, "BGM Volume       %d", p->m_pGameManager->GetBGMVolume() );
			p->DrawString2D( 100, 140, 0xAAAAAAFF, "Button Configuration" );
			p->DrawString2D( 100, 300, 0xAAAAAAFF, "Exit" );
		}
		else if( m_CurMenu == CONFIG_MENU_BUTTON ){
			p->DrawString2D( 100, 100, 0xAAAAAAFF, "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			p->DrawString2D( 100, 120, 0xAAAAAAFF, "BGM Volume       %d", p->m_pGameManager->GetBGMVolume() );
			p->DrawString2D( 100, 140, 0xFFFFFFFF, "Button Configuration" );
			if( m_CurButtonSelectMenu != BUTTON_SELECT_NONE ){
				p->DrawString2D( 120, 160, 0xFFFFFFFF, "%s : %c", pButtons[ m_CurButtonSelectMenu ], p->m_pGBManager->GetAssignedDevButton( m_CurButtonSelectMenu ) );
			}
			p->DrawString2D( 100, 300, 0xAAAAAAFF, "Exit" );
		}
		else if( m_CurMenu == CONFIG_MENU_EXIT ){
			p->DrawString2D( 100, 100, 0xAAAAAAFF, "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			p->DrawString2D( 100, 120, 0xAAAAAAFF, "BGM Volume       %d", p->m_pGameManager->GetBGMVolume() );
			p->DrawString2D( 100, 140, 0xAAAAAAFF, "Button Configuration" );
			p->DrawString2D( 100, 300, 0xFFFFFFFF, "Exit" );
		}

		// 2D描画終了
		p->EndDraw2D();
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