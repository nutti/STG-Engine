#include "Loading.h"
#include <MAPIL/IO/Archiver.h>

#include "ResourceHandler.h"


namespace RTG
{
	Loading::Loading() :	MAPIL::WinAPIThread(),
							m_LoadingState( LOADING_STATE_IDLE ),
							m_Scene( -1 ),
							m_ppScriptCmd( NULL ),
							m_pStageVCPU( NULL ),
							m_pStageInfo( NULL )
	{
	}

	Loading::~Loading()
	{
		m_LoadingState = LOADING_STATE_TERM;
		m_Scene = -1;
	}

	void Loading::Create()
	{
		Reset();
		WinAPIThread::Create();
	}

	void Loading::Start()
	{
		m_LoadingState = LOADING_STATE_LOAD;
	}

	void Loading::Stop()
	{
		m_LoadingState = LOADING_STATE_STOP;
	}

	void Loading::Reset()
	{
		m_LoadingState = LOADING_STATE_IDLE;
	}

	bool Loading::IsFinished() const
	{
		return m_LoadingState == LOADING_STATE_COMP ? true : false;
	}

	int Loading::ThreadFunc()
	{
		while( m_LoadingState != LOADING_STATE_TERM ){
			if(	m_LoadingState == LOADING_STATE_STOP ||
				m_LoadingState == LOADING_STATE_COMP ||
				m_LoadingState == LOADING_STATE_IDLE ){
				Sleep( 1 );
			}
			else if( m_LoadingState == LOADING_STATE_LOAD ){
				ResourceHandler* p = ResourceHandler::GetInst();
				//p->m_pCompiler->Compile( m_Scene );
				p->m_pCompiler->Load( p->m_Archiver, m_Scene );
				p->SetupHandle();
				*m_ppScriptCmd = p->m_pCompiler->GetStageScript();
				m_pStageVCPU->Init( *m_ppScriptCmd, m_pStageInfo );
				m_LoadingState = LOADING_STATE_COMP;
			}
		}

		return 0;
	}

	void Loading::SetScene( int scene, StageVCPU* pStageVCPU, VM::Data** ppScriptCmd, StageInfo* pStageInfo )
	{
		m_Scene = scene;
		m_pStageVCPU = pStageVCPU;
		m_ppScriptCmd = ppScriptCmd;
		m_pStageInfo = pStageInfo;
	}
}