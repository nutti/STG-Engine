#ifndef INCLUDED_STAGEVCPU_H
#define INCLUDED_STAGEVCPU_H

#include "ScriptType.h"
#include "ScriptEngine/VM.h"

namespace RTG
{
	struct StageInfo;
	class StageVCPU : public VM::VCPU
	{
	private:
		StageInfo*		m_pStageInfo;
		void SysAddEnemy();
		void SysAddEnemyIniPos();
		void SysGetFrame();
		void SysSetFrame();
		void SysUpdate();
		void SysGetRand();
	public:
		StageVCPU();
		~StageVCPU();
		void Init( VM::Data* pData, StageInfo* pInfo );
		void OpSysCall( int val );
	};
}

#endif