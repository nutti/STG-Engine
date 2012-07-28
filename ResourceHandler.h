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

		// メモリ関連
		MAPIL::Allocator < 3000, 4000 >		m_Alloc;				// アロケータ
	public:
		friend class MAPIL::Singleton < ResourceHandler >;

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
	
		void* AllocMemory();					// メモリの割り当て
		void ReleaseMemory( void* p );			// メモリの開放
	};
}

#endif