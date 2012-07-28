#ifndef INCLUDED_ENEMYVCPU_H
#define INCLUDED_ENEMYVCPU_H

#pragma once

#include "ScriptType.h"
#include "ScriptEngine/VM.h"

namespace RTG
{
	struct EnemyInfo;
	class EnemyVCPU : public VM::VCPU
	{
	private:
		EnemyInfo*		m_pEnemyInfo;

		void SysGetEnemyPosX();
		void SysGetEnemyPosY();
		void SysGetEnemyHP();
		void SysGetEnemySpeed();
		void SysGetEnemyCounter();
		void SysGetEnemyAngle();
		void SysSetEnemyPos();
		void SysSetEnemyAngle();
		void SysSetEnemySpeed();
		void SysSetEnemyHP();
		void SysSetEnemyImgID();
		void SysCreateEnemyShot1();
	public:
		EnemyVCPU();
		~EnemyVCPU();
		void Init( VM::Data* pData, EnemyInfo* pInfo );
		void OpSysCall( int val );
	};
}

#endif