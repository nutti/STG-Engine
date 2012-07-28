#include "Stage1.h"
#include "Menu.h"
#include "EntryScore.h"
#include "NormalPlayer.h"
#include "ResourceHandler.h"
#include "Loading.h"

//#include "HogeEnemy.h"
#include "EnemyShot1.h"
#include "ReflectedShot1.h"

#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"

#include "Boss1.h"

#include "Score.h"

#include "BombedEffect1.h"

#include "Math.h"

#include <iostream>
#include "GeneralButtonManager.h"


namespace RTG
{
	Stage1::Stage1( PlayMode mode ) :	Scene(),
										m_pPlayerList( NULL ),
										m_pEnemyList( NULL ),
										m_pEnemyShotList( NULL ),
										m_pReflectedShotList( NULL ),
										m_pEffect2DList( NULL ),
										m_pStage1Effect1List( NULL ),
										m_Frame( 0 ),
										m_Pos(),
										m_PointSprite(),
										m_PointSpriteCamera(),
										m_BossBGM(),
										m_Mode( mode ),
										m_Cleared( false ),
										m_IsGameOver( false ),
										m_ClearedCounter( 0 ),
										m_KillTotal( 0 ),
										m_ReflectTotal( 0 ),
										m_HitTotal( 0 ),
										m_Paused( false ),
										m_Loading()
	{
	}


	Stage1::~Stage1()
	{
		ResourceHandler::GetInst()->m_StreamingBuf->Stop();
		m_BossBGM->Stop();

		DeleteTaskList( m_pPlayerList );
		DeleteTaskList( m_pEnemyList );
		DeleteTaskList( m_pEnemyShotList );
		DeleteTaskList( m_pReflectedShotList );
		DeleteTaskList( m_pEffect2DList );
		DeleteTaskList( m_pStage1Effect1List );
		MAPIL::SafeDelete( m_pPlayerList );
		MAPIL::SafeDelete( m_pEnemyList );
		MAPIL::SafeDelete( m_pEnemyShotList );
		MAPIL::SafeDelete( m_pReflectedShotList );
		MAPIL::SafeDelete( m_pEffect2DList );
		MAPIL::SafeDelete( m_pStage1Effect1List );
		m_Cleared = false;
		m_IsGameOver = false;
		m_ClearedCounter = 0;
		m_KillTotal = 0;
		m_ReflectTotal = 0;
		m_HitTotal = 0;

		m_Paused = false;
	}

	void Stage1::ProcessPause()
	{
		ResourceHandler* p = ResourceHandler::GetInst();
	}

	void Stage1::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		p->RefleshResouces();

		//p->m_pGraphicsFactory->Reflesh( 2 );
		//p->m_pInputFactory->Reflesh( 2 );
		//p->m_pSoundFactory->Reflesh( 2 );
		//p->m_pGUIFactory->Reflesh( 2 );

