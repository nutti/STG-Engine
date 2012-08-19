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
		m_Archiver = MAPIL::OpenArchiveFile( "confetti.dat", MAPIL::FILE_OPEN_READ_MODE );
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
		const int INITIAL_SE_MAP_RESERVE_CAP = 50;				// 初期のSEMAP許容量
		const int INITIAL_BGM_MAP_RESERVE_CAP = 50;				// 初期のBGMMAP許容量
		m_ResourceMap.m_TextureMap.resize( INITIAL_TEXTURE_MAP_RESERVE_CAP, -1 );
		m_ResourceMap.m_SEMap.resize( INITIAL_SE_MAP_RESERVE_CAP, -1 );
		m_ResourceMap.m_BGMMap.resize( INITIAL_BGM_MAP_RESERVE_CAP, -1 );
		m_ResourceScriptData = m_pCompiler->GetResourceScriptData();
		// テクスチャの読み込み
		typedef std::map < int, std::string > ::iterator	TextureIter;
		for(	TextureIter it = m_ResourceScriptData.m_TextureList.begin();
				it != m_ResourceScriptData.m_TextureList.end();
				++it ){
			// 許容値を超えたインデックスが必要な場合は、指定されたインデックスの2倍のサイズのresizeする。
			if( it->first > m_ResourceMap.m_TextureMap.size() ){
				m_ResourceMap.m_TextureMap.resize( it->first * 2 );
			}
			m_ResourceMap.m_TextureMap[ it->first ] = MAPIL::CreateTexture( m_Archiver, it->second.c_str() );
		}
		// SEの読み込み
		typedef std::map < int, std::string > ::iterator	SEIter;
		for(	SEIter it = m_ResourceScriptData.m_SEList.begin();
				it != m_ResourceScriptData.m_SEList.end();
				++it ){
			if( it->first > m_ResourceMap.m_SEMap.size() ){
				m_ResourceMap.m_SEMap.resize( it->first * 2 );
			}
			int id = MAPIL::CreateStaticBuffer( m_Archiver, it->second.c_str() );
			MAPIL::SetStaticBufferVolume( id, ResourceHandler::GetInst()->m_pGameManager->GetSEVolume() );
			m_ResourceMap.m_SEMap[ it->first ] = id;
		}
		// BGMの読み込み
		typedef std::map < int, std::string > ::iterator	BGMIter;
		for(	BGMIter it = m_ResourceScriptData.m_BGMList.begin();
				it != m_ResourceScriptData.m_BGMList.end();
				++it ){
			if( it->first > m_ResourceMap.m_BGMMap.size() ){
				m_ResourceMap.m_BGMMap.resize( it->first * 2 );
			}
			int id = MAPIL::CreateStreamingBuffer( m_Archiver, it->second.c_str() );
			MAPIL::SetStreamingBufferVolume( id, ResourceHandler::GetInst()->m_pGameManager->GetBGMVolume() );
			m_ResourceMap.m_BGMMap[ it->first ] = id;
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

	void ResourceHandler::ReleaseAllStageResources()
	{
		// ステージに対して読み込まれたテクスチャの解放
		for( int i = 0; i < m_ResourceMap.m_TextureMap.size(); ++i ){
			if( m_ResourceMap.m_TextureMap[ i ] != -1 ){
				MAPIL::DeleteTexture( m_ResourceMap.m_TextureMap[ i ] );
			}
		}
		m_ResourceMap.m_TextureMap.clear();
		// ステージに対して読み込まれたBGMの解放
		for( int i = 0; i < m_ResourceMap.m_BGMMap.size(); ++i ){
			if( m_ResourceMap.m_BGMMap[ i ] != -1 ){
				MAPIL::DeleteStreamingBuffer( m_ResourceMap.m_BGMMap[ i ] );
			}
		}
		m_ResourceMap.m_BGMMap.clear();
		// ステージに対して読み込まれたSEの解放
		for( int i = 0; i < m_ResourceMap.m_SEMap.size(); ++i ){
			if( m_ResourceMap.m_SEMap[ i ] != -1 ){
				MAPIL::DeleteStaticBuffer( m_ResourceMap.m_SEMap[ i ] );
			}
		}
		m_ResourceMap.m_SEMap.clear();
	}


}