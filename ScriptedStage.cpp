#include "ScriptedStage.h"
#include "Menu.h"

#include "Math.h"

#include "NormalPlayer.h"
#include "ReflectedShot1.h"
#include "GeneralButtonManager.h"
#include "EntryScore.h"


namespace RTG
{
	// 衝突判定
	static bool DoesCollide( CircleObj* pObj1, CircleObj* pObj2 )
	{
		MAPIL::Vector2 < double > diff = pObj1->m_Pos - pObj2->m_Pos;
		if( diff.GetNorm() < pObj1->m_Radius + pObj2->m_Radius ){
			return true;
		}
		return false;
	}

	ScriptedStage::ScriptedStage( ScriptCompiler* pCompiler, int stage, int playMode ) :	m_pCompiler( pCompiler ),
																							m_pScriptCmd( NULL ),
																							m_Frame( 0 ),
																							m_Cleared( false ),
																							m_GameOvered( false ),
																							m_Paused( false ),
																							m_PlayerList(),
																							m_EnemyList(),
																							m_EnemyShotList(),
																							m_ReflectedShotList(),
																							m_Effect2DList(),
																							m_Stage1EffectList(),
																							m_StageNo( stage ),
																							m_KillTotal( 0 ),
																							m_ReflectTotal( 0 ),
																							m_HitTotal( 0 ),
																							m_FinishedCounter( 0 ),
																							m_PlayMode( playMode )
	{
	}

	ScriptedStage::~ScriptedStage()
	{
		// 全リソースの開放
		for( unsigned int i = 0; i < m_ResourceMap.m_TextureMap.size(); ++i ){
			MAPIL::DeleteTexture( m_ResourceMap.m_TextureMap[ i ] );
		}

		m_StageNo = 0;
		m_pScriptCmd = NULL;
		m_Frame = 0;
		m_Cleared = false;
		m_GameOvered = false;
		m_Paused = false;
		m_KillTotal = 0;
		m_ReflectTotal = 0;
		m_HitTotal = 0;
		m_FinishedCounter = 0;

		DeleteTaskList( &m_PlayerList );
		DeleteTaskList( &m_EnemyList );
		DeleteTaskList( &m_EnemyShotList );
		DeleteTaskList( &m_ReflectedShotList );
		DeleteTaskList( &m_Effect2DList );

		MAPIL::DeleteStaticBuffer( m_BombbedSE );
		MAPIL::DeleteStaticBuffer( m_ReflectSE );
		ResourceHandler::GetInst()->ReleaseAllStageResources();
		MAPIL::DeleteTexture( m_BGTexture[ 0 ] );
		MAPIL::DeleteTexture( m_BGTexture[ 1 ] );
		MAPIL::DeleteTexture( m_PointSpriteTexture );
		MAPIL::DeletePointSprite( m_PointSprite );
		MAPIL::DeleteCamera( m_PointSpriteCamera );
	}

