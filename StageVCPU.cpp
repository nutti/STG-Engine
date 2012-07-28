#include "StageVCPU.h"
#include "ScriptedEnemy.h"

namespace RTG
{
	StageVCPU::StageVCPU() : VM::VCPU()
	{
	}

	StageVCPU::~StageVCPU()
	{
	}

	void StageVCPU::Init( VM::Data* pData, StageInfo* pInfo )
	{
		m_pData = pData;
		m_pStageInfo = pInfo;
		VM::VCPU::Init();
	}

	void StageVCPU::SysAddEnemy()
	{
		Pop();
		ScriptedEnemy* pNewEnemy = new ScriptedEnemy( m_pStageInfo->m_pCompiler, 0, m_pStageInfo->m_pEnemyShotList );
		pNewEnemy->Init();
		m_pStageInfo->m_pEnemyList->Add( pNewEnemy );
	}

	void StageVCPU::SysAddEnemyIniPos()
	{
		Pop();
		int y = Top().m_Integer;
		Pop();
		int x = Top().m_Integer;
		Pop();
		int id = Top().m_Integer;
		Pop();
		ScriptedEnemy* pNewEnemy = new ScriptedEnemy(	m_pStageInfo->m_pCompiler,
														id,
														m_pStageInfo->m_pEnemyShotList, x, y );
		pNewEnemy->Init();
		m_pStageInfo->m_pEnemyList->Add( pNewEnemy );
	}

	void StageVCPU::SysGetFrame()
	{
		Pop();
		Push( *m_pStageInfo->m_pFrame );
	}

	void StageVCPU::OpSysCall( int val )
	{
		switch( val ){
			case VM::SYS_STAGE_ADD_ENEMY:
				SysAddEnemy();
				break;
			case VM::SYS_STAGE_ADD_ENEMY_INIPOS:
				SysAddEnemyIniPos();
				break;
			case VM::SYS_STAGE_GET_FRAME:
				SysGetFrame();
				break;
			default:
				VM::VCPU::OpSysCall( val );
				break;
		}
	}
}