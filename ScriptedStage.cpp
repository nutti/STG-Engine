#include "ScriptedStage.h"
#include "Menu.h"

#include "Math.h"

#include "NormalPlayer.h"
#include "ReflectedShot1.h"

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

	ScriptedStage::ScriptedStage( ScriptCompiler* pCompiler, int stage ) :	m_pCompiler( pCompiler ),
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
																			m_StageNo( stage ),
																			m_KillTotal( 0 ),
																			m_ReflectTotal( 0 ),
																			m_HitTotal( 0 )
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

		DeleteTaskList( &m_PlayerList );
		DeleteTaskList( &m_EnemyList );
		DeleteTaskList( &m_EnemyShotList );
		DeleteTaskList( &m_ReflectedShotList );
		DeleteTaskList( &m_Effect2DList );

		MAPIL::DeleteStaticBuffer( m_BombbedSE );
		MAPIL::DeleteStaticBuffer( m_ReflectSE );
		//MAPIL::DeleteStreamingBuffer( m_StageBGM );
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

			++m_Frame;
		}
		else{
			// ポーズ時の処理
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
		CircleEnemyList::Iterator it( &m_EnemyList );
		CircleEnemyList::Iterator itEnd( &m_EnemyList );
		itEnd.End();

		// 敵の情報を更新
		for( it.Begin(); it != itEnd; ++it ){
			if( !( *it ).Update() ){
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
					if( ( *itEnemy ).GetHP() <= 0 ){
						//p->m_pScore->Add( ( *itEnemy ).GetScore() );
						++m_KillTotal;
						/*m_pEffect2DList->Add( new BombedEffect1(	p->m_Sprite,
																	p->m_Texture[ 12 ],
																	MAPIL::Vector2 < float > (	static_cast < float > ( ( *itEnemy ).GetPos().m_X ),
																								static_cast < float > ( ( *itEnemy ).GetPos().m_Y ) ),
																	0.3f,
																	0.1 ) );*/
						if( ( *itEnemy ).IsBoss() ){
							m_Cleared = true;
						}
					}
					else{
						//p->m_pScore->Add( 100 );
					}
				}
			}
		}
	}

	void ScriptedStage::Draw()
	{
	}

	void ScriptedStage::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		// 削除要求のオブジェクトを完全削除
		MAPIL::RefleshResources();

		// スクリプトのコンパイル
		p->m_pCompiler->Compile( m_StageNo );
		p->SetupHandle();


		// ステージ情報の設定
		MAPIL::ZeroObject( &m_StageInfo, sizeof( m_StageInfo ) );
		m_StageInfo.m_pCompiler = m_pCompiler;
		m_StageInfo.m_pEnemyList = &m_EnemyList;
		m_StageInfo.m_pEnemyShotList = &m_EnemyShotList;
		m_StageInfo.m_pFrame = &m_Frame;
		m_StageInfo.m_pPlayerList = &m_PlayerList;
		m_StageInfo.m_pEffect2DList = &m_Effect2DList;
		m_StageInfo.m_pRandSeed = &p->m_RdmSeed;
		// スクリプトコマンドの取得
		m_pScriptCmd = m_pCompiler->GetStageScript();
		// 仮想マシンのセットアップ
		m_VirtualMachine.Init( m_pScriptCmd, &m_StageInfo );


		// 各リストの初期化
		m_PlayerList.Init();
		m_EnemyList.Init();
		m_EnemyShotList.Init();
		m_ReflectedShotList.Init();
		m_Effect2DList.Init();

		// プレイヤーの作成
		NormalPlayer* pNewPlayer = new NormalPlayer( MAPIL::Vector2 < double > ( 320.0, 430.0f ) );
		pNewPlayer->Init();
		m_PlayerList.Add( pNewPlayer );

		// リソースの読み込み
		m_ReflectSE = MAPIL::CreateStaticBuffer( "Resource/rtg_se1.wav" );
		m_BombbedSE = MAPIL::CreateStaticBuffer( "Resource/rtg_se2.wav" );
		//m_StageBGM = MAPIL::CreateStreamingBuffer( "Resource/rtg_stage2.wav" );

		// ランダムシードの初期化
		ResetRandSeed();

		//MAPIL::PlayStreamingBuffer( m_StageBGM );
	}

	bool ScriptedStage::IsLoading() const
	{
		bool ret;

		ret = m_pCompiler->Loaded();

		return !ret;
	}



	
}