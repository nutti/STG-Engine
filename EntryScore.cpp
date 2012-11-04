#include "ResourceHandler.h"

#include "EntryScore.h"
#include "EntryReplay.h"
#include "Menu.h"
#include "GeneralButtonManager.h"
#include "FontString.h"

namespace RTG
{
	EntryScore::EntryScore( int score, int progress ) :	m_Score( score ),
														m_NameLen( 0 ),
														m_Date( 0 ),
														m_Progress( progress ),
														m_NameEntry()
	{
		MAPIL::ZeroObject( m_Name, sizeof( m_Name ) );
	}

	EntryScore::~EntryScore()
	{
		MAPIL::ZeroObject( m_Name, sizeof( m_Name ) );
		m_NameLen = 0;
		m_Date = 0;
		m_Progress = 0;
	}

	bool EntryScore::IsLoading() const
	{
		return false;
	}

	void EntryScore::Update()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_RIGHT ) ){
			m_NameEntry.Advance( 1 );
			MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_LEFT ) ){
			m_NameEntry.Advance( -1 );
			MAPIL::PlayStaticBuffer( p->m_MenuMoveSE );
		}

		// 名前入力
		if( m_NameLen <= 14 ){
			// キャラクター名決定
			if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
				p->m_pSaveDataManager->UpdateScore( m_Name, m_Score, m_Progress );
				if( p->m_pSaveDataManager->IsUpdated() ){
					p->m_pSaveDataManager->Save();
				}
				SetNextScene( new EntryReplay( m_Score, m_Progress ) );
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
		else if( m_NameLen == 15 ){
			if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
				p->m_pSaveDataManager->UpdateScore( m_Name, m_Score, m_Progress );
				if( p->m_pSaveDataManager->IsUpdated() ){
					p->m_pSaveDataManager->Save();
				}
				SetNextScene( new EntryReplay( m_Score, m_Progress ) );
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
			}
			else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
				m_Name[ 14 ] = '\0';
				--m_NameLen;
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
			}
		}
	}

	void EntryScore::Draw()
	{
		// 2D描画開始
		MAPIL::BeginRendering2DGraphics();

		// 進捗状況の表示
		std::string prog;
		if( m_Progress == STAGE_PROGRESS_STAGE1 ){
			prog = "stage1";
		}
		else if( m_Progress == STAGE_PROGRESS_COMPLETED ){
			prog = "comp";
		}
		FontString s;
		s.Set( "Entry score name" );
		s.Draw( 60.0f, 100.0f, 0xFFAAFFAA );
		s.Set( m_Name );
		s.Draw( 60.0f, 200.0f );
		s.Set( prog );
		s.Draw( 280.0f, 200.0f );
		s.Set( "%d", m_Score );
		s.Draw( 390.0f, 200.0f );


		// 2D描画終了
		MAPIL::EndRendering2DGraphics();
	}

	void EntryScore::Init()
	{
		// 削除済みのリソースを完全消去
		MAPIL::RefleshResources();

		m_NameEntry.SetEffectiveChar( GetEffectiveChar() );
	}
}