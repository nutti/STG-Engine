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

	void ResourceHandler::SetupHandle()
	{
		// 各種リソースの読み込み
		const int INITIAL_TEXTURE_MAP_RESERVE_CAP = 50;			// 初期のテクスチャMAP許容量
		m_ResourceMap.m_TextureMap.resize( INITIAL_TEXTURE_MAP_RESERVE_CAP );
		m_ResourceScriptData = m_pCompiler->GetResourceScriptData();
		// テクスチャの読み込み
		typedef std::map < int, std::string > ::iterator	TextureIter;
		TextureIter it = m_ResourceScriptData.m_TextureList.begin();
		for( ; it != m_ResourceScriptData.m_TextureList.end(); ++it ){
			// 許容値を超えたインデックスが必要な場合は、指定されたインデックスの2倍のサイズのresizeする。
			if( it->first > m_ResourceMap.m_TextureMap.size() ){
				m_ResourceMap.m_TextureMap.resize( it->first * 2 );
			}
			m_ResourceMap.m_TextureMap[ it->first ] = MAPIL::CreateTexture( it->second.c_str() );
		}
	}

	int ResourceHandler::GetTextureHandle( int index )
	{
		return m_ResourceMap.m_TextureMap[ index ];
	}

	int ResourceHandler::GetBGMHandle( int index )
	{
		return m_ResourceMap.m_BGMMap[ index ];
	}

	int ResourceHandler::GetSEHandle( int index )
	{
		return m_ResourceMap.m_SEMap[ index ];
	}


	
	//float ResourceHandler::GetPlayerPositionY( int index )
	//{
	//	CirclePlayerList::Iterator it( &m_PlayerList );
	//	CirclePlayerList::Iterator itEnd( &m_PlayerList );
	//	itEnd.End();

	//	int cnt = 0;

	//	// プレイヤーの情報の更新
	//	for( it.Begin(); it != itEnd; ++itEnd ){
	//		if( cnt == index ){
	//			return ( *it ).GetPos().m_Y;
	//		}
	//		++cnt;
	//	}

	//	return 0.0f;		// 目的のプレイヤーは見つからなかった。
	//}
}