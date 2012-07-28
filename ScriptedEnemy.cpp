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
																							0.0,
																							20,
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
									int x,
									int y )	:	CircleEnemy(	pList,
																MAPIL::Vector2 < double > ( x, y ),
																1.0, 0.0, 0.0, 20, 100 ),
																m_pCompiler( pCompiler ),
																m_pScriptCmd( NULL ),
																m_ScriptID( id ),
																m_VirtualMachine()
	{
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

		MAPIL::DrawTexture( m_EnemyInfo.m_ImgID, m_EnemyInfo.m_PosX, m_EnemyInfo.m_PosY, 0.0f );
	}

	bool ScriptedEnemy::Move()
	{
		// スクリプトコマンドの実行
		// スクリプトが終了していないかチェック
		if( m_VirtualMachine.Terminated() ){
			return false;
		}
		m_VirtualMachine.Run();

		++m_EnemyInfo.m_Counter;

		return true;
	}

	void ScriptedEnemy::Init()
	{
		// 敵情報を設定
		MAPIL::ZeroObject( &m_EnemyInfo, sizeof( m_EnemyInfo ) );
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
}