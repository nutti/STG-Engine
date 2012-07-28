#include "ResourceHandler.h"

#include "EntryReplay.h"
#include "Menu.h"
#include "GeneralButtonManager.h"

#include <sstream>
#include <time.h>

namespace RTG
{
	EntryReplay::EntryReplay( int score, int progress ) :	m_Score( score ),
															m_NameLen( 0 ),
															m_Date( 0 ),
															m_Progress( progress ),
															m_FileNo( 0 ),
															m_Selected( false ),
															m_NameEntry()
	{
		MAPIL::ZeroObject( m_Name, sizeof( m_Name ) );
	}

	EntryReplay::~EntryReplay()
	{
		MAPIL::ZeroObject( m_Name, sizeof( m_Name ) );
		m_NameLen = 0;
		m_Date = 0;
		m_Progress = 0;
		m_FileNo = 0;
		m_Selected = false;
	}

	bool EntryReplay::IsLoading() const
	{
		return false;
	}

	void EntryReplay::Update()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		// 入力文字の変更
		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_RIGHT ) ){
			m_NameEntry.Advance( 1 );
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_LEFT ) ){
			m_NameEntry.Advance( -1 );
		}

		// ファイルの選択
		if( !m_Selected ){
			if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
				m_Selected = true;
			}
			else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_DOWN ) ){
				++m_FileNo;
				if( m_FileNo >= 25 ){
					m_FileNo = 0;
				}
			}
			else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_UP ) ){
				--m_FileNo;
				if( m_FileNo <= -1 ){
					m_FileNo = 24;
				}
			}
		}
		else{
			// 名前入力
			if( m_NameLen <= 14 ){
				// キャラクター名決定
				if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
					char fileName[ 40 ];
					::sprintf( fileName, "replay/entry%d.rpy", m_FileNo );
					p->m_pReplaySaver->Save( fileName, m_Name, m_Score, m_Progress );
					SetNextScene( new Menu() );
				}
				// 一文字消去
				else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
					if( m_NameLen > 0 ){
						m_Name[ m_NameLen - 1 ] = '\0';
						--m_NameLen;
					}
				}
				else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_BARRIER ) ){
					m_Name[ m_NameLen ] = m_NameEntry.GetCurChar();
					m_Name[ m_NameLen + 1 ] = '\0';
					++m_NameLen;
				}
			}
			// 15文字を超えた場合は、文字追加を受け付けない。
			else if( m_NameLen == 15 ){
				if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
					char fileName[ 40 ];
					::sprintf( fileName, "replay/entry%d.rpy", m_FileNo );
					SetNextScene( new Menu() );
				}
				else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
					m_Name[ 14 ] = '\0';
					--m_NameLen;
				}
			}
		}
	}

	void EntryReplay::Draw()
	{
		// 2D描画開始
		MAPIL::BeginRendering2DGraphics();

		if( !m_Selected ){
			for( int i = 0; i < 25; ++i ){
				// 選択されているファイル情報を強調
				if( i == m_FileNo ){
					MAPIL::DrawString( 100.0f, 50.0f + i * 15.0f, 0xFFFFFFFF, m_EntryStr[ i ] );
				}
				// 選択されていないファイル情報
				else{
					MAPIL::DrawString( 100.0f, 50.0f + i * 15.0f, 0x66666666, m_EntryStr[ i ] );
				}
			}
		}
		else{
			char str[ 256 ];
			char progStr[ 40 ];

			// 進捗状況を表示
			if( m_Progress == STAGE_PROGRESS_STAGE1 ){
				strcpy( progStr, "Stage 1" );
			}
			else if( m_Progress == STAGE_PROGRESS_COMPLETED ){
				strcpy( progStr, "Complete" );
			}
			sprintf( str, "Name : %s Score : %d Progress : %s", m_Name, m_Score, progStr );
			MAPIL::DrawString( 100.0f, 100.0f, 0xFFFFFFFF, str );
		}
		
		// 2D描画終了
		MAPIL::EndRendering2DGraphics();
	}

	void EntryReplay::Init()
	{
		// 削除済みのリソースを完全消去
		MAPIL::RefleshResources();

		m_NameEntry.SetEffectiveChar( GetEffectiveChar() );

		// リプレイデータ一覧を表示
		char fileName[ 256 ];
		for( int i = 0; i < 25; ++i ){
			sprintf( fileName, "replay/entry%d.rpy", i );
			char name[ 16 ];
			int score;
			int progress;
			::time_t date;
			std::ifstream fIn( fileName, std::ios::binary | std::ios::in );
			if( !fIn ){
				sprintf( m_EntryStr[ i ], "------------------No Data------------------" );
				continue;
			}
			fIn.read( name, sizeof( name ) );
			fIn.read( (char*)( &score ), sizeof( score ) );
			fIn.read( (char*)( &progress ), sizeof( progress ) );
			fIn.read( (char*)( &date ),sizeof( date ) );
			fIn.close();

			::tm* pDate = ::localtime( &date );
			sprintf(	m_EntryStr[ i ],
						"No.%d -- %s , %d : %d %04d/%02d/%02d %02d:%02d:%02d",
						i,
						name,
						score,
						progress,
						pDate->tm_year + 1900, pDate->tm_mon + 1, pDate->tm_mday, pDate->tm_hour, pDate->tm_min, pDate->tm_sec );
		}
		
	}
}