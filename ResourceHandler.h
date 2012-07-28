#ifndef INCLUDED_RTG_RESOURCEHANDLER_H
#define INCLUDED_RTG_RESOURCEHANDLER_H

#include "Defines.h"

#include "Score.h"
#include "SaveDataManager.h"
#include "ReplaySaver.h"

namespace RTG
{
	struct RandomSeed
	{
		int		m_PosX;
		int		m_PosY;
		int		m_Score;
		int		m_HitTotal;
		int		m_ReflectTotal;
		int		m_Frame;
	};

	class GeneralButtonManager;
	struct ReplayEntry;
	class GameManager;
	class ScriptCompiler;
	class ResourceHandler : public MAPIL::Singleton < ResourceHandler >
	{
	private:
		// デバッグ関連
		MAPIL::Console						m_Cons;		// コンソールデバイス

		// デバイス・ファクトリ関連
		MAPIL::IGUIDevice					m_GUIDev;				// GUIデバイス
		MAPIL::GUIFactory*					m_pGUIFactory;			// GUIファクトリ
		MAPIL::IGraphicsDevice				m_GraphicsDev;			// グラフィックスデバイス
		//MAPIL::GraphicsFactory*				m_pGraphicsFactory;		// グラフィックスファクトリ
		MAPIL::IInputDevice					m_InputDev;				// 入力デバイス
		MAPIL::InputFactory*				m_pInputFactory;		// 入力ファクトリ
		MAPIL::ISoundDevice					m_SoundDev;				// サウンドデバイス
		//MAPIL::SoundFactory*				m_pSoundFactory;		// サウンドファクトリ
	
		// グローバルリソース関連
		MAPIL::TTFFile*						m_FontFile;				// フォントファイル

		// メモリ関連
		MAPIL::Allocator < 3000, 4000 >		m_Alloc;				// アロケータ
	public:
		friend class MAPIL::Singleton < ResourceHandler >;

		MAPIL::GraphicsFactory*				m_pGraphicsFactory;		// グラフィックスファクトリ
		MAPIL::SoundFactory*				m_pSoundFactory;		// サウンドファクトリ

		// ウィンドウ関連
		MAPIL::IWindow						m_MainWnd;				// ウィンドウオブジェクト
		MAPIL::IGraphicsContext				m_GLContext;			// グラフィックスコンテキスト

		
		MAPIL::IStaticBuffer				m_StaticBuf[ 40 ];
		MAPIL::IStreamingBuffer				m_StreamingBuf;

		
		MAPIL::IGraphicsController			m_GraphicsCtrl;
		MAPIL::ICamera						m_Camera3D;
		MAPIL::ICamera						m_Camera;
		MAPIL::ICanvas2D					m_Canvas;
		MAPIL::ISprite						m_Sprite;
		MAPIL::IGraphicsFont				m_Font;

		MAPIL::ITexture						m_Texture[ 50 ];

		MAPIL::IRectangle3D					m_Rectangle[ 50 ];
		MAPIL::IPointSprite					m_PointSprite;

		

		MAPIL::IKeyboard					m_Keyboard;

		Score*								m_pScore;

		SaveDataManager*					m_pSaveDataManager;

		GeneralButtonManager*				m_pGBManager;
		ReplayEntry*						m_pReplayEntry;
		ReplaySaver*						m_pReplaySaver;
		GameManager*						m_pGameManager;

		ScriptCompiler*						m_pCompiler;

		RandomSeed							m_RdmSeed;

		ResourceHandler();
		~ResourceHandler();
		
		void Init();
		void SetupGlobalResources();				// グローバルなリソースのセットアップ
		MAPIL::ISprite CreateSpriteL( const char* pStr );
		MAPIL::IGraphicsFont CreateFontL( const char* pStr );
		void BeginDraw2D();
		void EndDraw2D();
		void DrawString2D( float x, float y, const char* pStr );
		void DrawString2D( float x, float y, int color, const char* pStr, ... );
		void RefleshResouces();
		void* AllocMemory();					// メモリの割り当て
		void ReleaseMemory( void* p );			// メモリの開放
	};
}

#endif