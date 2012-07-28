#include "ResourceHandler.h"
#include "Util.h"

#include "GameManager.h"


namespace RTG
{
	ResourceHandler::ResourceHandler() :	m_Cons(),
											m_Alloc(),
											m_pSaveDataManager( NULL ),
											m_pGBManager( NULL ),
											m_pReplayEntry( NULL ),
											m_pGameManager( NULL )
	{
	}

	ResourceHandler::~ResourceHandler()
	{
		MAPIL::SafeDelete( m_pScore );
		MAPIL::SafeDelete( m_pSaveDataManager );
		MAPIL::SafeDelete( m_pReplayEntry );
		MAPIL::SafeDelete( m_pGameManager );
	}


	void* ResourceHandler::AllocMemory()			// メモリの割り当て
	{
		return m_Alloc.Alloc();
	}

	void ResourceHandler::ReleaseMemory( void* p )			// メモリの開放
	{
		m_Alloc.Delete( p );
	}
}