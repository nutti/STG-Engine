#ifndef INCLUDED_RTG_LOADING_H
#define INCLUDED_RTG_LOADING_H

#include "Defines.h"
#include <list>

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

	struct IStreamingPair
	{
		MAPIL::IStreamingBuffer		m_Streaming;
		std::basic_string < TCHAR >	m_FileName;
	};

	struct IStaticBufferPair
	{
		MAPIL::IStaticBuffer		m_StaticBuffer;
		std::basic_string < TCHAR >	m_FileName;
	};

	class Loading : public MAPIL::WinAPIThread
	{
	private:
		std::basic_string < TCHAR >		m_ArchiveFileName;
		std::list < IStreamingPair >	m_StreamingList;
		std::list < IStaticBufferPair >	m_StaticBufferList;
		LoadingState					m_LoadingState;

		void LoadStreamingBuffer();
		void LoadStaticBuffer();
	public:
		Loading();
		~Loading();
		void Create();
		void SetArchiver( const TCHAR* pFileName );
		void Start();
		void Stop();
		void Reset();
		void SetContents( MAPIL::IStreamingBuffer c, const TCHAR* pFileName );
		void SetContents( MAPIL::IStaticBuffer c, const TCHAR* pFileName );
		bool IsFinished() const;
		int ThreadFunc();
	};
}

#endif