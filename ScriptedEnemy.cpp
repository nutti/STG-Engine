#include "ScriptedEnemy.h"

#include "ScriptCompiler.h"

namespace RTG
{
	ScriptedEnemy::ScriptedEnemy(	ScriptCompiler* pCompiler,
									int id,
									TaskList < CircleEnemyShot >* pList ) : CircleEnemy(	pList,
																							MAPIL::Vector2 < double > ( 0.0, 0.0 ),
																							1.0,
																							0.0,
																							4.0,
																							5,
																							100 ),
																			m_pCompiler( pCompiler ),
																			m_pScriptCmd( NULL ),
																			m_ScriptID( id ),
																			m_VirtualMachine()
	{
	}

	ScriptedEnemy::ScriptedEnemy(	ScriptCompiler* pCompiler,
									int id,
									TaskList < CircleEnemyShot >* pList,
									TaskList < Effect2D >* pEffectList,
									int x,
									int y,
									TaskList < CirclePlayer >* pPlayerList,
									StageInfo* pInfo )	:	CircleEnemy(	pList,
																			MAPIL::Vector2 < double > ( x, y ),
																			1.0, 0.0, 4.0, 5, 100 ),
															m_pCompiler( pCompiler ),
															m_pScriptCmd( NULL ),
															m_ScriptID( id ),
															m_VirtualMachine()
	{
		MAPIL::ZeroObject( &m_EnemyInfo, sizeof( m_EnemyInfo ) );
		m_EnemyInfo.m_pPlayerList = pPlayerList;
		m_EnemyInfo.m_pEffect2DList = pEffectList;
		m_EnemyInfo.m_pRandSeed = pInfo->m_pRandSeed;
	}

	ScriptedEnemy::~ScriptedEnemy()
	{
		m_ScriptID = 0;
		m_pCompiler = NULL;
		m_pScriptCmd = NULL;
	}

	void ScriptedEnemy::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		MAPIL::DrawTexture( p->GetTextureHandle( m_EnemyInfo.m_ImgID ), m_EnemyInfo.m_PosX, m_EnemyInfo.m_PosY, 0.0f );

		if( m_EnemyInfo.m_IsBoss ){
			MAPIL::DrawTextureNonCentering( p->m_BossHPBar, 12.0f, 50.0f, m_EnemyInfo.m_HP / 26.0f, 0.2f, 0.0f );
		}
	}

	bool ScriptedEnemy::Move()
	{
		m_Pos.m_X = m_EnemyInfo.m_PosX;
		m_Pos.m_Y = m_EnemyInfo.m_PosY;
		

		// スクリプトコマンドの実行
		// スクリプトが終了していないかチェック
		if( m_VirtualMachine.Terminated() ){
			return false;
		}
		m_VirtualMachine.Run();

		++m_EnemyInfo.m_Counter;

		m_Score = m_EnemyInfo.m_Score;
		m_Radius = m_EnemyInfo.m_ColRadius;
		m_IsBoss = m_EnemyInfo.m_IsBoss;

		if( m_EnemyInfo.m_HP <= 0 ){
			return false;
		}

		return true;
	}

	void ScriptedEnemy::Init()
	{
		// 敵情報を設定
		m_EnemyInfo.m_Angle = m_Angle;
		m_EnemyInfo.m_Counter = m_Counter;
		m_EnemyInfo.m_HP = m_HP;
		m_EnemyInfo.m_PosX = m_Pos.m_X;
		m_EnemyInfo.m_PosY = m_Pos.m_Y;
		m_EnemyInfo.m_pShotList = m_pShotList;
		m_EnemyInfo.m_Speed = m_Speed;
		m_EnemyInfo.m_ImgID = 0;
		// スクリプトの取得
		m_pScriptCmd = m_pCompiler->GetEnemyScript( m_ScriptID );
		// 仮想マシンのセットアップ
		m_VirtualMachine.Init( m_pScriptCmd, &m_EnemyInfo );
	}

	MAPIL::Vector2 < double > ScriptedEnemy::GetPos() const
	{
		return MAPIL::Vector2 < double > ( m_EnemyInfo.m_PosX, m_EnemyInfo.m_PosY );
	}

	void ScriptedEnemy::Damage( int dec )
	{
		m_EnemyInfo.m_HP -= dec;
	}

	int ScriptedEnemy::GetHP() const
	{
		return m_EnemyInfo.m_HP;
	}
}