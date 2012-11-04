#include "ResourceHandler.h"

#include "ShowReplay.h"
#include "Menu.h"
#include "Keyboard.h"
#include "ReplayLoader.h"
#include "ScriptedStage.h"
#include "GeneralButtonManager.h"
#include "FontString.h"

#include <time.h>

namespace RTG
{
	ShowReplay::ShowReplay() : m_FileNo( 0 )
	{
		MAPIL::ZeroObject( m_Name, sizeof( m_Name ) );
	}

	ShowReplay::~ShowReplay()
	{
		MAPIL::ZeroObject( m_Name, sizeof( m_Name ) );
		m_FileNo = 0;
	}

	bool ShowReplay::IsLoading() const
	{
		return false;
	}

	void ShowReplay::Update()
	{
		ResourceHandler* p = ResourceHandler::GetInst();

		if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_ENTER ) ){
			char fileName[ 40 ];
			sprintf( fileName, "replay/entry%d.rpy", m_FileNo );
			ReplayLoader rl;
			if( rl.Load( fileName ) != -1 ){
				rl.GetReplayData( p->m_pReplayEntry );
				p->m_pGBManager->SetReplay( 1 );
				SetNextScene( new ScriptedStage( p->m_pCompiler, 1, PLAY_MODE_REPLAY ) );
				MAPIL::StopStreamingBuffer( p->m_MenuBGM );
				MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
			}
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
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
			SetNextScene( new Menu() );
			MAPIL::PlayStaticBuffer( p->m_MenuSelectSE );
		}
	}

	void ShowReplay::Draw()
	{
		// 2D•`‰æŠJŽn
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
		
		// 2D•`‰æI—¹
		MAPIL::EndRendering2DGraphics();
	}


	void ShowReplay::Init()
	{
		MAPIL::RefleshResources();

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