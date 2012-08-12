#include "StageVCPU.h"
#include "ScriptedEnemy.h"

#include "Math.h"

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
		float y = Top().m_Float;
		Pop();
		float x = Top().m_Float;
		Pop();
		int id = Top().m_Integer;
		Pop();
		ScriptedEnemy* pNewEnemy = new ScriptedEnemy(	m_pStageInfo->m_pCompiler,
														id,
														m_pStageInfo->m_pEnemyShotList,
														m_pStageInfo->m_pEffect2DList, x, y, m_pStageInfo->m_pPlayerList,
														m_pStageInfo );
		pNewEnemy->Init();
		m_pStageInfo->m_pEnemyList->Add( pNewEnemy );
	}

	void StageVCPU::SysGetFrame()
	{
		Pop();
		Push( *m_pStageInfo->m_pFrame );
	}

	void StageVCPU::SysSetFrame()
	{
		Pop();
		int frame = Top().m_Integer;
		*m_pStageInfo->m_pFrame = frame;
	}

	void StageVCPU::SysGetRand()
	{
		Pop();
		Push( Rand() * 1.0f / RAND_MAXIMUM );
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
			case VM::SYS_STAGE_SET_FRAME:
				SysSetFrame();
				break;
			case VM::SYS_GET_RANDOM_F:
				SysGetRand();
				break;
			default:
				VM::VCPU::OpSysCall( val );
				break;
		}
	}
}