		// Set up the textures.
		p->m_Texture[ 0 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Enemy Shot 1" ) );
		p->m_Texture[ 0 ]->Create( TSTR( "Resource/rtg_enemy_shot_3.png" ) );
		p->m_Texture[ 1 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Normal Player 1" ) );
		p->m_Texture[ 1 ]->Create( TSTR( "Resource/NormalPlayer.png" ) );
		p->m_Texture[ 2 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Enemy 1" ) );
		p->m_Texture[ 2 ]->Create( TSTR( "Resource/Enemy1.png" ) );
		p->m_Texture[ 3 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Reflected Enemy Shot 1" ) );
		p->m_Texture[ 3 ]->Create( TSTR( "Resource/rtg_enemy_shot_4.png" ) );
		p->m_Texture[ 4 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Enemy 2" ) );
		p->m_Texture[ 4 ]->Create( TSTR( "Resource/Enemy2.png" ) );
		p->m_Texture[ 5 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Score" ) );
		p->m_Texture[ 5 ]->Create( TSTR( "Resource/Score.png" ) );
		p->m_Texture[ 5 ]->Split( 1, 16, 16, 16 );
		p->m_Texture[ 6 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Ememy 3-1" ) );
		p->m_Texture[ 6 ]->Create( TSTR( "Resource/Enemy3.png" ) );
		p->m_Texture[ 7 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Enemy 3-2" ) );
		p->m_Texture[ 7 ]->Create( TSTR( "Resource/Enemy3-2.png" ) );
		p->m_Texture[ 8 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Reflect Mode Effect" ) );
		p->m_Texture[ 8 ]->Create( TSTR( "Resource/ReflectModeEffect.png" ) );
		p->m_Texture[ 9 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Enemy 4" ) );
		p->m_Texture[ 9 ]->Create( TSTR( "Resource/Enemy4.png" ) );
		p->m_Texture[ 10 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "BackGround 1" ) );
		p->m_Texture[ 10 ]->Create( TSTR( "Resource/Background1.png" ) );
		p->m_Texture[ 11 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "BackGround 2" ) );
		p->m_Texture[ 11 ]->Create( TSTR( "Resource/Background2.png" ) );
		p->m_Texture[ 12 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Bombed Effect 1" ) );
		p->m_Texture[ 12 ]->Create( TSTR( "Resource/BombedEffect1.png" ) );
		p->m_Texture[ 13 ] = p->m_pGraphicsFactory->CreateTexture( TSTR( "Stage1 Background Effect 1" ) );
		p->m_Texture[ 13 ]->Create( TSTR( "Resource/Stage1BackgroundEffect.png" ) );

		// Set up the background.
		p->m_Rectangle[ 0 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 1" ) );
		p->m_Rectangle[ 1 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 2" ) );
		p->m_Rectangle[ 2 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 3" ) );
		p->m_Rectangle[ 3 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 4" ) );
		p->m_Rectangle[ 4 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 5" ) );
		p->m_Rectangle[ 5 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 6" ) );
		p->m_Rectangle[ 6 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 7" ) );
		p->m_Rectangle[ 7 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 8" ) );
		p->m_Rectangle[ 8 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 9" ) );
		p->m_Rectangle[ 9 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 10" ) );
		p->m_Rectangle[ 10 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 11" ) );
		p->m_Rectangle[ 11 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 12" ) );
		p->m_Rectangle[ 12 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 13" ) );
		p->m_Rectangle[ 13 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 14" ) );
		p->m_Rectangle[ 14 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 15" ) );
		p->m_Rectangle[ 15 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 16" ) );
		p->m_Rectangle[ 16 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 17" ) );
		p->m_Rectangle[ 17 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 18" ) );
		p->m_Rectangle[ 18 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 19" ) );
		p->m_Rectangle[ 19 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 20" ) );
		p->m_Rectangle[ 20 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 21" ) );
		p->m_Rectangle[ 21 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 22" ) );
		p->m_Rectangle[ 22 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 23" ) );
		p->m_Rectangle[ 23 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 24" ) );
		p->m_Rectangle[ 24 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 25" ) );
		p->m_Rectangle[ 25 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 26" ) );
		p->m_Rectangle[ 26 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 27" ) );
		p->m_Rectangle[ 27 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 28" ) );
		p->m_Rectangle[ 28 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 29" ) );
		p->m_Rectangle[ 29 ] = p->m_pGraphicsFactory->CreateRectangle3D( TSTR( "Background 30" ) );

		MAPIL::Rectangle3DVertexFormat fmt;
		MAPIL::ZeroObject( &fmt, sizeof( fmt ) );
		double tilt = MAPIL::DegToRad( 90.0 );
		for( int j = 0; j < 10; ++j ){
			fmt.m_Pos[ 0 ].m_X = -0.5f;
			fmt.m_Pos[ 0 ].m_Z = -0.5f + 1.0f * ( j - 8 );
			fmt.m_Pos[ 1 ].m_X = -0.5f;
			fmt.m_Pos[ 1 ].m_Z = 0.5f + 1.0f * ( j - 8 );
			fmt.m_Pos[ 2 ].m_X = 0.5f;
			fmt.m_Pos[ 2 ].m_Z = -0.5f + 1.0f * ( j - 8 );
			fmt.m_Pos[ 3 ].m_X = 0.5f;
			fmt.m_Pos[ 3 ].m_Z = 0.5f + 1.0f * ( j - 8 );
			fmt.m_Tex[ 0 ].m_U = 0.0f;
			fmt.m_Tex[ 0 ].m_V = 0.0f;
			fmt.m_Tex[ 1 ].m_U = 0.0f;
			fmt.m_Tex[ 1 ].m_V = 1.0f;
			fmt.m_Tex[ 2 ].m_U = 1.0f;
			fmt.m_Tex[ 2 ].m_V = 0.0f;
			fmt.m_Tex[ 3 ].m_U = 1.0f;
			fmt.m_Tex[ 3 ].m_V = 1.0f;
			for( int i = 0; i < 16; ++i ){
				fmt.m_ColElm[ i ] = 255 * 7 / 10;
			}
		
			p->m_Rectangle[ j ]->Create( fmt, p->m_Texture[ 10 ], MAPIL::VERTEX_MANAGEMENT_NONE );
		}

		for( int i = 0; i < 10; ++i ){
			for( int j = 0; j < 4; ++j ){
				fmt.m_Pos[ j ].m_X = -0.5f;
			}
			fmt.m_Pos[ 0 ].m_Y = 1.0f;
			fmt.m_Pos[ 0 ].m_Z = 0.0f - 1.0f * i;
			fmt.m_Pos[ 1 ].m_Y = 0.0f;
			fmt.m_Pos[ 1 ].m_Z = 0.0f - 1.0f * i;
			fmt.m_Pos[ 2 ].m_Y = 1.0f;
			fmt.m_Pos[ 2 ].m_Z = 1.0f - 1.0f * i;
			fmt.m_Pos[ 3 ].m_Y = 0.0f;
			fmt.m_Pos[ 3 ].m_Z = 1.0f - 1.0f * i;

			fmt.m_Tex[ 0 ].m_U = 0.0f;
			fmt.m_Tex[ 0 ].m_V = 0.0f;
			fmt.m_Tex[ 1 ].m_U = 0.0f;
			fmt.m_Tex[ 1 ].m_V = 1.0f;
			fmt.m_Tex[ 2 ].m_U = 1.0f;
			fmt.m_Tex[ 2 ].m_V = 0.0f;
			fmt.m_Tex[ 3 ].m_U = 1.0f;
			fmt.m_Tex[ 3 ].m_V = 1.0f;
			for( int j = 0; j < 16; ++j ){
				fmt.m_ColElm[ i ] = 255 * 7 / 10;
			}
			p->m_Rectangle[ i + 10 ]->Create( fmt, p->m_Texture[ 11 ], MAPIL::VERTEX_MANAGEMENT_NONE );
		}

		for( int i = 0; i < 10; ++i ){
			for( int j = 0; j < 4; ++j ){
				fmt.m_Pos[ j ].m_X = 0.5f;
			}
			fmt.m_Pos[ 0 ].m_Y = 1.0f;
			fmt.m_Pos[ 0 ].m_Z = 1.0f - 1.0f * i;
			fmt.m_Pos[ 1 ].m_Y = 0.0f;
			fmt.m_Pos[ 1 ].m_Z = 1.0f - 1.0f * i;
			fmt.m_Pos[ 2 ].m_Y = 1.0f;
			fmt.m_Pos[ 2 ].m_Z = 0.0f - 1.0f * i;
			fmt.m_Pos[ 3 ].m_Y = 0.0f;
			fmt.m_Pos[ 3 ].m_Z = 0.0f - 1.0f * i;

			fmt.m_Tex[ 0 ].m_U = 0.0f;
			fmt.m_Tex[ 0 ].m_V = 0.0f;
			fmt.m_Tex[ 1 ].m_U = 0.0f;
			fmt.m_Tex[ 1 ].m_V = 1.0f;
			fmt.m_Tex[ 2 ].m_U = 1.0f;
			fmt.m_Tex[ 2 ].m_V = 0.0f;
			fmt.m_Tex[ 3 ].m_U = 1.0f;
			fmt.m_Tex[ 3 ].m_V = 1.0f;
			for( int j = 0; j < 16; ++j ){
				fmt.m_ColElm[ i ] = 255 * 7 / 10;
			}
			p->m_Rectangle[ i + 20 ]->Create( fmt, p->m_Texture[ 11 ], MAPIL::VERTEX_MANAGEMENT_NONE );
		}




		p->m_PointSprite = p->m_pGraphicsFactory->CreatePointSprite( TSTR( "Point sprite" ) );
		p->m_PointSprite->Create( 100, MAPIL::VERTEX_MANAGEMENT_NONE );

		m_PointSprite = p->m_pGraphicsFactory->CreatePointSprite( TSTR( "Stage1 Backgound Effect1" ) );
		m_PointSprite->Create( 200, p->m_Texture[ 13 ], MAPIL::VERTEX_MANAGEMENT_NONE );

		m_PointSpriteCamera = p->m_pGraphicsFactory->CreateCamera( TSTR( "Stage1 PointSprite Camera" ) );
		m_PointSpriteCamera->Create(	MAPIL::Vector3 < float > ( 0.0f, 0.0f, 10.0f ),
										MAPIL::Vector3 < float > ( 0.0f, 0.0f, 0.0f ),
										MAPIL::Vector3 < float > ( 0.0f, 1.0f, 0.0f ),
										static_cast < float > ( MAPIL::DegToRad( 30.0 ) ),
										p->m_GLContext->GetWidth() * 1.0f / p->m_GLContext->GetHeight(),
										0.01f, 20.0f );

		// Set up SE.
		p->m_StaticBuf[ 0 ] = p->m_pSoundFactory->CreateStaticBuffer( TSTR( "SE1" ) );
		p->m_StaticBuf[ 1 ] = p->m_pSoundFactory->CreateStaticBuffer( TSTR( "SE2" ) );
		p->m_StaticBuf[ 2 ] = p->m_pSoundFactory->CreateStaticBuffer( TSTR( "SE3" ) );

		// 情報表示のためのテクスチャ
		m_PlayerEnergyBar = p->m_pGraphicsFactory->CreateTexture( TSTR( "Energy Bar" ) );
		m_PlayerHPBar = p->m_pGraphicsFactory->CreateTexture( TSTR( "HP Bar" ) );
		m_PlayerEnergyBar->Create( TSTR( "Resource/EnergyBar.png" ) );
		m_PlayerHPBar->Create( TSTR( "Resource/HPBar.png" ) );

		// Set up BGM.
		p->m_StreamingBuf = p->m_pSoundFactory->CreateStreamingBuffer( TSTR( "Stage1" ) );

		m_BossBGM = p->m_pSoundFactory->CreateStreamingBuffer( TSTR( "Boss BGM 1" ) );

		m_Loading.Create();
		m_Loading.Reset();
		m_Loading.SetArchiver( TSTR( "resource.dat" ) );
		m_Loading.SetContents( p->m_StreamingBuf, TSTR( "Resource/rtg_stage2.wav" ) );
		m_Loading.SetContents( m_BossBGM, TSTR( "Resource/rtg_boss1-2.wav" ) );
		m_Loading.SetContents( p->m_StaticBuf[ 0 ], TSTR( "Resource/rtg_se1.wav" ) );
		m_Loading.SetContents( p->m_StaticBuf[ 1 ], TSTR( "Resource/rtg_se2.wav" ) );
		m_Loading.SetContents( p->m_StaticBuf[ 2 ], TSTR( "Resource/EnemyShotSE.wav" ) );
		m_Loading.Start();

		p->m_pScore = new Score( p->m_Texture[ 5 ], p->m_Sprite );
		p->m_pScore->Set( 0 );

		p->m_Camera3D->Create(	MAPIL::Vector3 < float > ( 0.0f, 0.0f, 10.0f ),
								MAPIL::Vector3 < float > ( 0.0f, 0.0f, 0.0f ),
								MAPIL::Vector3 < float > ( 0.0f, 1.0f, 0.0f ),
								static_cast < float > ( MAPIL::DegToRad( 30.0 ) ),
								static_cast < float > ( p->m_GLContext->GetWidth() * 1.0f / p->m_GLContext->GetHeight() ),
								0.01f, 50.0f );

		p->m_Camera->SetProjectionTransMat( 0, 640, 480, 0, 0, 1 );

		m_pPlayerList = new TaskList < CirclePlayer > ();
		m_pPlayerList->Init();

		m_pEnemyList = new TaskList < CircleEnemy > ();
		m_pEnemyList->Init();

		m_pEnemyShotList = new TaskList < CircleEnemyShot > ();
		m_pEnemyShotList->Init();

		m_pReflectedShotList = new TaskList < CircleReflectedShot > ();
		m_pReflectedShotList->Init();

		m_pEffect2DList = new TaskList < Effect2D > ();
		m_pEffect2DList->Init();

		m_pStage1Effect1List = new TaskList < Stage1Effect1 > ();
		m_pStage1Effect1List->Init();

		for( int i = 0; i < 200; ++i ){
			m_pStage1Effect1List->Add(	new Stage1Effect1(	m_PointSprite,
															MAPIL::Vector3 < float > (	-5.0f + 10.0f * rand() / RAND_MAX,
																						-1.0f - 6.0f * rand() / RAND_MAX,
																						-1.0f - 30.0f * rand() / RAND_MAX ),
																						-0.01 - 0.1 * rand() / RAND_MAX,
																						MAPIL::DegToRad( -70.0 - 40.0 * rand() / RAND_MAX ),
																						i ) );
		}

		CirclePlayer* pPlayer = new NormalPlayer( MAPIL::Vector2 < double > ( 320.0, 240.0 ), m_PlayerEnergyBar, m_PlayerHPBar );

		m_pPlayerList->Add( pPlayer );


		// ランダムシードのリセット
		ResetRandSeed();
	}

	bool DoesCollide( CircleObj* pObj1, CircleObj* pObj2 )
	{
		MAPIL::Vector2 < double > diff = pObj1->m_Pos - pObj2->m_Pos;
		if( diff.GetNorm() < pObj1->m_Radius + pObj2->m_Radius ){
			return true;
		}
		return false;
	}

	bool Stage1::IsLoading() const
	{
		return !m_Loading.IsFinished();
	}

	void Stage1::Update()
	{

		ResourceHandler* pp = ResourceHandler::GetInst();

		
		if( pp->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_PAUSE ) ){
			m_Paused = !m_Paused;
			// ボス戦中のpauseに対応していない
			if( m_Paused ){
				ResourceHandler::GetInst()->m_StreamingBuf->Pause();
				m_BossBGM->Pause();
			}
			else{
				ResourceHandler::GetInst()->m_StreamingBuf->Play();
			}
		}

		if( !m_Paused ){
			TaskList < CirclePlayer > ::Iterator itP( m_pPlayerList );
			itP.Begin();

			Sequence();

			//m_Cleared = true;

			ResourceHandler* p = ResourceHandler::GetInst();

			if( m_Cleared || m_IsGameOver ){
				++m_ClearedCounter;
				if( m_ClearedCounter >= 120 ){
					if( m_Cleared ){
						if( m_Mode == PLAY_MODE_NORMAL ){
							SetNextScene( new EntryScore( p->m_pScore->Get(), STAGE_PROGRESS_COMPLETED ) );
						}
						else{
							p->m_pGBManager->SetReplay( 0 );
							p->m_pGBManager->Assign( GENERAL_BUTTON_LEFT, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_LEFT );
							p->m_pGBManager->Assign( GENERAL_BUTTON_RIGHT, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_RIGHT );
							p->m_pGBManager->Assign( GENERAL_BUTTON_DOWN, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_DOWN );
							p->m_pGBManager->Assign( GENERAL_BUTTON_UP, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_UP );
							p->m_pGBManager->Assign( GENERAL_BUTTON_ROT_CCW, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_A );
							p->m_pGBManager->Assign( GENERAL_BUTTON_ROT_CW, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_S );
							p->m_pGBManager->Assign( GENERAL_BUTTON_BARRIER, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_Z );
							p->m_pGBManager->Assign( GENERAL_BUTTON_CANCEL, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_X );
							p->m_pGBManager->Assign( GENERAL_BUTTON_PAUSE, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_F1 );
							p->m_pGBManager->Assign( GENERAL_BUTTON_SS, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_P );
							p->m_pGBManager->Assign( GENERAL_BUTTON_TERM, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_DELETE );
							p->m_pGBManager->Assign( GENERAL_BUTTON_ENTER, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_RETURN );
							SetNextScene( new Menu() );
						}
					}
					else{
						if( m_Mode == PLAY_MODE_NORMAL ){
							SetNextScene( new EntryScore( p->m_pScore->Get(), STAGE_PROGRESS_STAGE1 ) );
						}
						else{
							p->m_pGBManager->SetReplay( 0 );
							p->m_pGBManager->Assign( GENERAL_BUTTON_LEFT, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_LEFT );
							p->m_pGBManager->Assign( GENERAL_BUTTON_RIGHT, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_RIGHT );
							p->m_pGBManager->Assign( GENERAL_BUTTON_DOWN, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_DOWN );
							p->m_pGBManager->Assign( GENERAL_BUTTON_UP, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_UP );
							p->m_pGBManager->Assign( GENERAL_BUTTON_ROT_CCW, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_A );
							p->m_pGBManager->Assign( GENERAL_BUTTON_ROT_CW, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_S );
							p->m_pGBManager->Assign( GENERAL_BUTTON_BARRIER, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_Z );
							p->m_pGBManager->Assign( GENERAL_BUTTON_CANCEL, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_X );
							p->m_pGBManager->Assign( GENERAL_BUTTON_PAUSE, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_F1 );
							p->m_pGBManager->Assign( GENERAL_BUTTON_SS, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_P );
							p->m_pGBManager->Assign( GENERAL_BUTTON_TERM, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_DELETE );
							p->m_pGBManager->Assign( GENERAL_BUTTON_ENTER, INPUT_DEVICE_KEYBOARD, MAPIL::KEYBOARD_KEY_RETURN );
							SetNextScene( new Menu() );
						}
					}
				}
				else{
					if( m_Cleared ){
						p->m_Sprite->Begin();
						char str[ 256 ];
						TCHAR tstr[ 256 ];
						sprintf( str, "Stage 1 Clear \n\n Killed : %d\n Hit ratio : %.2f", m_KillTotal, m_HitTotal * 1.0f / m_ReflectTotal );
						MAPIL::ConvertToTChar( str, 256, tstr, 256 );
						p->m_Sprite->DrawString( p->m_Font, tstr, MAPIL::IMAGE_TRANSFORMATION_METHOD_MOVE, MAPIL::Vector2 < float > ( 100.0f, 100.0f ), 0xFFFFFFFF );
						p->m_Sprite->End();
					}
				}
			}

			// リプレイ用にキー保存。
			if( m_Mode == PLAY_MODE_NORMAL ){
				char str[ GENERAL_BUTTON_TOTAL ];
				p->m_pGBManager->CopyCurState( str );
				p->m_pReplaySaver->Add( str );
			}
		
			p->m_Camera->Enable();

			p->m_Sprite->Begin();

			TaskList < CirclePlayer > ::Iterator itPlayer( m_pPlayerList );
			TaskList < CirclePlayer > ::Iterator itPlayerEnd( m_pPlayerList );

			itPlayerEnd.End();

			for( itPlayer.Begin(); itPlayer != itPlayerEnd; ++itPlayer ){
				if( !( *itPlayer ).Update() ){
					itPlayer.Remove();
					m_IsGameOver = true;
				}
			}

			TaskList < CircleEnemy > ::Iterator itEnemy( m_pEnemyList );
			TaskList < CircleEnemy > ::Iterator itEnemyEnd( m_pEnemyList );

			itEnemyEnd.End();

			for( itEnemy.Begin(); itEnemy != itEnemyEnd; ++itEnemy ){
				if( !( *itEnemy ).Update() ){
					itEnemy.Remove();
				}
			}

			TaskList < CircleEnemyShot > ::Iterator itEnemyShot( m_pEnemyShotList );
			TaskList < CircleEnemyShot > ::Iterator itEnemyShotEnd( m_pEnemyShotList );

			itEnemyShotEnd.End();

			for( itEnemyShot.Begin(); itEnemyShot != itEnemyShotEnd; ++itEnemyShot ){
				if( !( *itEnemyShot ).Update() ){
					itEnemyShot.Remove();
				}
			}

			TaskList < CircleReflectedShot > ::Iterator itReflectedShot( m_pReflectedShotList );
			TaskList < CircleReflectedShot > ::Iterator itReflectedShotEnd( m_pReflectedShotList );

			itReflectedShotEnd.End();

			for( itReflectedShot.Begin(); itReflectedShot != itReflectedShotEnd; ++itReflectedShot ){
				if( !( *itReflectedShot ).Update() ){
					itReflectedShot.Remove();
				}
			}

			TaskList < Effect2D > ::Iterator itEffect2D( m_pEffect2DList );
			TaskList < Effect2D > ::Iterator itEffect2DEnd( m_pEffect2DList );

			itEffect2DEnd.End();

			for( itEffect2D.Begin(); itEffect2D != itEffect2DEnd; ++itEffect2D ){
				if( !( *itEffect2D ).Update() ){
					itEffect2D.Remove();
				}
			}

			TaskList < Stage1Effect1 > ::Iterator itStage1Effect1( m_pStage1Effect1List );
			TaskList < Stage1Effect1 > ::Iterator itStage1Effect1End( m_pStage1Effect1List );

			itStage1Effect1End.End();
		
			for( itStage1Effect1.Begin(); itStage1Effect1 != itStage1Effect1End; ++itStage1Effect1 ){
				if( !( *itStage1Effect1 ).Update() ){
					int index = ( *itStage1Effect1 ).GetIndex();
					itStage1Effect1.Remove();
					m_pStage1Effect1List->Add( new Stage1Effect1(	m_PointSprite,
																	MAPIL::Vector3 < float > (	-5.0f + 10.0f * rand() / RAND_MAX,
																							-1.0f - 6.0f * rand() / RAND_MAX,
																							-1.0f - 30.0f * rand() / RAND_MAX ),
																							-0.01 - 0.1 * rand() / RAND_MAX,
																							MAPIL::DegToRad( -70.0 - 40.0 * rand() / RAND_MAX ),
																							index ) );
				}
			}

			p->m_pScore->Update();
			p->m_pScore->Display( 200.0f, 20.0f, 16.0f, 10 );

			Score frame( p->m_Texture[ 5 ], p->m_Sprite );
			frame.Set( m_Frame );
			frame.Display( 580.0f, 20.0f, 16.0f, 6 );

			p->m_Sprite->End();


			// Collision judgement.

			// Player-EnemyShot
			itPlayerEnd.End();
			for( itPlayer.Begin(); itPlayer != itPlayerEnd; ++itPlayer ){
				itEnemyShotEnd.End();

				for( itEnemyShot.Begin(); itEnemyShot != itEnemyShotEnd; ++itEnemyShot ){
					if( DoesCollide( &(*itPlayer), &(*itEnemyShot) ) ){
						if( ((NormalPlayer*)&(*itPlayer))->IsReflectMode() ){
							((NormalPlayer*)&(*itPlayer))->DecEnergy( 100 );
							m_pReflectedShotList->Add( new ReflectedShot1( *itEnemyShot, *(NormalPlayer*)&(*itPlayer), 3 ) );
							p->m_StaticBuf[ 0 ]->Play();
							p->m_pScore->Add( 1 );
							++m_HitTotal;
						}
						else{
							((NormalPlayer*)&(*itPlayer))->Damage( 1 );
						}
						itEnemyShot.Remove();
					}
				}
			}

			// Enemy-ReflectedShot
			itEnemyEnd.End();
			itReflectedShotEnd.End();
		
			for( itReflectedShot.Begin(); itReflectedShot != itReflectedShotEnd; ++itReflectedShot ){
				for( itEnemy.Begin(); itEnemy != itEnemyEnd; ++itEnemy ){
					if( DoesCollide( &(*itEnemy), &(*itReflectedShot) ) ){
						itReflectedShot.Remove();
						( *itEnemy ).Damage( 1 );
						++m_ReflectTotal;
						p->m_StaticBuf[ 1 ]->Play();
						// 2重判定が起こる可能性があり、要修正
						// 倒した時に得点が入るようにする等
						if( ( *itEnemy ).GetHP() <= 0 ){
							p->m_pScore->Add( ( *itEnemy ).GetScore() );
							++m_KillTotal;
							m_pEffect2DList->Add( new BombedEffect1(	p->m_Sprite,
																		p->m_Texture[ 12 ],
																		MAPIL::Vector2 < float > (	static_cast < float > ( ( *itEnemy ).GetPos().m_X ),
																									static_cast < float > ( ( *itEnemy ).GetPos().m_Y ) ),
																		0.3f,
																		0.1 ) );
							if( ( *itEnemy ).IsBoss() ){
								m_Cleared = true;
							}
						}
						else{
							p->m_pScore->Add( 100 );
						}
					}
				}
			}
		

			++m_Frame;
		}
		else{
			ProcessPause();
		}
	}

	void Stage1::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		if( m_Paused ){
			return;
		}

		static bool isFirst = true;
		if( isFirst ){
			isFirst = !isFirst;
		}

		m_Pos.m_Y = 0.5f;//0.5f;
		if( m_Frame < 3350 ){
			m_Pos.m_Z -= 0.025f;
		}
		else if( m_Frame >= 3350 && m_Frame < 6000 ){
			m_Pos.m_Z -= 0.05f;
		}
		else if( m_Frame >= 5800 && m_Frame < 6200 ){
			m_Pos.m_Z -= ( 6200 - m_Frame ) * 0.05f / 400 + 0.001f;
		}
		else{
			m_Pos.m_Z -= 0.001f;
		}
		
		if( m_Pos.m_Z <= 0.0f ){
			m_Pos.m_Z = 2.0f;
		}

		if( m_Frame >= 3350 && m_Frame <= 3750 ){
			float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( m_Frame - 3350 ) * 20.0f / 400 ) ) );
			float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( m_Frame - 3350 ) * 20.0f / 400 ) ) );
			p->m_Camera3D->SetViewTransMat( m_Pos,
											MAPIL::Vector3 < float > ( 0.0f, 0.0f, m_Pos.m_Z - 1.5f ),
											MAPIL::Vector3 < float > ( tiltX, tiltY, 0.0f ) );
		}
		else if( m_Frame > 3750 && m_Frame <= 4150 ){
			float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( 4150 - m_Frame ) * 20.0f / 400 ) ) );
			float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( 4150 - m_Frame ) * 20.0f / 400 ) ) );
			p->m_Camera3D->SetViewTransMat( m_Pos,
											MAPIL::Vector3 < float > ( 0.0f, 0.0f, m_Pos.m_Z - 1.5f ),
											MAPIL::Vector3 < float > ( tiltX, tiltY, 0.0f ) );
		}
		else if( m_Frame > 4150 && m_Frame <= 4550 ){
			float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( 4150 - m_Frame ) * 20.0f / 400 ) ) );
			float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( 4150 - m_Frame ) * 20.0f / 400 ) ) );
			p->m_Camera3D->SetViewTransMat( m_Pos,
											MAPIL::Vector3 < float > ( 0.0f, 0.0f, m_Pos.m_Z - 1.5f ),
											MAPIL::Vector3 < float > ( tiltX, tiltY, 0.0f ) );
		}
		else if( m_Frame > 4550 && m_Frame <= 4950 ){
			float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( m_Frame - 4950 ) * 20.0f / 400 ) ) );
			float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( m_Frame - 4950 ) * 20.0f / 400 ) ) );
			p->m_Camera3D->SetViewTransMat( m_Pos,
											MAPIL::Vector3 < float > ( 0.0f, 0.0f, m_Pos.m_Z - 1.5f ),
											MAPIL::Vector3 < float > ( tiltX, tiltY, 0.0f ) );
		}
		else if( m_Frame >= 6200 ){
			const int CYCLE = 1000;
			const int HALF_CYCLE = 1000 / 2;
			int frame = m_Frame - 6200;
			frame %= CYCLE;
			if( frame < HALF_CYCLE / 2 ){
				float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( frame * 10.0f / HALF_CYCLE ) ) );
				float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( frame * 10.0f / HALF_CYCLE ) ) );
				p->m_Camera3D->SetViewTransMat( m_Pos,
												MAPIL::Vector3 < float > ( tiltX / 5.0f, 0.0f, m_Pos.m_Z - 1.5f ),
												MAPIL::Vector3 < float > ( tiltX, tiltY, 0.0f ) );
			}
			else if( frame >= HALF_CYCLE / 2 && frame < HALF_CYCLE ){
				float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( HALF_CYCLE - frame ) * 10.0f / HALF_CYCLE ) ) );
				float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( HALF_CYCLE - frame ) * 10.0f / HALF_CYCLE ) ) );
				p->m_Camera3D->SetViewTransMat( m_Pos,
												MAPIL::Vector3 < float > ( tiltX / 5.0f, 0.0f, m_Pos.m_Z - 1.5f ),
												MAPIL::Vector3 < float > ( tiltX, tiltY, 0.0f ) );
			}
			else if( frame >= HALF_CYCLE && frame < HALF_CYCLE * 3 / 2 ){
				float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( HALF_CYCLE - frame ) * 10.0f / HALF_CYCLE ) ) );
				float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( HALF_CYCLE - frame ) * 10.0f / HALF_CYCLE ) ) );
				p->m_Camera3D->SetViewTransMat( m_Pos,
												MAPIL::Vector3 < float > ( tiltX / 5.0f, 0.0f, m_Pos.m_Z - 1.5f ),
												MAPIL::Vector3 < float > ( tiltX, tiltY, 0.0f ) );
			}
			else if( frame >= HALF_CYCLE * 3 / 2 && frame < CYCLE ){
				float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( frame - CYCLE ) * 10.0f / HALF_CYCLE ) ) );
				float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( frame - CYCLE ) * 10.0f / HALF_CYCLE ) ) );
				p->m_Camera3D->SetViewTransMat( m_Pos,
												MAPIL::Vector3 < float > ( tiltX / 5.0f, 0.0f, m_Pos.m_Z - 1.5f ),
												MAPIL::Vector3 < float > ( tiltX, tiltY, 0.0f ) );
			}
		}
		else{
			p->m_Camera3D->SetViewTransMat(	m_Pos,
											MAPIL::Vector3 < float > ( 0.0f, 0.0f, m_Pos.m_Z - 1.5f ),
											MAPIL::Vector3 < float > ( 0.0f, 1.0f, 0.0f ) );
		}

		

		p->m_Camera3D->Enable();

		p->m_GraphicsCtrl->EnableFog( true );
		p->m_GraphicsCtrl->SetFogParam(	MAPIL::ColorARGB < float > ( 122.0f, 100.0f, 100.0f, 0.0f ),
										MAPIL::FOG_MODE_EXP,
										10.0f,
										20.0f,
										0.2f );


		for( int i = 0; i < 30; ++i ){
			p->m_Rectangle[ i ]->Draw();
		}

		p->m_GraphicsCtrl->EnableFog( false );

		p->m_GraphicsCtrl->EnableZBuffer( false );

		m_PointSpriteCamera->Enable();

		m_PointSprite->Draw();

		p->m_GraphicsCtrl->EnableZBuffer( true );
	}

	void Stage1::Sequence()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		TaskList < CirclePlayer > ::Iterator itP( m_pPlayerList );
		itP.Begin();

		p->m_RdmSeed.m_PosX = static_cast < int > ( ( *itP ).GetPos().m_X );
		p->m_RdmSeed.m_PosY = static_cast < int > ( ( *itP ).GetPos().m_Y );
		p->m_RdmSeed.m_Score = p->m_pScore->Get();
		p->m_RdmSeed.m_HitTotal = m_HitTotal;
		p->m_RdmSeed.m_ReflectTotal = m_ReflectTotal;
		p->m_RdmSeed.m_Frame = m_Frame;

		double random = Rand(	p->m_RdmSeed.m_PosX,
								p->m_RdmSeed.m_PosY,
								p->m_RdmSeed.m_Score,
								p->m_RdmSeed.m_HitTotal,
								p->m_RdmSeed.m_ReflectTotal,
								p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;

		switch( m_Frame ){
			case 10:
			case 30:
			case 50:
			case 70:
			case 90:
			case 110:
			case 130:
				m_pEnemyList->Add( new Enemy1(	&( *itP ),
												m_pEnemyShotList,
												MAPIL::Vector2 < double > (	120.0, 0.0 ),
												4.0,
												MAPIL::DegToRad( 90.0 ),
												10.0,
												1,
												2,
												1000 ) );
				break;
			case 20:
			case 40:
			case 60:
			case 80:
			case 100:
			case 120:
			case 140:
				m_pEnemyList->Add( new Enemy1(	&( *itP ),
													m_pEnemyShotList,
													MAPIL::Vector2 < double > (	360.0, 0 ),
													4.0,
													MAPIL::DegToRad( 90.0 ),
													10.0,
													1,
													2,
													1000 ) );
				break;
			case 330:
				m_pEnemyList->Add( new Enemy2(	&( *itP ),
												m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 320.0, 0.0 ),
												2.0,
												MAPIL::DegToRad( 90.0 ),
												32.0,
												10,
												4,
												2500 ) );
				break;
			case 560:
			case 580:
			case 600:
			case 620:
			case 640:
			case 660:
			case 680:
				m_pEnemyList->Add( new Enemy1(	&( *itP ),
												m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 0.0, 0.0 ),
												4.0,
												MAPIL::DegToRad( 45.0 ),
												10.0,
												1,
												2,
												1000 ) );
				break;
			case 570:
			case 590:
			case 610:
			case 630:
			case 650:
			case 670:
			case 690:
				m_pEnemyList->Add( new Enemy1(	&( *itP ),
												m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 640.0, 0.0 ),
												4.0,
												MAPIL::DegToRad( 135.0 ),
												10.0,
												1,
												2,
												1000 ) );
				break;
			case 900:
			case 905:
			case 910:
			case 915:
			case 920:
			case 925:
			case 930:
			case 935:
			case 940:
			case 945:
			case 950:
			case 955:
			case 960:
			case 965:
			case 970:
			case 975:
			case 980:
			case 985:
			case 990:
			case 995:
			case 1000:
			case 1005:
			case 1010:
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > (	640.0, 100.0 + 100.0 * random ),
												3.0 + 2.0 * random, MAPIL::DegToRad( 180.0 ),
												10.0, 1, 2, 1000 ) );
				break;
			case 1100:
			case 1105:
			case 1110:
			case 1115:
			case 1120:
			case 1125:
			case 1130:
			case 1135:
			case 1140:
			case 1145:
			case 1150:
			case 1155:
			case 1160:
			case 1165:
			case 1170:
			case 1175:
			case 1180:
			case 1185:
			case 1190:
			case 1195:
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > (	0.0, 100.0 + 100.0 * random ),
												2.0 + 1.8 * random, MAPIL::DegToRad( -5.0 + 10.0 * random ),
												10.0, 1, 2, 1000 ) );
				break;
			case 1400:
			case 1405:
			case 1410:
			case 1415:
			case 1420:
			case 1425:
			case 1430:
			case 1435:
			case 1440:
			case 1445:
			case 1450:
			case 1455:
			case 1460:
			case 1465:
			case 1470:
			case 1475:
			case 1480:
			case 1485:
			case 1490:
			case 1495:
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > (	640.0, 100.0 + 100.0 * random ),
												3.0 + 2.0 * random, MAPIL::DegToRad( 180.0 ),
												10.0, 1, 2, 1000 ) );
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > (	0.0, 100.0 + 100.0 * random ),
												2.0 + 1.8 * random, MAPIL::DegToRad( -5.0 + 10.0 * random ),
												10.0, 1, 2, 1000 ) );
				break;
			case 1650:
				for( int i = 0; i < 2; ++i ){
					m_pEnemyList->Add( new Enemy2(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > ( 160.0 + 320 * i, 0.0 ),
													3.0, MAPIL::DegToRad( 90.0 ),
													32.0, 10, 4, 2500 ) );
				}
				break;
			case 1970:
				for( int i = 0; i < 3; ++i ){
					m_pEnemyList->Add( new Enemy2(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > ( 160.0 + 160.0 * i, 0.0 ),
													3.0, MAPIL::DegToRad( 90.0 ),
													32.0, 10, 4, 2500 ) );
				}
				break;
			case 2290:
				for( int i = 0; i < 4; ++ i ){
					m_pEnemyList->Add( new Enemy2(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > ( 120.0 + 120.0 * i, 0.0 ),
													3.0, MAPIL::DegToRad( 90.0 ),
													32.0, 10, 4, 2500 ) );
				}
				break;
			case 2610:
				for( int i = 0; i < 2; ++ i ){
					m_pEnemyList->Add( new Enemy2(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > ( 120.0 + 360.0 * i, 0.0 ),
													3.0, MAPIL::DegToRad( 90.0 ),
													32.0, 10, 4, 2500 ) );
				}
				for( int i = 0; i < 20; ++i ){
					random = Rand(	p->m_RdmSeed.m_PosX,
									p->m_RdmSeed.m_PosY,
									p->m_RdmSeed.m_Score,
									p->m_RdmSeed.m_HitTotal,
									p->m_RdmSeed.m_ReflectTotal,
									p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
					double random2 = Rand(	p->m_RdmSeed.m_PosX,
											p->m_RdmSeed.m_PosY,
											p->m_RdmSeed.m_Score,
											p->m_RdmSeed.m_HitTotal,
											p->m_RdmSeed.m_ReflectTotal,
											p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
					double random3 = Rand(	p->m_RdmSeed.m_PosX,
											p->m_RdmSeed.m_PosY,
											p->m_RdmSeed.m_Score,
											p->m_RdmSeed.m_HitTotal,
											p->m_RdmSeed.m_ReflectTotal,
											p->m_RdmSeed.m_Frame ) * 1.0 / RAND_MAXIMUM;
					m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > (	0.0, 100.0 + 100.0 * random ),
													1.5 + 1.8 * random2, MAPIL::DegToRad( -5.0 + 10.0 * random3 ),
													10.0, 1, 2, 1000 ) );
				}
				break;
			case 3020:
			case 3025:
			case 3030:
				m_pEnemyList->Add(	new Enemy4(	&( *itP ),
												m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 640.0f, 100.0 ),
												9.0,
												MAPIL::DegToRad( 180.0 ),
												3,
												1,
												9,
												5000 ) );
				break;
			case 3110:
			case 3115:
			case 3120:
				for( int i = 0; i < 2; ++i ){
					m_pEnemyList->Add(	new Enemy4(	&( *itP ),
													m_pEnemyShotList,
													MAPIL::Vector2 < double > ( 0.0f, 100.0f + i * 100.0f ),
													6.0,
													MAPIL::DegToRad( 0.0 ),
													3,
													1,
													9,
													5000 ) );
				}
				break;
			case 3200:
			case 3205:
			case 3210:
				for( int i = 0; i < 3; ++i ){
					m_pEnemyList->Add(	new Enemy4(	&( *itP ),
													m_pEnemyShotList,
													MAPIL::Vector2 < double > ( 640.0f, 100.0f + 50.0f * i ),
													6.0,
													MAPIL::DegToRad( 180.0 ),
													3,
													1,
													9,
													5000 ) );
				}
				break;
			case 3290:
			case 3295:
			case 3300:
				for( int i = 0; i < 4; ++i ){
					m_pEnemyList->Add(	new Enemy4(	&( *itP ),
													m_pEnemyShotList,
													MAPIL::Vector2 < double > ( 0.0f, 100.0f + 30.0f * i ),
													6.0,
													MAPIL::DegToRad( 0.0 ),
													3,
													1,
													9,
													5000 ) );
				}
				break;
			case 3350:
				m_pEnemyList->Add(	new Enemy3(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 100.0, 0.0 ),
												3.0, MAPIL::DegToRad( 90.0 ),
												5, 2, 6, 2000 ) );
				break;
			case 3470:
			case 3490:
			case 3510:
			case 3530:
			case 3550:
			case 3570:
			case 3590:
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > (	480.0, 0 ),
													4.0, MAPIL::DegToRad( 90.0 ),
													10.0, 1, 2, 1000 ) );
				break;
			case 3690:
				m_pEnemyList->Add(	new Enemy3(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 540.0, 0.0 ),
												3.0, MAPIL::DegToRad( 90.0 ),
												5, 2, 6, 2000 ) );
				break;
			case 3810:
			case 3830:
			case 3850:
			case 3870:
			case 3890:
			case 3910:
			case 3930:
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > (	160.0, 0 ),
													4.0, MAPIL::DegToRad( 90.0 ),
													10.0, 1, 2, 1000 ) );
				break;
			case 4030:
				m_pEnemyList->Add(	new Enemy3(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 100.0, 0.0 ),
												3.0, MAPIL::DegToRad( 90.0 ),
												5, 2, 6, 2000 ) );
				m_pEnemyList->Add(	new Enemy3(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 540.0, 0.0 ),
												3.0, MAPIL::DegToRad( 90.0 ),
												5, 2, 6, 2000 ) );
				break;
			case 4150:
			case 4170:
			case 4190:
			case 4210:
			case 4230:
			case 4250:
			case 4270:
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > (	320.0, 0 ),
													4.0, MAPIL::DegToRad( 90.0 ),
													10.0, 1, 2, 1000 ) );
				break;
			case 4360:
				m_pEnemyList->Add(	new Enemy3(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 100.0, 0.0 ),
												3.0, MAPIL::DegToRad( 90.0 ),
												5, 2, 6, 2000 ) );
				m_pEnemyList->Add(	new Enemy3(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 540.0, 0.0 ),
												3.0, MAPIL::DegToRad( 90.0 ),
												5, 2, 6, 2000 ) );
				break;
			case 4480:
			case 4500:
			case 4520:
			case 4540:
			case 4560:
			case 4580:
			case 4600:
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > (	240.0, 0 ),
													4.0, MAPIL::DegToRad( 90.0 ),
													10.0, 1, 2, 1000 ) );
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > (	360.0, 0 ),
													4.0, MAPIL::DegToRad( 90.0 ),
													10.0, 1, 2, 1000 ) );
				break;
			case 4700:
				m_pEnemyList->Add(	new Enemy3(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 100.0, 0.0 ),
												3.0, MAPIL::DegToRad( 90.0 ),
												5, 2, 6, 2000 ) );
				m_pEnemyList->Add(	new Enemy3(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 320.0, 0.0 ),
												3.0, MAPIL::DegToRad( 90.0 ),
												5, 2, 6, 2000 ) );
				m_pEnemyList->Add(	new Enemy3(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > ( 540.0, 0.0 ),
												3.0, MAPIL::DegToRad( 90.0 ),
												5, 2, 6, 2000 ) );
				break;
			case 4820:
			case 4840:
			case 4860:
			case 4880:
			case 4900:
			case 4920:
			case 4940:
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > (	210.0, 0 ),
													4.0, MAPIL::DegToRad( 90.0 ),
													10.0, 1, 2, 1000 ) );
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
													MAPIL::Vector2 < double > (	430.0, 0 ),
													4.0, MAPIL::DegToRad( 90.0 ),
													10.0, 1, 2, 1000 ) );
				break;
			default:
				break;
		}

		if( m_Frame >= 5140 && m_Frame <= 6000 ){
			if( ( m_Frame % 40 ) == 0 ){
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > (	m_Frame % 240 + 240, 0 ),
												4.0, MAPIL::DegToRad( m_Frame % 30 + 90 ),
												10.0, 1, 2, 1000 ) );
			}
			if( ( m_Frame % 30 ) == 0 ){
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > (	0, m_Frame % 100 + 100 ),
												4.0, MAPIL::DegToRad( m_Frame % 60 - 30 ),
												10.0, 1, 2, 1000 ) );
			}
			if( ( m_Frame % 30 ) == 15 ){
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > (	640, m_Frame % 100 + 100 ),
												4.0, MAPIL::DegToRad( m_Frame % 60 + 150 ),
												10.0, 1, 2, 1000 ) );
			}
			if( ( m_Frame % 50 ) == 0 ){
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > (	0, 0 ),
												4.0, MAPIL::DegToRad( m_Frame % 35 + 10 ),
												10.0, 1, 2, 1000 ) );
			}
			if( ( m_Frame % 50 ) == 25 ){
				m_pEnemyList->Add( new Enemy1(	&( *itP ), m_pEnemyShotList,
												MAPIL::Vector2 < double > (	640, 0 ),
												4.0, MAPIL::DegToRad( m_Frame % 35 + 135 ),
												10.0, 1, 2, 1000 ) );
			}
		}

		if( m_Frame == 6200 ){
			ResourceHandler* p = ResourceHandler::GetInst();
			p->m_StreamingBuf->Stop();
			
		}

		if( m_Frame == 6350 ){
			m_BossBGM->Play();
			m_pEnemyList->Add( new Boss1( &( *itP ), m_pEnemyShotList, 2, m_PlayerHPBar ) );
		}
	}

	
}