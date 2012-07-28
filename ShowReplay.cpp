#include "ResourceHandler.h"

#include "ShowReplay.h"
#include "Menu.h"
#include "Keyboard.h"
#include "ReplayLoader.h"
#include "ScriptedStage.h"
#include "GeneralButtonManager.h"

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
			rl.Load( fileName );
			rl.GetReplayData( p->m_pReplayEntry );
			p->m_pGBManager->SetReplay( 1 );
			SetNextScene( new ScriptedStage( p->m_pCompiler, 1 ) );
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
		else if( p->m_pGBManager->IsPushedOnce( GENERAL_BUTTON_CANCEL ) ){
			SetNextScene( new Menu() );
		}
	}

	void ShowReplay::Draw()
	{
		// 2D•`‰æŠJŽn
		MAPIL::BeginRendering2DGraphics();

		for( int i = 0; i < 25; ++i ){
			if( i == m_FileNo ){
				MAPIL::DrawString( 100.0f, 50.0f + i * 15.0f, 0xFFFFFFFF, m_EntryStr[ i ] );
			}
			else{
				MAPIL::DrawString( 100.0f, 50.0f + i * 15.0f, 0x66666666, m_EntryStr[ i ] );
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