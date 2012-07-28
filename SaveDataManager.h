#ifndef INCLUDED_RTG_SAVEDATAMANAGER_H
#define INCLUDED_RTG_SAVEDATAMANAGER_H

#include <iostream>

namespace RTG
{
	enum StageProgress
	{
		STAGE_PROGRESS_STAGE1			= 0,
		STAGE_PROGRESS_COMPLETED		= 1,
	};

	// スコアエントリ
	struct ScoreEntry
	{
		char		m_Name[ 16 ];		// 名前
		int			m_Score;			// 得点
		int			m_Progress;			// 進行度
		::time_t	m_Date;				// 日時
		bool		m_Used;				// 使用中か
	};

	class SaveDataManager
	{
		bool			m_Updated;
		const char*		m_pFileName;
		
		struct Configuration
		{
		};
		// ゲーム進行度
		struct Progress
		{
			int			m_RunCount;			// 起動回数
		};
		// スコア
		struct ScoreHistory
		{
			ScoreEntry		m_Entry[ 32 ];
		};

		Configuration			m_Configuration;	// ゲーム設定
		Progress				m_Progress;			// ゲーム進行度
		ScoreHistory			m_ScoreHistory;		// スコア履歴

	public:
		SaveDataManager( const char* pFileName );
		~SaveDataManager();
		void UpdateScore( const char* pName, int score, int progress );
		void IncRunCount();
		bool IsUpdated() const;
		ScoreEntry GetScoreEntry( int rank ) const;
		void Save();
		void Load();
	};
}

#endif