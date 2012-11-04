#include "Defines.h"

#include "ReplayLoader.h"

#include <time.h>

#include <MAPIL/Algorithm/LZ.h>
#include <MAPIL/Algorithm/Caesar.h>
#include <MAPIL/Algorithm/XOR.h>

namespace RTG
{
	ReplayLoader::ReplayLoader() : m_EntryTotal( 0 )
	{
		MAPIL::ZeroObject( &m_Entry, sizeof( m_Entry ) );
	}

	ReplayLoader::~ReplayLoader()
	{
		MAPIL::ZeroObject( &m_Entry, sizeof( m_Entry ) );
		m_EntryTotal = 0;
	}

	int ReplayLoader::Load( const char* pFileName )
	{
		std::ifstream fIn( pFileName, std::ios::binary | std::ios::in );

		if( !fIn ){
			return -1;
		}

		// 各種情報読み込み
		fIn.read( m_Name, sizeof( m_Name ) );
		fIn.read( (char*)( &m_Score ), sizeof( m_Score ) );
		fIn.read( (char*)( &m_Progress ), sizeof( m_Progress ) );
		fIn.read( (char*)( &m_Date ),sizeof( m_Date ) );

		int realSize = 0;		// 圧縮前のサイズ
		int compSize = 0;		// 圧縮後のサイズ

		// データ読み込み
		fIn.read( (char*)( &compSize ), sizeof( compSize ) );
		char* pComp = new char [ compSize ];	// 圧縮後のデータ
		fIn.read( pComp, compSize );
		fIn.close();

		// 暗号解読
		MAPIL::XOR xor( 10 );				// XOR暗号
		xor.Decrypt( pComp, compSize );
		MAPIL::Caesar cs( 3 );				// シーザー暗号
		cs.Decrypt( pComp, compSize );

		// 解凍
		char* pRaw = new char [ MAXIMUM_HISTORY_ENTRY * REPLAY_BUTTON_TOTAL * 2 ];	// 圧縮前のデータ
		MAPIL::LZ lz( 200, 3 );
		lz.Expand( pComp, compSize, &pRaw, MAXIMUM_HISTORY_ENTRY * REPLAY_BUTTON_TOTAL * 2, &realSize );

		::memcpy( m_Entry.m_Histories, pRaw, MAXIMUM_HISTORY_ENTRY * REPLAY_BUTTON_TOTAL );

		MAPIL::SafeDeleteArray( pComp );
		MAPIL::SafeDeleteArray( pRaw );

		return 0;
	}

	void ReplayLoader::Open( const char* pFileName )
	{
		std::ifstream fIn( pFileName, std::ios::binary | std::ios::in );

		if( !fIn ){
			m_Score = -1;
			return;
		}

		fIn.read( m_Name, sizeof( m_Name ) );
		fIn.read( (char*)( &m_Score ), sizeof( m_Score ) );
		fIn.read( (char*)( &m_Progress ), sizeof( m_Progress ) );
		fIn.read( (char*)( &m_Date ),sizeof( m_Date ) );

		fIn.close();
	}

	const char* ReplayLoader::GetName() const
	{
		return m_Name;
	}

	int ReplayLoader::GetScore() const
	{
		return m_Score;
	}

	int ReplayLoader::GetProgress() const
	{
		return m_Progress;
	}

	::time_t ReplayLoader::GetDate() const
	{
		return m_Date;
	}

	void ReplayLoader::GetReplayData( ReplayEntry* pEntry ) const
	{
		*pEntry = m_Entry;
	}

}