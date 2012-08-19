#ifndef INCLUDED_RTG_SCRIPTEDENEMY_H
#define INCLUDED_RTG_SCRIPTEDENEMY_H

#include "CircleEnemy.h"
#include "Effect2D.h"

#include "EnemyVCPU.h"

#include "ScriptType.h"

namespace RTG
{
	

	class ScriptCompiler;
	class ScriptedEnemy : public CircleEnemy
	{
	private:
		ScriptCompiler*		m_pCompiler;		// スクリプトコンパイラ
		VM::Data*			m_pScriptCmd;		// スクリプトコマンド
		int					m_ScriptID;			// スクリプトID
		EnemyInfo			m_EnemyInfo;		// スクリプトエンジンに渡す敵情報
		EnemyVCPU			m_VirtualMachine;	// 仮想実行マシン
	public:
		ScriptedEnemy(	ScriptCompiler* pCompiler,
						int id,
						TaskList < CircleEnemyShot >* pList );
		ScriptedEnemy(	ScriptCompiler* pCompiler,
						int id,
						TaskList < CircleEnemyShot >* pList,
						TaskList < Effect2D >* pEffectList,
						int x,
						int y,
						TaskList < CirclePlayer >* pPlayerList,
						StageInfo* pInfo );
		~ScriptedEnemy();
		void Draw();
		bool Move();
		void Damage( int dec );
		int GetHP() const;
		void Init();
		MAPIL::Vector2 < double > GetPos() const;
	};
}

#endif