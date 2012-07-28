#ifndef INCLUDED_RTG_SCRIPTEDSTAGE_H
#define INCLUDED_RTG_SCRIPTEDSTAGE_H

#include "Scene.h"

#include "ScriptCompiler.h"
#include "TaskList.hpp"
#include "CirclePlayer.h"
#include "CircleEnemy.h"
#include "CircleReflectedShot.h"
#include "Effect2D.h"

#include "StageVCPU.h"
#include "ScriptType.h"

namespace RTG
{
	//enum PlayMode
	//{
	//	PLAY_MODE_REPLAY = 0,
	//	PLAY_MODE_NORMAL = 1,
	//};

	class ScriptCompiler;
	class ScriptedStage : public Scene
	{
	private:
		// スクリプトコンパイラ
		ScriptCompiler*		m_pCompiler;		// コンパイラ本体
		VM::Data*			m_pScriptCmd;		// スクリプトコマンド
		StageVCPU			m_VirtualMachine;	// 仮想マシン
		StageInfo			m_StageInfo;		// ステージ情報

		// ステージの状態
		int					m_Frame;		// フレーム数
		bool				m_Cleared;		// ステージクリアフラグ
		bool				m_GameOvered;	// ゲームオーバフラグ
		bool				m_Paused;		// ポーズフラグ
		int					m_StageNo;		// ステージ番号

		// 各種オブジェクトリスト
		typedef TaskList < CirclePlayer >			CirclePlayerList;
		typedef TaskList < CircleEnemy >			CircleEnemyList;
		typedef TaskList < CircleEnemyShot >		CircleEnemyShotList;
		typedef TaskList < CircleReflectedShot >	CircleReflectedShotList;
		typedef TaskList < Effect2D >				Effect2DList;
		CirclePlayerList			m_PlayerList;			// プレイヤーリスト
		CircleEnemyList				m_EnemyList;			// 敵リスト
		CircleEnemyShotList			m_EnemyShotList;		// 敵弾リスト
		CircleReflectedShotList		m_ReflectedShotList;	// 反射弾リスト
		Effect2DList				m_Effect2DList;				// 2Dエフェクトリスト
		
		// 非公開メソッド群
		void UpdatePlayer();					// プレイヤーの情報を更新
		void UpdateEnemy();						// 敵の情報を更新
		void UpdateEnemyShot();					// 敵の弾の情報を更新
		void UpdateReflectedShot();				// 反射弾の情報を更新
		void UpdateEffect2D();					// エフェクトの更新
		void CollidePlayerAndEnemy();			// プレイヤーと敵との衝突判定
		void CollideEnemyAndReflectedShot();	// 敵と反射弾との衝突判定
	public:
		ScriptedStage( ScriptCompiler* pCompiler, int stage );
		~ScriptedStage();
		void Update();				// データ更新
		void Draw();				// 描画
		void Init();				// 初期化
		bool IsLoading() const;		// ロード中か？
	};
}

#endif