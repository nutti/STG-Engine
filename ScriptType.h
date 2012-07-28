#ifndef INCLUDED_SCRIPTTYPE_H
#define INCLUDED_SCRIPTTYPE_H

#include "TaskList.hpp"
#include "CircleEnemyShot.h"
#include "CircleEnemy.h"

namespace RTG
{
	// �X�N���v�g�G���W���ɓn���G���
	struct EnemyInfo
	{
		TaskList < CircleEnemyShot >*	m_pShotList;
		double							m_Angle;
		int								m_Counter;
		double							m_Speed;
		int								m_HP;
		float							m_PosX;
		float							m_PosY;
		int								m_ImgID;
	};

	// �X�N���v�g�G���W���ɓn���X�e�[�W���
	class ScriptCompiler;
	struct StageInfo
	{
		ScriptCompiler*					m_pCompiler;
		TaskList < CircleEnemy >*		m_pEnemyList;
		TaskList < CircleEnemyShot >*	m_pEnemyShotList;
		int*							m_pFrame;
	};
}

#endif