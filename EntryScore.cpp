#include "ResourceHandler.h"

#include "EntryScore.h"
#include "EntryReplay.h"
#include "Menu.h"
#include "GeneralButtonManager.h"

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
		}
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_LEFT ) ){
			m_NameEntry.Advance( -1 );
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
		else if( m_NameLen == 15 ){
			if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
				p->m_pSaveDataManager->UpdateScore( m_Name, m_Score, m_Progress );
				if( p->m_pSaveDataManager->IsUpdated() ){
					p->m_pSaveDataManager->Save();
				}
				SetNextScene( new EntryReplay( m_Score, m_Progress ) );
			}
			else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
				m_Name[ 14 ] = '\0';
				--m_NameLen;
			}
		}
	}

	void EntryScore::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		// 2D描画開始
		p->BeginDraw2D();

		// 進捗状況の表示
		char str[ 160 ];
		char progStr[ 40 ];
		if( m_Progress == STAGE_PROGRESS_STAGE1 ){
			strcpy( progStr, "Stage 1" );
		}
		else if( m_Progress == STAGE_PROGRESS_COMPLETED ){
			strcpy( progStr, "Complete" );
		}
		sprintf( str, "Name : %s Score : %d Progress : %s", m_Name, m_Score, progStr );
		p->DrawString2D( 100.0f, 100.0f, 0xFFFFFFFF, str );

		// 2D描画終了
		p->EndDraw2D();
	}

	void EntryScore::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		// 削除済みのリソースを完全消去
		p->RefleshResouces();

		m_NameEntry.SetEffectiveChar( GetEffectiveChar() );
	}
}