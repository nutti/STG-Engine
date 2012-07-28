#include "Loading.h"
#include <MAPIL/IO/Archiver.h>


namespace RTG
{
	Loading::Loading() :	MAPIL::WinAPIThread(),
							m_StreamingList(),
							m_StaticBufferList(),
							m_LoadingState( LOADING_STATE_IDLE )
	{
		m_StreamingList.clear();
		m_StaticBufferList.clear();
	}

	Loading::~Loading()
	{
		m_LoadingState = LOADING_STATE_TERM;
		m_StreamingList.clear();
		m_StaticBufferList.clear();
	}

	void Loading::SetArchiver( const TCHAR* pFileName )
	{
		m_ArchiveFileName = pFileName;
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
		m_StreamingList.clear();
		m_StaticBufferList.clear();
	}

	void Loading::SetContents( MAPIL::IStreamingBuffer c, const TCHAR* pFileName )
	{
		IStreamingPair pair;

		pair.m_Streaming = c;
		pair.m_FileName = pFileName;

		m_StreamingList.push_back( pair );
	}

	void Loading::SetContents( MAPIL::IStaticBuffer c, const TCHAR* pFileName )
	{
		IStaticBufferPair pair;

		pair.m_StaticBuffer = c;
		pair.m_FileName = pFileName;

		m_StaticBufferList.push_back( pair );
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
				LoadStreamingBuffer();
				LoadStaticBuffer();
				m_LoadingState = LOADING_STATE_COMP;
			}
		}

		return 0;
	}

	void Loading::LoadStreamingBuffer()
	{
		std::list < IStreamingPair > ::iterator it = m_StreamingList.begin();
		for( ; it != m_StreamingList.end(); ++it ){
			( *it ).m_Streaming->Create( m_ArchiveFileName.c_str(), ( *it ).m_FileName.c_str() );
		}
	}

	void Loading::LoadStaticBuffer()
	{
		MAPIL::Archiver* p = new MAPIL::Archiver();
		char name[ 1024 ];
		MAPIL::ConvertToMultiByte( m_ArchiveFileName.c_str(), -1, name, 1024 );

		p->Open( name, MAPIL::FILE_OPEN_READ_MODE );

		std::list < IStaticBufferPair > ::iterator it = m_StaticBufferList.begin();
		for( ; it != m_StaticBufferList.end(); ++it ){
			( *it ).m_StaticBuffer->Create( p, ( *it ).m_FileName.c_str() );
		}

		MAPIL::SafeDelete( p );
	}
}