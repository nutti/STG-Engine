#include "Config.h"
#include "Menu.h"

#include "ResourceHandler.h"
#include "GeneralButtonManager.h"
#include "GameManager.h"
#include "FontString.h"

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

		FontString s;

		// メニュー画面表示
		if( m_CurMenu == CONFIG_MENU_SE_VOLUME ){
			s.Set( "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			s.Draw( 100.0f, 100.0f );
			s.Set( "BGM Volume       %d", p->m_pGameManager->GetBGMVolume() );
			s.Draw( 100.0f, 120.0f, 0xAAAAAAFF );
			//s.Set( "Button Configuration" );
			//s.Draw( 100.0f, 140.0f, 0xAAAAAAFF );
			s.Set( "Exit" );
			s.Draw( 100.0f, 300.0f, 0xAAAAAAFF );
		}
		else if( m_CurMenu == CONFIG_MENU_BGM_VOLUME ){
			s.Set( "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			s.Draw( 100.0f, 100.0f, 0xAAAAAAFF );
			s.Set( "BGM Volume       %d", p->m_pGameManager->GetBGMVolume() );
			s.Draw( 100.0f, 120.0f );
			//s.Set( "Button Configuration" );
			//s.Draw( 100.0f, 140.0f, 0xAAAAAAFF );
			s.Set( "Exit" );
			s.Draw( 100.0f, 300.0f, 0xAAAAAAFF );
		}
		else if( m_CurMenu == CONFIG_MENU_BUTTON ){
			s.Set( "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			s.Draw( 100.0f, 100.0f, 0xAAAAAAFF );
			s.Set( "BGM Volume       %d", p->m_pGameManager->GetBGMVolume() );
			s.Draw( 100.0f, 120.0f, 0xAAAAAAFF );
			s.Set( "Button Configuration" );
			s.Draw( 100.0f, 140.0f );
			if( m_CurButtonSelectMenu != BUTTON_SELECT_NONE ){
				MAPIL::DrawString( 100.0f, 160.0f, 0xFFFFFFFF, "%s : %c", pButtons[ m_CurButtonSelectMenu ], p->m_pGBManager->GetAssignedDevButton( m_CurButtonSelectMenu ) );
			}
			s.Set( "Exit" );
			s.Draw( 100.0f, 300.0f, 0xAAAAAAFF );
		}
		else if( m_CurMenu == CONFIG_MENU_EXIT ){
			s.Set( "SE Volume        %d", p->m_pGameManager->GetSEVolume() );
			s.Draw( 100.0f, 100.0f, 0xAAAAAAFF );
			s.Set( "BGM Volume       %d", p->m_pGameManager->GetBGMVolume() );
			s.Draw( 100.0f, 120.0f, 0xAAAAAAFF );
			//s.Set( "Button Configuration" );
			//s.Draw( 100.0f, 140.0f, 0xAAAAAAFF );
			s.Set( "Exit" );
			s.Draw( 100.0f, 300.0f );
		}

		// 2D描画終了
		MAPIL::EndRendering2DGraphics();
	}

	void Config::Update()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		int revisedKey = -1;

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
			else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
				if( revisedKey != -1 ){
					// ここを追加する。
					//p->m_pGBManager->Assign( m_CurButtonSelectMenu, 
					m_CurButtonSelectMenu = BUTTON_SELECT_NONE;
				}
				else{
					while( revisedKey == -1 ){
						unsigned char keys[ 256 ];
						MAPIL::GetKeyboardState( keys );
						for( int i = 0; i < sizeof( keys ); ++i ){
							if( MAPIL::HasKeyPushedStatus( keys[ i ] ) ){
								revisedKey = i;
								break;
							}
						}
						::Sleep( 1 );
					}
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
			MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_UP ) ){
			--m_CurMenu;
			if( m_CurMenu < CONFIG_MENU_SE_VOLUME ){
				m_CurMenu = CONFIG_MENU_EXIT;
			}
			MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
		}

		// 音量の調節
		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_RIGHT ) ){
			if( m_CurMenu == CONFIG_MENU_SE_VOLUME ){
				int volume = p->m_pGameManager->GetSEVolume() + 5;
				p->m_pGameManager->SetSEVolume( volume > 100 ? 100 : volume );
				MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
			}
			else if( m_CurMenu == CONFIG_MENU_BGM_VOLUME ){
				int volume = p->m_pGameManager->GetBGMVolume() + 5;
				p->m_pGameManager->SetBGMVolume( volume > 100 ? 100 : volume );
				MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
			}
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_LEFT ) ){
			if( m_CurMenu == CONFIG_MENU_SE_VOLUME ){
				int volume = p->m_pGameManager->GetSEVolume() - 5;
				p->m_pGameManager->SetSEVolume( volume < 0 ? 0 : volume );
				MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
			}
			else if( m_CurMenu == CONFIG_MENU_BGM_VOLUME ){
				int volume = p->m_pGameManager->GetBGMVolume() - 5;
				p->m_pGameManager->SetBGMVolume( volume < 0 ? 0 : volume );
				MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
			}
		}

		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_BARRIER ) ){
			// 設定終了
			if( m_CurMenu == CONFIG_MENU_EXIT ){
				p->m_pGameManager->SaveConfigFile( "config/config.dat" );
				SetNextScene( new Menu() );
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
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