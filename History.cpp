#include "ResourceHandler.h"

#include "History.h"
#include "Menu.h"
#include "GeneralButtonManager.h"

#include <time.h>

namespace RTG
{
	History::History()
	{
	}

	History::~History()
	{
	}

	bool History::IsLoading() const
	{
		return false;
	}

	void History::Update()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
			SetNextScene( new Menu() );
		}
	}

	void History::Draw()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		// 2D•`‰æŠJŽn
		p->BeginDraw2D();

		for( int i = 0; i < 32; ++i ){
			char strBase[ 160 ];
			ScoreEntry se = p->m_pSaveDataManager->GetScoreEntry( i );
			if( se.m_Used ){
				int score = se.m_Score;
				char progStr[ 40 ];
				if( se.m_Progress == STAGE_PROGRESS_STAGE1 ){
					sprintf( progStr, "Stage 1" );
				}
				else if( se.m_Progress == STAGE_PROGRESS_COMPLETED ){
					sprintf( progStr, "Complete" );
				}
				::tm* pDate = ::localtime( &se.m_Date );
				sprintf( strBase, "%s , %s : %d %04d/%02d/%02d %02d:%02d:%02d", se.m_Name, progStr, se.m_Score,
					pDate->tm_year + 1900, pDate->tm_mon + 1, pDate->tm_mday, pDate->tm_hour, pDate->tm_min, pDate->tm_sec );
				p->DrawString2D( 200.0f, 10.0f + i * 16.0f, 0xFFFFFFFF, strBase );
			}
		}
		
		// 2D•`‰æI—¹
		p->EndDraw2D();
	}

	void History::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		p->RefleshResouces();
	}
}