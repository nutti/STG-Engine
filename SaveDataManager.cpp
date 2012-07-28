#include "Defines.h"

#include "SaveDataManager.h"

#include <time.h>

namespace RTG
{
	SaveDataManager::SaveDataManager( const char* pFileName ) :	m_pFileName( pFileName ),
																m_Updated( false )
	{
		MAPIL::ZeroObject( &m_Configuration, sizeof( m_Configuration ) );
		MAPIL::ZeroObject( &m_Progress, sizeof( m_Progress ) );
		MAPIL::ZeroObject( &m_ScoreHistory, sizeof( m_ScoreHistory ) );
	}

	SaveDataManager::~SaveDataManager()
	{
		m_Updated = false;
		MAPIL::ZeroObject( &m_Configuration, sizeof( m_Configuration ) );
		MAPIL::ZeroObject( &m_Progress, sizeof( m_Progress ) );
		MAPIL::ZeroObject( &m_ScoreHistory, sizeof( m_ScoreHistory ) );
	}

	void SaveDataManager::UpdateScore( const char* pName, int score, int progress )
	{
		int len = strlen( pName );

		for( int i = 0; i < sizeof( m_ScoreHistory.m_Entry ) / sizeof( m_ScoreHistory.m_Entry[ 0 ] ); ++i ){
			// 未使用の場合、すぐに保存
			if( !m_ScoreHistory.m_Entry[ i ].m_Used ){
				strncpy( m_ScoreHistory.m_Entry[ i ].m_Name, pName, len );
				m_ScoreHistory.m_Entry[ i ].m_Name[ len ] = '\0';
				m_ScoreHistory.m_Entry[ i ].m_Score = score;
				m_ScoreHistory.m_Entry[ i ].m_Progress = progress;
				::time( &m_ScoreHistory.m_Entry[ i ].m_Date );
				m_ScoreHistory.m_Entry[ i ].m_Used = true;
				m_Updated = true;
				break;
			}
			// 使用中の場合、スコアの比較をする。
			else{
				// スコアが現在のランクより高い場合
				// それ以降のものをずらす
				if( score >= m_ScoreHistory.m_Entry[ i ].m_Score ){
					// 最終のところを見つける
					int lastEntry = 0;
					for( int j = 0; j < sizeof( m_ScoreHistory.m_Entry ) / sizeof( m_ScoreHistory.m_Entry[ 0 ] ); ++j ){
						if( !m_ScoreHistory.m_Entry[ j ].m_Used ){
							lastEntry = j;
							break;
						}
					}
					// ずらし処理
					for( int j = lastEntry; j >= i; --j ){
						if( lastEntry != sizeof( m_ScoreHistory.m_Entry ) / sizeof( m_ScoreHistory.m_Entry[ 0 ] ) ){
							memcpy( &m_ScoreHistory.m_Entry[ j + 1 ], &m_ScoreHistory.m_Entry[ j ], sizeof( m_ScoreHistory.m_Entry[ 0 ] ) );
						}
					}
					strncpy( m_ScoreHistory.m_Entry[ i ].m_Name, pName, len );
					m_ScoreHistory.m_Entry[ i ].m_Name[ len ] = '\0';
					m_ScoreHistory.m_Entry[ i ].m_Score = score;
					m_ScoreHistory.m_Entry[ i ].m_Progress = progress;
					::time( &m_ScoreHistory.m_Entry[ i ].m_Date );
					m_ScoreHistory.m_Entry[ i ].m_Used = true;
					m_Updated = true;
					break;
				}
			}
 		}
	}

	void SaveDataManager::IncRunCount()
	{
		m_Progress.m_RunCount++;
		m_Updated = true;
	}

	bool SaveDataManager::IsUpdated() const
	{
		return m_Updated ? true : false;
	}

	void SaveDataManager::Save()
	{
		std::ofstream fOut( m_pFileName, std::ios::out | std::ios::binary );

		if( !fOut ){
			return;
		}

		for( int i = 0; i < sizeof( m_ScoreHistory.m_Entry ) / sizeof( m_ScoreHistory.m_Entry[ 0 ] ); ++i ){
			if( m_ScoreHistory.m_Entry[ i ].m_Used ){
				fOut.write( m_ScoreHistory.m_Entry[ i ].m_Name, sizeof( m_ScoreHistory.m_Entry[ i ].m_Name ) );
				fOut.write( reinterpret_cast < char* > ( &m_ScoreHistory.m_Entry[ i ].m_Score ), sizeof( m_ScoreHistory.m_Entry[ i ].m_Score ) );
				fOut.write( reinterpret_cast < char* > ( &m_ScoreHistory.m_Entry[ i ].m_Progress ), sizeof( m_ScoreHistory.m_Entry[ i ].m_Progress ) );
				fOut.write( reinterpret_cast < char* > ( &m_ScoreHistory.m_Entry[ i ].m_Date ), sizeof( m_ScoreHistory.m_Entry[ i ].m_Date ) );
			}
		}

		fOut.close();
	}

	void SaveDataManager::Load()
	{
		std::ifstream fIn( m_pFileName, std::ios::out | std::ios::binary );

		if( !fIn ){
			return;
		}

		int entry = 0;

		while( !fIn.eof() ){
			if( entry >= 32 ){
				break;
			}
			char name[ 16 ];
			int score;
			int progress;
			::time_t date;
			fIn.read( name, sizeof( name ) );
			if( fIn.eof() ){
				break;
			}
			fIn.read( reinterpret_cast < char* > ( &score ), sizeof( score ) );
			fIn.read( reinterpret_cast < char* > ( &progress ), sizeof( progress ) );
			fIn.read( reinterpret_cast < char* > ( &date ), sizeof( date ) );
			strcpy( m_ScoreHistory.m_Entry[ entry ].m_Name, name );
			m_ScoreHistory.m_Entry[ entry ].m_Score = score;
			m_ScoreHistory.m_Entry[ entry ].m_Progress = progress;
			m_ScoreHistory.m_Entry[ entry ].m_Date = date;
			m_ScoreHistory.m_Entry[ entry ].m_Used = true;
			++entry;
		}

		fIn.close();
	}

	ScoreEntry SaveDataManager::GetScoreEntry( int rank ) const
	{
		return m_ScoreHistory.m_Entry[ rank ];
	}
}