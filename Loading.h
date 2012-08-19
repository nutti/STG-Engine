#ifndef INCLUDED_RTG_LOADING_H
#define INCLUDED_RTG_LOADING_H

#include "Defines.h"
#include <list>

#include "StageVCPU.h"

namespace RTG
{
	enum LoadingState
	{
		LOADING_STATE_IDLE	= 0,
		LOADING_STATE_LOAD	= 1,
		LOADING_STATE_COMP	= 2,
		LOADING_STATE_STOP	= 3,
		LOADING_STATE_TERM	= 4,
	};

	class Loading : public MAPIL::WinAPIThread
	{
	private:
		LoadingState	m_LoadingState;
		int				m_Scene;
		StageVCPU*		m_pStageVCPU;
		VM::Data**		m_ppScriptCmd;
		StageInfo*		m_pStageInfo;
	public:
		Loading();
		~Loading();
		void Create();
		void SetScriptData( const char* pFileName );
		void Start();
		void Stop();
		void Reset();
		bool IsFinished() const;
		void SetScene( int scene, StageVCPU* pStageVCPU, VM::Data** ppScriptCmd, StageInfo* pStageInfo );
		int ThreadFunc();
	};
}

#endif