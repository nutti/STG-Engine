#ifndef INCLUDED_RTG_GENERALBUTTONMANAGER_H
#define INCLUDED_RTG_GENERALBUTTONMANAGER_H

#include "Defines.h"
#include "Keyboard.h"
#include "ReplayLoader.h"

namespace RTG
{
	enum GeneralButton
	{
		GENERAL_BUTTON_UP		= 0,		// 上
		GENERAL_BUTTON_DOWN		= 1,		// 下
		GENERAL_BUTTON_RIGHT	= 2,		// 右
		GENERAL_BUTTON_LEFT		= 3,		// 左
		GENERAL_BUTTON_BARRIER	= 4,		// バリア（決定ボタン）
		GENERAL_BUTTON_ROT_CW	= 5,		// 時計回り回転
		GENERAL_BUTTON_ROT_CCW	= 6,		// 反時計周り回転

		GENERAL_BUTTON_CANCEL	= 7,		// キャンセルボタン
		GENERAL_BUTTON_SS		= 8,		// スクリーンショット
		GENERAL_BUTTON_PAUSE	= 9,		// ポーズボタン
		GENERAL_BUTTON_TERM		= 10,		// 強制終了
		GENERAL_BUTTON_ENTER	= 11,		// 決定ボタン
	};

	enum InputDevice
	{
		INPUT_DEVICE_KEYBOARD	= 0,		// キーボード
		INPUT_DEVICE_MOUSE		= 1,		// マウス
		INPUT_DEVICE_GAMEPAD	= 2,		// ゲームパッド
		INPUT_DEVICE_REPLAY		= 3,		// リプレイ数
	};

	const int GENERAL_BUTTON_TOTAL = 12;	// ボタン数
	const int INPUT_DEVICE_TOTAL = 4;		// デバイスの種類数


	class GeneralButtonManager
	{
	private:
		unsigned short		m_ButtonMaps[ GENERAL_BUTTON_TOTAL ];		// ボタンマップ（割り当ての状態を保持）、上位1byte->デバイス、下位1byte->ボタン
		bool				m_IsPushedOnce[ GENERAL_BUTTON_TOTAL ];		// ボタンは現在押されているか？
		bool				m_IsPushed[ GENERAL_BUTTON_TOTAL ];			// ボタンは前回も押されていたか？
		Keyboard*			m_pKeyboard;
		ReplayEntry*		m_pReplay;
		int					m_CurFrame;					// 現在のフレーム

		int	 repmode;
	public:
		GeneralButtonManager();
		~GeneralButtonManager();
		void Init( ReplayEntry* pReplayEntry );
		void Assign( int button, int dev, int devButton );
		int GetAssignedDev( int button );
		int GetAssignedDevButton( int button );
		void Update();
		void SetReplay( int set );
		bool IsPushedOnce( GeneralButton button ) const;
		bool IsPushed( GeneralButton button ) const;
		void Reset();
		void CopyCurState( char* pPushed ) const;
	};
}

#endif