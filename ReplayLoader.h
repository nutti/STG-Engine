#ifndef INCLUDED_RTG_REPLAYLOADER_H
#define INCLUDED_RTG_REPLAYLOADER_H

namespace RTG
{
	const int REPLAY_BUTTON_TOTAL	= 7;		// リプレイの保存に必要なボタン数
	const int MAXIMUM_HISTORY_ENTRY	= 65535;	// ヒストリエントリー数

	struct ReplayEntry
	{
		// ゲームのリプレイでは、押している状態のみ必要
		char	m_Histories[ MAXIMUM_HISTORY_ENTRY * REPLAY_BUTTON_TOTAL ];
	};

	class ReplayLoader
	{
		char			m_Name[ 16 ];
		int				m_Score;
		int				m_Progress;
		::time_t		m_Date;
		ReplayEntry		m_Entry;			// リプレイデータ本体
		int				m_EntryTotal;		// エントリ数
	public:
		ReplayLoader();
		~ReplayLoader();
		int Load( const char* pFileName );					// ロード（リプレイデータを読み込む）
		void Open( const char* pFileName );					// ロード（リプレイデータは読み込まない）
		const char* GetName() const;						// 名前の取得
		int GetScore() const;								// スコアの取得
		int GetProgress() const;							// 進行度の取得
		::time_t GetDate() const;							// 日時の取得
		void GetReplayData( ReplayEntry* pEntry ) const;	// リプレイのエントリを保存
	};
}

#endif