#include "Menu.h"
#include "ScriptedStage.h"
#include "Config.h"
#include "History.h"
#include "MenuEffect1.h"
#include "GeneralButtonManager.h"
#include "SaveDataManager.h"
#include "GameManager.h"

#include "EntryScore.h"
#include "ShowReplay.h"

namespace RTG
{
	

	Menu::Menu() :	Scene(),
					m_PointSprite(),
					m_Camera3D(),
					m_Counter( 0 ),
					m_pEffect3DList( NULL ),
					m_BGM(),
					m_SelectedMenuItem( MENU_ITEM_PLAY_GAME ),
					m_StateChangeCounter( 0 ),
					m_NextMenuItem( MENU_ITEM_PLAY_GAME ),
					m_SelectSE(),
					m_NameEntry()
	{
	}

	Menu::~Menu()
	{
		MAPIL::StopStreamingBuffer( m_BGM );
		DeleteTaskList( m_pEffect3DList );
		m_Counter = 0;
		MAPIL::SafeDelete( m_pEffect3DList );
		m_StateChangeCounter = 0;
	}

	void Menu::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		MAPIL::RefleshResources();

		m_Texture[ 0 ] = MAPIL::CreateTexture( "Resource/MenuEffect2.png" );

		m_BGM = MAPIL::CreateStreamingBuffer( "Resource/rtg_title.wav" );

		m_SelectSE = MAPIL::CreateStaticBuffer( "Resource/select.wav" );

		m_MoveSE = MAPIL::CreateStaticBuffer( "Resource/move.wav" );

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
			//m_pEffect3DList->Add( new MenuEffect1(	m_PointSprite,
			//										MAPIL::Vector3 < float > (	-1.0f + 2.0f * rand() / RAND_MAX,
			//																	5.0f + 10.0f * rand() / RAND_MAX,
			//																	-1.0f - 3.0f * rand() / RAND_MAX ),
			//										0.01 + 0.02 * rand() / RAND_MAX,
			//										MAPIL::DegToRad( -180.0 * rand() / RAND_MAX ),
			//										i ) );
		}
		
		MAPIL::PlayStreamingBuffer( m_BGM );
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
			SetNextScene( new ScriptedStage( p->m_pCompiler, 1 ) );
			return;
		}
		
		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_DOWN ) ){
			++m_SelectedMenuItem;
			if( m_SelectedMenuItem > MENU_ITEM_EXIT ){
				m_SelectedMenuItem = MENU_ITEM_PLAY_GAME;
			}
			MAPIL::PlayStaticBuffer( m_MoveSE );
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_UP ) ){
			--m_SelectedMenuItem;
			if( m_SelectedMenuItem < MENU_ITEM_PLAY_GAME ){
				m_SelectedMenuItem = MENU_ITEM_EXIT;
			}
			MAPIL::PlayStaticBuffer( m_MoveSE );
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_BARRIER ) ){
			if( m_SelectedMenuItem == MENU_ITEM_PLAY_GAME ){
				SetNextScene( new ScriptedStage( p->m_pCompiler, 1 ) );
				MAPIL::PlayStaticBuffer( m_SelectSE );
			}
			else if( m_SelectedMenuItem == MENU_ITEM_REPLAY ){
				SetNextScene( new ShowReplay() );
				MAPIL::PlayStaticBuffer( m_SelectSE );
			}
			else if( m_SelectedMenuItem == MENU_ITEM_SCORE ){
				m_NextMenuItem = MENU_ITEM_SCORE;
				m_StateChangeCounter = 1;
				MAPIL::PlayStaticBuffer( m_SelectSE );
			}
			else if( m_SelectedMenuItem == MENU_ITEM_CONFIG ){
				SetNextScene( new Config() );
				MAPIL::PlayStaticBuffer( m_SelectSE );
			}
			else if( m_SelectedMenuItem == MENU_ITEM_EXIT ){
				p->m_pGameManager->SetTermSig();
				MAPIL::PlayStaticBuffer( m_SelectSE );
			}
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
			if( m_SelectedMenuItem == MENU_ITEM_EXIT ){
				p->m_pGameManager->SetTermSig();
			}
			m_SelectedMenuItem = MENU_ITEM_EXIT;
			MAPIL::PlayStaticBuffer( m_MoveSE );
		}

		TaskList < MenuEffect1 > ::Iterator itEffect3D( m_pEffect3DList );
		TaskList < MenuEffect1 > ::Iterator itEffect3DEnd( m_pEffect3DList );

		itEffect3DEnd.End();
		
		for( itEffect3D.Begin(); itEffect3D != itEffect3DEnd; ++itEffect3D ){
			if( !( *itEffect3D ).Update() ){
				int index = ( *itEffect3D ).GetIndex();
				itEffect3D.Remove();
				//m_pEffect3DList->Add( new MenuEffect1(	m_PointSprite,
				//										MAPIL::Vector3 < float > (	-1.0f + 2.0f * rand() / RAND_MAX,
				//																	5.0f + 10.0f * rand() / RAND_MAX,
				//																	-1.0f - 3.0f * rand() / RAND_MAX ),
				//										0.01f + 0.02f * rand() / RAND_MAX,
				//										MAPIL::DegToRad( -180.0 * rand() / RAND_MAX ),
				//										index ) );
			}
		}

		// ÉÅÉjÉÖÅ[ï\é¶
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

		MAPIL::BeginRendering2DGraphics();


		if( m_StateChangeCounter == 0 ){
			MAPIL::DrawString( MENU_POS_BASE_X - 20.0f + MENU_POS_OFFSET_X * m_SelectedMenuItem, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * m_SelectedMenuItem, "Å°" );
			MAPIL::DrawString( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 0, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 0, "Play Game" );
			MAPIL::DrawString( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 1, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 1, "Replay" );
			MAPIL::DrawString( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 2, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 2, "Score" );
			MAPIL::DrawString( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 3, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 3, "Config" );
			MAPIL::DrawString( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 4, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 4, "Exit" );
		}
		else if( m_NextMenuItem == MENU_ITEM_SCORE ){
			MAPIL::DrawString( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 2 + m_StateChangeCounter * 5, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 2, "Score" );
		}

		MAPIL::EndRendering2DGraphics();

		++m_Counter;
	}

	void Menu::Draw()
	{
		MAPIL::EnableCamera( m_Camera3D );

		MAPIL::DisableZBuffering();

		MAPIL::DrawPointSprite( m_PointSprite );

		MAPIL::EnableZBuffering();
	}

	
}