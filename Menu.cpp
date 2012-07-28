#include "Menu.h"
#include "Stage1.h"
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
		if( m_BGM.GetPointer() ){
			m_BGM->Stop();
		}
		DeleteTaskList( m_pEffect3DList );
		m_Counter = 0;
		MAPIL::SafeDelete( m_pEffect3DList );
		m_StateChangeCounter = 0;
	}

	void Menu::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		p->RefleshResouces();

		m_PointSprite = p->m_pGraphicsFactory->CreatePointSprite( TSTR( "Menu effect" ) );

		m_Texture[ 0 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Menu effect 1" ) );
		m_Texture[ 0 ]->Create( TSTR( "Resource/MenuEffect2.png" ) );

		m_BGM = p->m_pSoundFactory->CreateStreamingBuffer( TSTR( "Menu BGM" ) );
		m_BGM->Create( TSTR( "Resource/rtg_title.wav" ) );

		m_SelectSE = p->m_pSoundFactory->CreateStaticBuffer( TSTR( "Selected SE" ) );
		m_SelectSE->Create( TSTR( "Resource/select.wav" ) );

		m_MoveSE = p->m_pSoundFactory->CreateStaticBuffer( TSTR( "Moce SE" ) );
		m_MoveSE->Create( TSTR( "Resource/move.wav" ) );

		m_PointSprite->Create( 200, m_Texture[ 0 ], MAPIL::VERTEX_MANAGEMENT_NONE );

		m_Camera2D = p->m_pGraphicsFactory->CreateCamera( TSTR( "Menu Camera 2D" ) );

		m_Camera3D = p->m_pGraphicsFactory->CreateCamera( TSTR( "Menu Camera 3D" ) );
		m_Camera3D->Create(	MAPIL::Vector3 < float > ( 0.0f, 0.0f, 10.0f ),
							MAPIL::Vector3 < float > ( 0.0f, 0.0f, 0.0f ),
							MAPIL::Vector3 < float > ( 0.0f, 1.0f, 0.0f ),
							static_cast < float > ( MAPIL::DegToRad( 30.0 ) ),
							p->m_GLContext->GetWidth() * 1.0f / p->m_GLContext->GetHeight(),
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
		
		m_BGM->Play();
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
			m_MoveSE->Play();
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_UP ) ){
			--m_SelectedMenuItem;
			if( m_SelectedMenuItem < MENU_ITEM_PLAY_GAME ){
				m_SelectedMenuItem = MENU_ITEM_EXIT;
			}
			m_MoveSE->Play();
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_BARRIER ) ){
			if( m_SelectedMenuItem == MENU_ITEM_PLAY_GAME ){
				SetNextScene( new Stage1( PLAY_MODE_NORMAL ) );
				m_SelectSE->Play();
			}
			else if( m_SelectedMenuItem == MENU_ITEM_REPLAY ){
				SetNextScene( new ShowReplay() );
				m_SelectSE->Play();
			}
			else if( m_SelectedMenuItem == MENU_ITEM_SCORE ){
				m_NextMenuItem = MENU_ITEM_SCORE;
				m_StateChangeCounter = 1;
				m_SelectSE->Play();
			}
			else if( m_SelectedMenuItem == MENU_ITEM_CONFIG ){
				SetNextScene( new Config() );
				m_SelectSE->Play();
			}
			else if( m_SelectedMenuItem == MENU_ITEM_EXIT ){
				p->m_pGameManager->SetTermSig();
				m_SelectSE->Play();
			}
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
			if( m_SelectedMenuItem == MENU_ITEM_EXIT ){
				p->m_pGameManager->SetTermSig();
			}
			m_SelectedMenuItem = MENU_ITEM_EXIT;
			m_MoveSE->Play();
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

		m_Camera2D->Enable();

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

		p->m_Sprite->Begin();

		if( m_StateChangeCounter == 0 ){
			p->m_Sprite->DrawString( p->m_Font, TSTR( "Å°" ), MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE, MAPIL::Vector2 < float > ( MENU_POS_BASE_X - 20.0f + MENU_POS_OFFSET_X * m_SelectedMenuItem, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * m_SelectedMenuItem ), 0xFFFFFFFF );

			p->m_Sprite->DrawString( p->m_Font, TSTR( "Play Game" ), MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE, MAPIL::Vector2 < float > ( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 0, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 0 ), 0xFFFFFFFF );
			p->m_Sprite->DrawString( p->m_Font, TSTR( "Replay" ), MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE, MAPIL::Vector2 < float > ( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 1, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 1 ), 0xFFFFFFFF );
			p->m_Sprite->DrawString( p->m_Font, TSTR( "Score" ), MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE, MAPIL::Vector2 < float > ( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 2, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 2 ), 0xFFFFFFFF );
			p->m_Sprite->DrawString( p->m_Font, TSTR( "Config" ), MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE, MAPIL::Vector2 < float > ( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 3, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 3 ), 0xFFFFFFFF );
			p->m_Sprite->DrawString( p->m_Font, TSTR( "Exit" ), MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE, MAPIL::Vector2 < float > ( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 4, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 4 ), 0xFFFFFFFF );
		}
		else if( m_NextMenuItem == MENU_ITEM_SCORE ){
			p->m_Sprite->DrawString( p->m_Font, TSTR( "Score" ), MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE, MAPIL::Vector2 < float > ( MENU_POS_BASE_X + MENU_POS_OFFSET_X * 2 + m_StateChangeCounter * 5, MENU_POS_BASE_Y + MENU_POS_OFFSET_Y * 2 ), 0xFFFFFFFF );
		}
		p->m_Sprite->End();

		++m_Counter;
	}

	void Menu::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		m_Camera3D->Enable();

		p->m_GraphicsCtrl->EnableZBuffer( false );

		m_PointSprite->Draw();

		p->m_GraphicsCtrl->EnableZBuffer( false );
	}

	
}