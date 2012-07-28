#include "Defines.h"
#include "MainFrame.h"

#include "ScriptCompiler.h"

#include "ScriptEngine/Compiler.h"
#include "ScriptEngine/VM.h"

#include "ScriptedEnemy.h"
#include "ScriptedStage.h"

#pragma comment ( lib, "MAPIL.lib" )

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nCmd )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	try{
		RTG::MainFrame mf;
		mf.Init();
		mf.Run();
	}
	catch( MAPIL::MapilException& e ){
		OutputDebugString( e.GetExceptionStr().c_str() );
	}

	return 0;
}