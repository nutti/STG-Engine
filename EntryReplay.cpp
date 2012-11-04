#include "ResourceHandler.h"

#include "EntryReplay.h"
#include "Menu.h"
#include "GeneralButtonManager.h"
#include "FontString.h"

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
			MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_LEFT ) ){
			m_NameEntry.Advance( -1 );
			MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
		}

		// ファイルの選択
		if( !m_Selected ){
			if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
				m_Selected = true;
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
			}
			else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_DOWN ) ){
				++m_FileNo;
				if( m_FileNo >= 25 ){
					m_FileNo = 0;
				}
				MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
			}
			else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_UP ) ){
				--m_FileNo;
				if( m_FileNo <= -1 ){
					m_FileNo = 24;
				}
				MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
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
					MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
				}
				// 一文字消去
				else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
					if( m_NameLen > 0 ){
						m_Name[ m_NameLen - 1 ] = '\0';
						--m_NameLen;
						MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
					}
				}
				else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_BARRIER ) ){
					m_Name[ m_NameLen ] = m_NameEntry.GetCurChar();
					m_Name[ m_NameLen + 1 ] = '\0';
					++m_NameLen;
					MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
				}
			}
			// 15文字を超えた場合は、文字追加を受け付けない。
			else if( m_NameLen == 15 ){
				if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
					char fileName[ 40 ];
					::sprintf( fileName, "replay/entry%d.rpy", m_FileNo );
					SetNextScene( new Menu() );
					MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
				}
				else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
					m_Name[ 14 ] = '\0';
					--m_NameLen;
					MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
				}
			}
		}
	}

	void EntryReplay::Draw()
	{
		// 2D描画開始
		MAPIL::BeginRendering2DGraphics();

		if( !m_Selected ){
			FontString s;
			s.Set( "name" );
			s.Draw( 60.0f, 20.0f, 0xFFAAFFAA );
			s.Set( "progress" );
			s.Draw( 280.0f, 20.0f, 0xFFAAFFAA );
			s.Set( "score" );
			s.Draw( 390.0f, 20.0f, 0xFFAAFFAA );
			s.Set( "date" );
			s.Draw( 500.0f, 20.0f, 0xFFAAFFAA );

			for( int i = 0; i < 25; ++i ){
				int color;

				if( i == m_FileNo ){
					color = 0xFFFFFFFF;
				}
				else{
					color = 0x66666666;
				}

				s.Set( "%02d", i + 1 );
				s.Draw( 20.0f, 50.0f + i * 16.0f, color );

				if( m_Entry[ i ].m_Progress != -1 ){
					s.Set( m_Entry[ i ].m_Name );
					s.Draw( 60.0f, 50.0f + i * 16.0f, color );
					std::string prog;
					if( m_Entry[ i ].m_Progress == STAGE_PROGRESS_STAGE1 ){
						prog = "stage1";
					}
					else if( m_Entry[ i ].m_Progress == STAGE_PROGRESS_COMPLETED ){
						prog = "comp";
					}
					s.Set( prog );
					s.Draw( 280.0f, 50.0f + i * 16.0f, color );
					s.Set( "%d", m_Entry[ i ].m_Score );
					s.Draw( 390.0f, 50.0f + i * 16.0f, color );
					s.Set( "%d%02d%02d", m_Entry[ i ].m_Year, m_Entry[ i ].m_Mon, m_Entry[ i ].m_Day );
					s.Draw( 500.0f, 50.0f + i * 16.0f, color );
				}
				else{
					s.Set( "no data" );
					s.Draw( 60.0f, 50.0f + i * 16.0f, color );
				}
			}
		}
		else{
			std::string prog;
			if( m_Progress == STAGE_PROGRESS_STAGE1 ){
				prog = "stage1";
			}
			else if( m_Progress == STAGE_PROGRESS_COMPLETED ){
				prog = "comp";
			}
			FontString s;
			s.Set( "Save replay data" );
			s.Draw( 60.0f, 100.0f, 0xFFAAFFAA );
			s.Set( m_Name );
			s.Draw( 60.0f, 200.0f );
			s.Set( prog );
			s.Draw( 280.0f, 200.0f );
			s.Set( "%d", m_Score );
			s.Draw( 390.0f, 200.0f );
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
				m_Entry[ i ].m_Progress = -1;
				continue;
			}
			fIn.read( name, sizeof( name ) );
			fIn.read( (char*)( &score ), sizeof( score ) );
			fIn.read( (char*)( &progress ), sizeof( progress ) );
			fIn.read( (char*)( &date ),sizeof( date ) );
			fIn.close();

			::tm* pDate = ::localtime( &date );
			m_Entry[ i ].m_Name = name;
			m_Entry[ i ].m_Score = score;
			m_Entry[ i ].m_Progress = progress;
			m_Entry[ i ].m_Year = pDate->tm_year + 1900;
			m_Entry[ i ].m_Mon = pDate->tm_mon + 1;
			m_Entry[ i ].m_Day = pDate->tm_mday;
			m_Entry[ i ].m_Hour = pDate->tm_hour;
			m_Entry[ i ].m_Min = pDate->tm_min;
			m_Entry[ i ].m_Sec = pDate->tm_sec;
		}
		
	}
}