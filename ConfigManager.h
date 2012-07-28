#ifndef INCLUDED_RTG_CONFIGMANAGER_H
#define INCLUDED_RTG_CONFIGMANAGER_H

#include "GeneralButtonManager.h"

namespace RTG
{
	class ConfigManager
	{
	private:
		// ウィンドウ関連
		char				m_IsWndMode;							// ウィンドウモードか
		int					m_Width;								// ウィンドウの幅
		int					m_Height;								// ウィンドウの高さ
		// ボタン配置関連
		unsigned short		m_ButtonMaps[ GENERAL_BUTTON_TOTAL ];	// 各ボタンの割り当て
		// サウンド関連
		int					m_SEVolume;			// SEのボリューム
		int					m_BGMVolume;		// BGMのボリューム
	public:
		ConfigManager();
		~ConfigManager();
		void Load( const char* pFileName );						// コンフィグファイルの読み込み
		void Save( const char* pFileName );						// コンフィグファイルへの書き込み
		char IsWndMode() const;									// ウィンドウモードかどうか
		void SetWndMode( char wndMode );						// ウィンドウモード
		int GetWidth() const;									// ウィンドウの幅を取得
		void SetWidth( int width );								// ウィンドウの幅を設定
		int GetHeight() const;									// ウィンドウの高さを取得
		void SetHeight( int height );							// ウィンドウの高さを設定
		void GetButtonMaps( unsigned short* pButtonMap ) const;	// 各ボタンの割り当てを取得
		void SetButtonMaps( unsigned short* pButtonMap );		// 各ボタンの割り当てを設定
		int GetSEVolume() const;								// SEのボリュームを取得
		void SetSEVolume( int volume );							// SEのボリュームを設定
		int GetBGMVolume() const;								// BGMのボリュームを取得
		void SetBGMVolume( int volume );						// BGMのボリュームを設定
	};
}

#endif