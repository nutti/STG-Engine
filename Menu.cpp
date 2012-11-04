#include "Menu.h"
#include "ScriptedStage.h"
#include "Config.h"
#include "History.h"
#include "MenuEffect1.h"
#include "GeneralButtonManager.h"
#include "SaveDataManager.h"
#include "GameManager.h"
#include "FontString.h"

#include "EntryScore.h"
#include "ShowReplay.h"

namespace RTG
{
	

	Menu::Menu() :	Scene(),
					m_PointSprite(),
					m_Camera3D(),
					m_Counter( 0 ),
					m_pEffect3DList( NULL ),
					m_SelectedMenuItem( MENU_ITEM_PLAY_GAME ),
					m_StateChangeCounter( 0 ),
					m_NextMenuItem( MENU_ITEM_PLAY_GAME ),
					m_NameEntry()
	{
	}

	Menu::~Menu()
	{
		DeleteTaskList( m_pEffect3DList );
		m_Counter = 0;
		MAPIL::SafeDelete( m_pEffect3DList );
		m_StateChangeCounter = 0;
		MAPIL::DeleteTexture( m_Texture[ 0 ] );
		MAPIL::DeletePointSprite( m_PointSprite );
		MAPIL::DeleteCamera( m_Camera3D );
	}

	void Menu::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		MAPIL::RefleshResources();

		m_Texture[ 0 ] = MAPIL::CreateTexture( p->m_Archiver, "archive/resource/texture/MenuEffect2.png" );

		//m_BGM = MAPIL::CreateStreamingBuffer( p->m_Archiver, "archive/resource/bgm/rtg_title.wav" );

		//m_SelectSE = MAPIL::CreateStaticBuffer( p->m_Archiver, "archive/resource/se/select.wav" );

		//m_MoveSE = MAPIL::CreateStaticBuffer( p->m_Archiver, "archive/resource/se/move.wav" );

		m_PointSprite = MAPIL::CreatePointSprite( 200, m_Texture[ 0 ] );

		m_Camera3D = MAPIL::CreateCamera();
		MAPIL::SetCameraViewTrans(	m_Camera3D,
									0.0f, 0.0f, 10.0f,
									0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f );
		MAPIL::SetCameraProjTrans(	m_Camera3D,
									static_cast < float > ( MAPIL::DegToRad( 30.0 ) ),
									640.0f / 480.0f,
									0.01f, 20.0f );
									


		m_NameEntry.SetEffectiveChar( GetEffectiveChar() );

		m_pEffect3DList = new TaskList < MenuEffect1 > ();
		m_pEffect3DList->Init();

		
		for( int i = 0; i < 200; ++i ){
			m_pEffect3DList->Add( new MenuEffect1(	m_PointSprite,
													MAPIL::Vector3 < float > (	-1.0f + 2.0f * rand() / RAND_MAX,
																				5.0f + 10.0f * rand() / RAND_MAX,
																				-1.0f - 3.0f * rand() / RAND_MAX ),
													0.01 + 0.02 * rand() / RAND_MAX,
													MAPIL::DegToRad( -180.0 * rand() / RAND_MAX ),
													i ) );
		}
		
		MAPIL::PlayStreamingBuffer( p->m_MenuBGM );
	}

	bool Menu::IsLoading() const
	{
		return false;
	}

	void Menu::Update()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		// For testing.
		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
			SetNextScene( new ScriptedStage( p->m_pCompiler, 1, PLAY_MODE_NORMAL ) );
			return;
		}
		
		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_DOWN ) ){
			++m_SelectedMenuItem;
			if( m_SelectedMenuItem > MENU_ITEM_EXIT ){
				m_SelectedMenuItem = MENU_ITEM_PLAY_GAME;
			}
			MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_UP ) ){
			--m_SelectedMenuItem;
			if( m_SelectedMenuItem < MENU_ITEM_PLAY_GAME ){
				m_SelectedMenuItem = MENU_ITEM_EXIT;
			}
			MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_BARRIER ) ){
			if( m_SelectedMenuItem == MENU_ITEM_PLAY_GAME ){
				SetNextScene( new ScriptedStage( p->m_pCompiler, 1, PLAY_MODE_NORMAL ) );
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
				MAPIL::StopStreamingBuffer( p->m_MenuBGM );
			}
			else if( m_SelectedMenuItem == MENU_ITEM_REPLAY ){
				SetNextScene( new ShowReplay() );
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
			}
			else if( m_SelectedMenuItem == MENU_ITEM_SCORE ){
				m_NextMenuItem = MENU_ITEM_SCORE;
				m_StateChangeCounter = 1;
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
			}
			else if( m_SelectedMenuItem == MENU_ITEM_CONFIG ){
				SetNextScene( new Config() );
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
			}
			else if( m_SelectedMenuItem == MENU_ITEM_EXIT ){
				p->m_pGameManager->SetTermSig();
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
			}
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
			if( m_SelectedMenuItem == MENU_ITEM_EXIT ){
				p->m_pGameManager->SetTermSig();
			}
			m_SelectedMenuItem = MENU_ITEM_EXIT;
			MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
		}

		TaskList < MenuEffect1 > ::Iterator itEffect3D( m_pEffect3DList );
		TaskList < MenuEffect1 > ::Iterator itEffect3DEnd( m_pEffect3DList );

		itEffect3DEnd.End();
		
		for( itEffect3D.Begin(); itEffect3D != itEffect3DEnd; ++itEffect3D ){
			if( !( *itEffect3D ).Update() ){
				int index = ( *itEffect3D ).GetIndex();
				itEffect3D.Remove();
				m_pEffect3DList->Add( new MenuEffect1(	m_PointSprite,
														MAPIL::Vector3 < float > (	-1.0f + 2.0f * rand() / RAND_MAX,
																					5.0f + 10.0f * rand() / RAND_MAX,
																					-1.0f - 3.0f * rand() / RAND_MAX ),
														0.01f + 0.02f * rand() / RAND_MAX,
														MAPIL::DegToRad( -180.0 * rand() / RAND_MAX ),
														index ) );
			}
		}

		// ƒƒjƒ…[•\Ž¦
		const float MENU_POS_BASE_X = 420.0f;
		const float MENU_POS_BASE_Y = 310.0f;
		const float MENU_POS_OFFSET_X = 10.0f;
		const float MENU_POS_OFFSET_Y = 20.0f;

		if( m_StateChangeCounter >= 1 ){
			++m_StateChangeCounter;
		}
		if( m_StateChangeCounter > 60 ){
			if( m_NextMenuItem == MENU_ITEM_SCORE ){
				SetNextScene( new History() );
			}
		}

		++m_Counter;
	}

	void Menu::Draw()
	{
		MAPIL::BeginRendering2DGraphics();

		ResourceHandler* p = ResourceHandler::GetInst();
		MAPIL::DrawTexture( p->m_TitleTexture, 300.0f, 180.0f, 0.0f );
		for( int i = 0; i < 5; ++i ){
			if( m_SelectedMenuItem == i ){
				MAPIL::DrawTexture( p->m_MenuTexture[ i ], 350.0f + 10.0f * i, 320.0f + 30.0f * i, 0.0f );
			}
			else{
				MAPIL::DrawTexture( p->m_MenuTexture[ i + 5 ], 350.0f + 10.0f * i, 320.0f + 30.0f * i, 0.0f );
			}
		}

		MAPIL::EndRendering2DGraphics();

		MAPIL::EnableCamera( m_Camera3D );

		MAPIL::DisableZBuffering();

		MAPIL::DrawPointSprite( m_PointSprite );

		MAPIL::EnableZBuffering();

		
	}

	
}