	void ScriptedStage::Update()
	{
		ResourceHandler* p = ResourceHandler::GetInst();
		
		if( !m_Paused ){

			MAPIL::BeginRendering2DGraphics();

			UpdatePlayer();					// プレイヤーの情報を更新
			UpdateEnemy();					// 敵の情報を更新
			UpdateEnemyShot();				// 敵の弾の情報を更新
			UpdateReflectedShot();			// 反射弾の情報を更新
			UpdateEffect2D();				// エフェクトの更新
			UpdateStage1Effect();			// ポイントスプライトエフェクトの更新
			CollidePlayerAndEnemy();		// プレイヤーと敵衝突判定
			CollideEnemyAndReflectedShot();	// 敵と反射弾との衝突判定

			MAPIL::EndRendering2DGraphics();

			// スクリプトコマンドの実行
			// スクリプトが終了していないかチェック
			m_VirtualMachine.Run();
			if( m_VirtualMachine.Terminated() ){
				SetNextScene( new Menu() );
				return;
			}

			// スコア更新/表示
			p->m_pScore->Update();
			p->m_pScore->Display( 70.0f, 20.0f, 16.0f, 10 );

			// フレーム数更新
			++m_Frame;

			// ポーズを行う時の処理
			if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_PAUSE ) ){
				m_Paused = true;
			}
			// クリア/ゲームオーバー時の処理
			if( m_Cleared || m_GameOvered ){
				++m_FinishedCounter;
				if( m_FinishedCounter >= 120 ){
					if( m_PlayMode == PLAY_MODE_NORMAL ){
						if( m_Cleared ){
							SetNextScene( new EntryScore( p->m_pScore->Get(), STAGE_PROGRESS_COMPLETED ) );
						}
						else if( m_GameOvered ){
							SetNextScene( new EntryScore( p->m_pScore->Get(), STAGE_PROGRESS_STAGE1 ) );
						}
					}
					else if( m_PlayMode == PLAY_MODE_REPLAY ){
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
					MAPIL::BeginRendering2DGraphics();
					MAPIL::DrawString( 100.0f, 100.0f, "Stage 1 Clear \n\n Killed : %d\n Hit ratio : %.2f", m_KillTotal, m_HitTotal * 1.0f / m_ReflectTotal );
					MAPIL::EndRendering2DGraphics();
				}
			}

			// リプレイ用のキー保存
			if( m_PlayMode == PLAY_MODE_NORMAL ){
				char str[ GENERAL_BUTTON_TOTAL ];
				p->m_pGBManager->CopyCurState( str );
				p->m_pReplaySaver->Add( str );
			}

			

		}
		// ポーズ時の処理
		else{
			// ポーズ解除の時の処理
			if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_PAUSE ) ){
				m_Paused = false;
			}
		}
	}

	void ScriptedStage::UpdatePlayer()
	{
		CirclePlayerList::Iterator it( &m_PlayerList );
		CirclePlayerList::Iterator itEnd( &m_PlayerList );
		itEnd.End();

		// プレイヤーの情報の更新
		for( it.Begin(); it != itEnd; ++it ){
			if( !( *it ).Update() ){
				it.Remove();
				m_GameOvered = true;	// ゲームオーバー
			}
			else{
				ResourceHandler* p = ResourceHandler::GetInst();
				p->m_RdmSeed.m_PosX = ( *it ).GetPos().m_X;
				p->m_RdmSeed.m_PosY = ( *it ).GetPos().m_Y;
				p->m_RdmSeed.m_Score = p->m_pScore->Get();
				p->m_RdmSeed.m_HitTotal = m_HitTotal;
				p->m_RdmSeed.m_ReflectTotal = m_ReflectTotal;
				p->m_RdmSeed.m_Frame = m_Frame;
			}
		}
	}

	void ScriptedStage::UpdateEnemy()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		CircleEnemyList::Iterator it( &m_EnemyList );
		CircleEnemyList::Iterator itEnd( &m_EnemyList );
		itEnd.End();

		// 敵の情報を更新
		for( it.Begin(); it != itEnd; ++it ){
			if( !( *it ).Update() ){
				if( ( *it ).GetHP() <= 0 ){
					++m_KillTotal;
					p->m_pScore->Add( ( *it ).GetScore() );
					if( ( *it ).IsBoss() ){
						m_Cleared = true;
					}
				}
				it.Remove();
			}
		}
	}

	void ScriptedStage::UpdateEnemyShot()
	{
		CircleEnemyShotList::Iterator it( &m_EnemyShotList );
		CircleEnemyShotList::Iterator itEnd( &m_EnemyShotList );
		itEnd.End();

		// 敵の弾の情報を更新
		for( it.Begin(); it != itEnd; ++it ){
			if( !( *it ).Update() ){
				it.Remove();
			}
		}	
	}

	void ScriptedStage::UpdateReflectedShot()
	{
		CircleReflectedShotList::Iterator it( &m_ReflectedShotList );
		CircleReflectedShotList::Iterator itEnd( &m_ReflectedShotList );
		itEnd.End();

		// 反射弾の情報を更新
		for( it.Begin(); it != itEnd; ++it ){
			if( !( *it ).Update() ){
				it.Remove();
			}
		}
	}

	void ScriptedStage::UpdateEffect2D()
	{
		Effect2DList::Iterator it( &m_Effect2DList );
		Effect2DList::Iterator itEnd( &m_Effect2DList );
		itEnd.End();

		// 反射弾の情報を更新
		for( it.Begin(); it != itEnd; ++it ){
			if( !( *it ).Update() ){
				it.Remove();
			}
		}
	}

	void ScriptedStage::UpdateStage1Effect()
	{
		Stage1Effect1List::Iterator it( &m_Stage1EffectList );
		Stage1Effect1List::Iterator itEnd( &m_Stage1EffectList );
		itEnd.End();

		// 反射弾の情報を更新
		for( it.Begin(); it != itEnd; ++it ){
			if( !( *it ).Update() ){
				int index = ( *it ).GetIndex();
					it.Remove();
					m_Stage1EffectList.Add( new Stage1Effect1(	m_PointSprite,
																MAPIL::Vector3 < float > (	-5.0f + 10.0f * rand() / RAND_MAX,
																						-1.0f - 6.0f * rand() / RAND_MAX,
																						-1.0f - 30.0f * rand() / RAND_MAX ),
																						-0.01 - 0.1 * rand() / RAND_MAX,
																						MAPIL::DegToRad( -70.0 - 40.0 * rand() / RAND_MAX ),
																						index ) );
			}
		}
	}

	void ScriptedStage::CollidePlayerAndEnemy()
	{
		CirclePlayerList::Iterator itPlayer( &m_PlayerList );
		CirclePlayerList::Iterator itPlayerEnd( &m_PlayerList );
		CircleEnemyShotList::Iterator itEnemyShot( &m_EnemyShotList );
		CircleEnemyShotList::Iterator itEnemyShotEnd( &m_EnemyShotList );

		itPlayerEnd.End();

		for( itPlayer.Begin(); itPlayer != itPlayerEnd; ++itPlayer ){
			itEnemyShotEnd.End();
			for( itEnemyShot.Begin(); itEnemyShot != itEnemyShotEnd; ++itEnemyShot ){
				if( DoesCollide( &( *itPlayer ), &( *itEnemyShot ) ) ){
					if( ((NormalPlayer*)&(*itPlayer))->IsReflectMode() ){
						ResourceHandler* p = ResourceHandler::GetInst();
						p->m_pScore->Add( 1 );
						((NormalPlayer*)&(*itPlayer))->DecEnergy( 100 );
						m_ReflectedShotList.Add( new ReflectedShot1( *itEnemyShot, *(NormalPlayer*)&(*itPlayer), (*itEnemyShot).GetImgID() ) );
						MAPIL::PlayStaticBuffer( m_ReflectSE );
					}
					else{
						((NormalPlayer*)&(*itPlayer))->Damage( 1 );
					}
					itEnemyShot.Remove();
				}
			}
		}
	}

	void ScriptedStage::CollideEnemyAndReflectedShot()
	{
		CircleEnemyList::Iterator itEnemy( &m_EnemyList );
		CircleEnemyList::Iterator itEnemyEnd( &m_EnemyList );
		CircleReflectedShotList::Iterator itReflectedShot( &m_ReflectedShotList );
		CircleReflectedShotList::Iterator itReflectedShotEnd( &m_ReflectedShotList );

		itEnemyEnd.End();
		itReflectedShotEnd.End();

		for( itReflectedShot.Begin(); itReflectedShot != itReflectedShotEnd; ++itReflectedShot ){
			for( itEnemy.Begin(); itEnemy != itEnemyEnd; ++itEnemy ){
				if( DoesCollide( &(*itEnemy), &(*itReflectedShot) ) ){
					itReflectedShot.Remove();
					( *itEnemy ).Damage( 1 );
					++m_ReflectTotal;
					MAPIL::PlayStaticBuffer( m_BombbedSE );
					// 2重判定が起こる可能性があり、要修正
					// 倒した時に得点が入るようにする等
					ResourceHandler* p = ResourceHandler::GetInst();
					p->m_pScore->Add( 100 );
					break;
				}
			}
		}
	}

	void ScriptedStage::Draw()
	{
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
			MAPIL::SetCameraViewTrans(	m_Pos.m_X, m_Pos.m_Y, m_Pos.m_Z,
										0.0f, 0.0f, m_Pos.m_Z - 1.5f,
										tiltX, tiltY, 0.0f );
		}
		else if( m_Frame > 3750 && m_Frame <= 4150 ){
			float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( 4150 - m_Frame ) * 20.0f / 400 ) ) );
			float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( 4150 - m_Frame ) * 20.0f / 400 ) ) );
			MAPIL::SetCameraViewTrans(	m_Pos.m_X, m_Pos.m_Y, m_Pos.m_Z,
										0.0f, 0.0f, m_Pos.m_Z - 1.5f,
										tiltX, tiltY, 0.0f );
		}
		else if( m_Frame > 4150 && m_Frame <= 4550 ){
			float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( 4150 - m_Frame ) * 20.0f / 400 ) ) );
			float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( 4150 - m_Frame ) * 20.0f / 400 ) ) );
			MAPIL::SetCameraViewTrans(	m_Pos.m_X, m_Pos.m_Y, m_Pos.m_Z,
										0.0f, 0.0f, m_Pos.m_Z - 1.5f,
										tiltX, tiltY, 0.0f );
		}
		else if( m_Frame > 4550 && m_Frame <= 4950 ){
			float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( m_Frame - 4950 ) * 20.0f / 400 ) ) );
			float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( m_Frame - 4950 ) * 20.0f / 400 ) ) );
			MAPIL::SetCameraViewTrans(	m_Pos.m_X, m_Pos.m_Y, m_Pos.m_Z,
										0.0f, 0.0f, m_Pos.m_Z - 1.5f,
										tiltX, tiltY, 0.0f );
		}
		else if( m_Frame >= 6200 ){
			const int CYCLE = 1000;
			const int HALF_CYCLE = 1000 / 2;
			int frame = m_Frame - 6200;
			frame %= CYCLE;
			if( frame < HALF_CYCLE / 2 ){
				float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( frame * 10.0f / HALF_CYCLE ) ) );
				float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( frame * 10.0f / HALF_CYCLE ) ) );
				MAPIL::SetCameraViewTrans(	m_Pos.m_X, m_Pos.m_Y, m_Pos.m_Z,
											tiltX / 5.0f, 0.0f, m_Pos.m_Z - 1.5f,
											tiltX, tiltY, 0.0f );
			}
			else if( frame >= HALF_CYCLE / 2 && frame < HALF_CYCLE ){
				float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( HALF_CYCLE - frame ) * 10.0f / HALF_CYCLE ) ) );
				float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( HALF_CYCLE - frame ) * 10.0f / HALF_CYCLE ) ) );
				MAPIL::SetCameraViewTrans(	m_Pos.m_X, m_Pos.m_Y, m_Pos.m_Z,
											tiltX / 5.0f, 0.0f, m_Pos.m_Z - 1.5f,
											tiltX, tiltY, 0.0f );
			}
			else if( frame >= HALF_CYCLE && frame < HALF_CYCLE * 3 / 2 ){
				float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( HALF_CYCLE - frame ) * 10.0f / HALF_CYCLE ) ) );
				float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( HALF_CYCLE - frame ) * 10.0f / HALF_CYCLE ) ) );
				MAPIL::SetCameraViewTrans(	m_Pos.m_X, m_Pos.m_Y, m_Pos.m_Z,
											tiltX / 5.0f, 0.0f, m_Pos.m_Z - 1.5f,
											tiltX, tiltY, 0.0f );
			}
			else if( frame >= HALF_CYCLE * 3 / 2 && frame < CYCLE ){
				float tiltX = static_cast < float > ( ::sin( MAPIL::DegToRad( ( frame - CYCLE ) * 10.0f / HALF_CYCLE ) ) );
				float tiltY = static_cast < float > ( ::cos( MAPIL::DegToRad( ( frame - CYCLE ) * 10.0f / HALF_CYCLE ) ) );
				MAPIL::SetCameraViewTrans(	m_Pos.m_X, m_Pos.m_Y, m_Pos.m_Z,
											tiltX / 5.0f, 0.0f, m_Pos.m_Z - 1.5f,
											tiltX, tiltY, 0.0f );
			}
		}
		else{
			MAPIL::SetCameraViewTrans(	m_Pos.m_X, m_Pos.m_Y, m_Pos.m_Z,
										0.0f, 0.0f, m_Pos.m_Z - 1.5f,
										0.0f, 1.0f, 0.0f );
		}


		// 背景の描画
		MAPIL::SetCameraProjTrans(	static_cast < float > ( MAPIL::DegToRad( 30.0 ) ),
									static_cast < float > ( 640.0f * 1.0f / 480.0f ),
									0.01f, 50.0f );
		MAPIL::EnableCamera();

		MAPIL::EnableFog();
		MAPIL::SetFogParam(	MAPIL::GetColorARGBValue( 122, 100, 100, (unsigned char)0 ),
							MAPIL::FOG_MODE_EXP,
							10.0f,
							20.0f,
							0.2f );

		for( int j = 0; j < 10; ++j ){
			MAPIL::Polygon3DVertexFormat fmt[ 4 ];
			MAPIL::ZeroObject( fmt, sizeof( fmt ) );
			fmt[ 0 ].m_Pos.m_X = -0.5f;
			fmt[ 0 ].m_Pos.m_Z = -0.5f + 1.0f * ( j - 8 );
			fmt[ 1 ].m_Pos.m_X = -0.5f;
			fmt[ 1 ].m_Pos.m_Z = 0.5f + 1.0f * ( j - 8 );
			fmt[ 2 ].m_Pos.m_X = 0.5f;
			fmt[ 2 ].m_Pos.m_Z = -0.5f + 1.0f * ( j - 8 );
			fmt[ 3 ].m_Pos.m_X = 0.5f;
			fmt[ 3 ].m_Pos.m_Z = 0.5f + 1.0f * ( j - 8 );
			fmt[ 0 ].m_Tex.m_U = 0.0f;
			fmt[ 0 ].m_Tex.m_V = 0.0f;
			fmt[ 1 ].m_Tex.m_U = 0.0f;
			fmt[ 1 ].m_Tex.m_V = 1.0f;
			fmt[ 2 ].m_Tex.m_U = 1.0f;
			fmt[ 2 ].m_Tex.m_V = 0.0f;
			fmt[ 3 ].m_Tex.m_U = 1.0f;
			fmt[ 3 ].m_Tex.m_V = 1.0f;
			for( int i = 0; i < 4; ++i ){
				fmt[ i ].m_ColElm[ 0 ] = 255 * 7 / 10;
				fmt[ i ].m_ColElm[ 1 ] = 255 * 7 / 10;
				fmt[ i ].m_ColElm[ 2 ] = 255 * 7 / 10;
				fmt[ i ].m_ColElm[ 3 ] = 255 * 7 / 10;
			}
			MAPIL::DrawPolygon3D( fmt, 2, m_BGTexture[ 0 ] );
		}


		for( int i = 0; i < 10; ++i ){
			MAPIL::Polygon3DVertexFormat fmt[ 4 ];
			MAPIL::ZeroObject( fmt, sizeof( fmt ) );
			for( int j = 0; j < 4; ++j ){
				fmt[ j ].m_Pos.m_X = -0.5f;
			}
			fmt[ 0 ].m_Pos.m_Y = 1.0f;
			fmt[ 0 ].m_Pos.m_Z = 0.0f - 1.0f * i;
			fmt[ 1 ].m_Pos.m_Y = 0.0f;
			fmt[ 1 ].m_Pos.m_Z = 0.0f - 1.0f * i;
			fmt[ 2 ].m_Pos.m_Y = 1.0f;
			fmt[ 2 ].m_Pos.m_Z = 1.0f - 1.0f * i;
			fmt[ 3 ].m_Pos.m_Y = 0.0f;
			fmt[ 3 ].m_Pos.m_Z = 1.0f - 1.0f * i;

			fmt[ 0 ].m_Tex.m_U = 0.0f;
			fmt[ 0 ].m_Tex.m_V = 0.0f;
			fmt[ 1 ].m_Tex.m_U = 0.0f;
			fmt[ 1 ].m_Tex.m_V = 1.0f;
			fmt[ 2 ].m_Tex.m_U = 1.0f;
			fmt[ 2 ].m_Tex.m_V = 0.0f;
			fmt[ 3 ].m_Tex.m_U = 1.0f;
			fmt[ 3 ].m_Tex.m_V = 1.0f;
			for( int j = 0; j < 4; ++j ){
				fmt[ j ].m_ColElm[ 0 ] = 255 * 7 / 10;
				fmt[ j ].m_ColElm[ 1 ] = 255 * 7 / 10;
				fmt[ j ].m_ColElm[ 2 ] = 255 * 7 / 10;
				fmt[ j ].m_ColElm[ 3 ] = 255 * 7 / 10;
			}
			MAPIL::DrawPolygon3D( fmt, 2, m_BGTexture[ 1 ] );
		}

		for( int i = 0; i < 10; ++i ){
			MAPIL::Polygon3DVertexFormat fmt[ 4 ];
			MAPIL::ZeroObject( fmt, sizeof( fmt ) );
			for( int j = 0; j < 4; ++j ){
				fmt[ j ].m_Pos.m_X = 0.5f;
			}
			fmt[ 0 ].m_Pos.m_Y = 1.0f;
			fmt[ 0 ].m_Pos.m_Z = 1.0f - 1.0f * i;
			fmt[ 1 ].m_Pos.m_Y = 0.0f;
			fmt[ 1 ].m_Pos.m_Z = 1.0f - 1.0f * i;
			fmt[ 2 ].m_Pos.m_Y = 1.0f;
			fmt[ 2 ].m_Pos.m_Z = 0.0f - 1.0f * i;
			fmt[ 3 ].m_Pos.m_Y = 0.0f;
			fmt[ 3 ].m_Pos.m_Z = 0.0f - 1.0f * i;

			fmt[ 0 ].m_Tex.m_U = 0.0f;
			fmt[ 0 ].m_Tex.m_V = 0.0f;
			fmt[ 1 ].m_Tex.m_U = 0.0f;
			fmt[ 1 ].m_Tex.m_V = 1.0f;
			fmt[ 2 ].m_Tex.m_U = 1.0f;
			fmt[ 2 ].m_Tex.m_V = 0.0f;
			fmt[ 3 ].m_Tex.m_U = 1.0f;
			fmt[ 3 ].m_Tex.m_V = 1.0f;
			for( int j = 0; j < 4; ++j ){
				fmt[ j ].m_ColElm[ 0 ] = 255 * 7 / 10;
				fmt[ j ].m_ColElm[ 1 ] = 255 * 7 / 10;
				fmt[ j ].m_ColElm[ 2 ] = 255 * 7 / 10;
				fmt[ j ].m_ColElm[ 3 ] = 255 * 7 / 10;
			}
			MAPIL::DrawPolygon3D( fmt, 2, m_BGTexture[ 1 ] );
		}

		

		MAPIL::DisableFog();

		MAPIL::DisableZBuffering();
		MAPIL::EnableCamera( m_PointSpriteCamera );
		MAPIL::DrawPointSprite( m_PointSprite );
		MAPIL::EnableZBuffering();
	}

	void ScriptedStage::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		// 削除要求のオブジェクトを完全削除
		MAPIL::RefleshResources();

		// スコアの初期化
		p->m_pScore->Set( 0 );

		// 各リストの初期化
		m_PlayerList.Init();
		m_EnemyList.Init();
		m_EnemyShotList.Init();
		m_ReflectedShotList.Init();
		m_Effect2DList.Init();
		m_Stage1EffectList.Init();

		// プレイヤーの作成
		NormalPlayer* pNewPlayer = new NormalPlayer( MAPIL::Vector2 < double > ( 320.0, 430.0f ) );
		pNewPlayer->Init();
		m_PlayerList.Add( pNewPlayer );

		// リソースの読み込み
		m_ReflectSE = MAPIL::CreateStaticBuffer( p->m_Archiver, "archive/resource/se/rtg_se1.wav" );
		m_BombbedSE = MAPIL::CreateStaticBuffer( p->m_Archiver, "archive/resource/se/rtg_se2.wav" );
		m_BGTexture[ 0 ] = MAPIL::CreateTexture( p->m_Archiver, "archive/resource/texture/Background1.png" );
		m_BGTexture[ 1 ] = MAPIL::CreateTexture( p->m_Archiver, "archive/resource/texture/Background2.png" );
		m_PointSpriteTexture = MAPIL::CreateTexture( p->m_Archiver, "archive/resource/texture/Stage1BackgroundEffect.png" );
		m_PointSprite = MAPIL::CreatePointSprite( 200, m_PointSpriteTexture );
		m_PointSpriteCamera = MAPIL::CreateCamera();

		// バックグラウンドエフェクトの構築
		for( int i = 0; i < 200; ++i ){
			m_Stage1EffectList.Add(	new Stage1Effect1(	m_PointSprite,
															MAPIL::Vector3 < float > (	-5.0f + 10.0f * rand() / RAND_MAX,
																						-1.0f - 6.0f * rand() / RAND_MAX,
																						-1.0f - 30.0f * rand() / RAND_MAX ),
																						-0.01 - 0.1 * rand() / RAND_MAX,
																						MAPIL::DegToRad( -70.0 - 40.0 * rand() / RAND_MAX ),
																						i ) );
		}
		MAPIL::SetCameraViewTrans(	m_PointSpriteCamera,
									0.0f, 0.0f, 10.0f,
									0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f );
		MAPIL::SetCameraProjTrans(	m_PointSpriteCamera,
									static_cast < float > ( MAPIL::DegToRad( 30.0 ) ),
									640 * 1.0f / 480.0f,
									0.01f, 20.0f );

		// ステージ情報の設定
		MAPIL::ZeroObject( &m_StageInfo, sizeof( m_StageInfo ) );
		m_StageInfo.m_pCompiler = m_pCompiler;
		m_StageInfo.m_pEnemyList = &m_EnemyList;
		m_StageInfo.m_pEnemyShotList = &m_EnemyShotList;
		m_StageInfo.m_pFrame = &m_Frame;
		m_StageInfo.m_pPlayerList = &m_PlayerList;
		m_StageInfo.m_pEffect2DList = &m_Effect2DList;
		m_StageInfo.m_pRandSeed = &p->m_RdmSeed;

		m_Loading.Create();
		m_Loading.Reset();
		m_Loading.SetScene( m_StageNo, &m_VirtualMachine, &m_pScriptCmd, &m_StageInfo );
		m_Loading.Start();
		
		// ランダムシードの初期化
		ResetRandSeed();
	}

	bool ScriptedStage::IsLoading() const
	{
		return !m_Loading.IsFinished();
	}



	
}