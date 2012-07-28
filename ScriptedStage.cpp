#include "ScriptedStage.h"
#include "Menu.h"

#include "Math.h"

namespace RTG
{
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
																			m_StageNo( stage )
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

		DeleteTaskList( &m_PlayerList );
		DeleteTaskList( &m_EnemyList );
		DeleteTaskList( &m_EnemyShotList );
		DeleteTaskList( &m_ReflectedShotList );
		DeleteTaskList( &m_Effect2DList );
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
		for( it.Begin(); it != itEnd; ++itEnd ){
			if( !( *it ).Update() ){
				it.Remove();
				m_GameOvered = true;	// ゲームオーバー
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

		for( itEnemyShot.Begin(); itEnemyShot != itEnemyShotEnd; ++itEnemyShot ){
			// 作成途中
		}
	}

	void ScriptedStage::CollideEnemyAndReflectedShot()
	{
		CircleEnemyList::Iterator itEnemy( &m_EnemyList );
		CircleEnemyList::Iterator itEnemyEnd( &m_EnemyList );
		CircleReflectedShotList::Iterator itReflectedShot( &m_ReflectedShotList );
		CircleReflectedShotList::Iterator itReflectedShotEnd( &m_ReflectedShotList );

		for( itReflectedShot.Begin(); itReflectedShot != itReflectedShotEnd; ++itReflectedShot ){
			for( itEnemy.Begin(); itEnemy != itEnemyEnd; ++itEnemy ){
				// 作成途中
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

		// 各種リソースの読み込み
		const int INITIAL_TEXTURE_MAP_RESERVE_CAP = 50;			// 初期のテクスチャMAP許容量
		m_ResourceMap.m_TextureMap.resize( INITIAL_TEXTURE_MAP_RESERVE_CAP );
		m_ResourceScriptData = p->m_pCompiler->GetResourceScriptData();
		// テクスチャの読み込み
		typedef std::map < int, std::string > ::iterator	TextureIter;
		TextureIter it = m_ResourceScriptData.m_TextureList.begin();
		for( ; it != m_ResourceScriptData.m_TextureList.end(); ++it ){
			// 許容値を超えたインデックスが必要な場合は、指定されたインデックスの2倍のサイズのresizeする。
			if( it->first > m_ResourceMap.m_TextureMap.size() ){
				m_ResourceMap.m_TextureMap.resize( it->first * 2 );
			}
			m_ResourceMap.m_TextureMap[ it->first ] = MAPIL::CreateTexture( it->second.c_str() );
		}


		// ステージ情報の設定
		MAPIL::ZeroObject( &m_StageInfo, sizeof( m_StageInfo ) );
		m_StageInfo.m_pCompiler = m_pCompiler;
		m_StageInfo.m_pEnemyList = &m_EnemyList;
		m_StageInfo.m_pEnemyShotList = &m_EnemyShotList;
		m_StageInfo.m_pFrame = &m_Frame;
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

		// ランダムシードの初期化
		ResetRandSeed();
	}

	bool ScriptedStage::IsLoading() const
	{
		bool ret;

		ret = m_pCompiler->Loaded();

		return !ret;
	}



	// 衝突判定
	//bool DoesCollide( CircleObj* pObj1, CircleObj* pObj2 )
	//{
	//	MAPIL::Vector2 < double > diff = pObj1->m_Pos - pObj2->m_Pos;
	//	if( diff.GetNorm() < pObj1->m_Radius + pObj2->m_Radius ){
	//		return true;
	//	}
	//	return false;
	//}
}