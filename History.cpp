#include "ResourceHandler.h"

#include "History.h"
#include "Menu.h"
#include "GeneralButtonManager.h"
#include "FontString.h"

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

		// 2Dï`âÊäJén
		MAPIL::BeginRendering2DGraphics();

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
			ScoreEntry se = p->m_pSaveDataManager->GetScoreEntry( i );
			if( se.m_Used ){
				int score = se.m_Score;
				char progStr[ 40 ];
				if( se.m_Progress == STAGE_PROGRESS_STAGE1 ){
					sprintf( progStr, "Stage1" );
				}
				else if( se.m_Progress == STAGE_PROGRESS_COMPLETED ){
					sprintf( progStr, "Comp" );
				}
				::tm* pDate = ::localtime( &se.m_Date );
				s.Set( "%02d", i + 1 );
				s.Draw( 20.0f, 50.0f + i * 16.0f );
				s.Set( se.m_Name );
				s.Draw( 60.0f, 50.0f + i * 16.0f );
				s.Set( progStr );
				s.Draw( 280.0f, 50.0f + i * 16.0f );
				s.Set( "%d", se.m_Score );
				s.Draw( 390.0f, 50.0f + i * 16.0f );
				s.Set( "%d%02d%02d", pDate->tm_year + 1900, pDate->tm_mon + 1, pDate->tm_mday );
				s.Draw( 500.0f, 50.0f + i * 16.0f );
			}
		}
		
		// 2Dï`âÊèIóπ
		MAPIL::EndRendering2DGraphics();
	}

	void History::Init()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		MAPIL::RefleshResources();
	}
}