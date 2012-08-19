#include "Defines.h"

#include "ScriptCompiler.h"

#include "ScriptEngine/Compiler.h"

#include <fstream>
#include <string.h>

#pragma warning ( disable : 4996 )

namespace RTG
{
	static int GetFileSize( std::fstream &f )
	{
		int size = 0;
		int begin = 0;
		int end = 0;
		f.seekg( 0, std::ios::beg );
		begin = f.tellg();
		f.seekg( 0, std::ios::end );
		end = f.tellg();
		size = end - begin;
		f.seekg( 0, std::ios::beg );

		return size;
	}

	static int GetInt( char** p )
	{
		int i = MAPIL::TransformCharIntoInt32( *p, MAPIL::BYTE_ORDER_LITTLE );
		*p += 4;

		return i;
	}

	static int GetID( const char* pStr )
	{
		char buf[ 5 ];		// 1000まで格納可能
		int pos = 0;

		while( *pStr ){
			if( *pStr == ' ' || pos > 3 ){
				break;
			}
			buf[ pos++ ] = *pStr++;
		}
		buf[ pos ] = '\0';

		return ::atoi( buf );
	}

	static char* GetFileName( char* pStr )
	{
		while( *pStr++ != ' ' ){
		}

		return pStr;
	}

	static void GetLineFromString( char** pStr, char* pEnd, char* pOut, int outSize )
	{
		while( *pStr != pEnd ){
			if( **pStr == '\r' ){
				(*pStr)++;
				continue;
			}
			else if( **pStr == '\n' ){
				(*pStr)++;
				break;
			}
			*pOut++ = **pStr;
			(*pStr)++;
		}
		*pOut = '\0';
	}

	ScriptCompiler::ScriptCompiler() :	m_Loaded( true ),
										m_StageFileList(),
										m_pStageScriptData( NULL ),
										m_pEnemyScriptData( NULL ),
										m_EnemyScirptTotal( 0 ),
										m_pEnemyShotScriptData( NULL ),
										m_EnemyShotScriptTotal( 0 )
	{
		m_StageFileList.clear();
	}

	ScriptCompiler::~ScriptCompiler()
	{
		Cleanup();

		m_StageFileList.clear();
		m_Loaded = false;
	}

	void ScriptCompiler::CompileEnemyShotScript( int id, const char* pFileName )
	{
		Compiler compiler;
		compiler.Compile( pFileName, m_pEnemyShotScriptData[ id ].m_Data );
	}

	void ScriptCompiler::CompileEnemyScript( int id, const char* pFileName )
	{
		Compiler compiler;
		compiler.Compile( pFileName, m_pEnemyScriptData[ id ].m_Data );
	}

	void ScriptCompiler::CompileStageScript( const char* pFileName )
	{
		Compiler compiler;
		compiler.Compile( pFileName, m_pStageScriptData->m_Data );
	}

	void ScriptCompiler::LoadScript( const char* pFileName, VM::Data* pVMData )
	{
		std::fstream fStgScrIn( pFileName, std::ios::binary | std::ios::in );
		int dataSize = GetFileSize( fStgScrIn );
		char* pData = new char [ dataSize ];
		fStgScrIn.read( pData, dataSize );
		// VM::Dataの再構築
		char* p = pData;
		int cmdSize = GetInt( &p );
		pVMData->m_CommandSize = cmdSize;
		pVMData->m_Command = new unsigned char [ cmdSize ];
		::memcpy( pVMData->m_Command, p, cmdSize );
		p += cmdSize;
		int entryPoint = GetInt( &p );
		pVMData->m_EntryPoint = entryPoint;
		int textSize = GetInt( &p );
		pVMData->m_TextSize = textSize;
		pVMData->m_TextBuffer = new char [ textSize ];
		::memcpy( pVMData->m_TextBuffer, p, textSize );
		p += textSize;
		int valueSize = GetInt( &p );
		pVMData->m_ValueSize = valueSize;
		MAPIL::SafeDeleteArray( pData );
	}

	void ScriptCompiler::LoadScript( int archiveHandle, const char* pFileName, VM::Data* pVMData )
	{
		// アーカイブからのデータ読み込み
		int dataSize = MAPIL::GetContentsSizeOnArchiveFile( archiveHandle, pFileName );
		char* pData = new char [ dataSize ];
		MAPIL::LoadDataFromArchiveFile( archiveHandle, pFileName, pData );
		// VM::Dataの再構築
		char* p = pData;
		int cmdSize = GetInt( &p );
		pVMData->m_CommandSize = cmdSize;
		pVMData->m_Command = new unsigned char [ cmdSize ];
		::memcpy( pVMData->m_Command, p, cmdSize );
		p += cmdSize;
		int entryPoint = GetInt( &p );
		pVMData->m_EntryPoint = entryPoint;
		int textSize = GetInt( &p );
		pVMData->m_TextSize = textSize;
		pVMData->m_TextBuffer = new char [ textSize ];
		::memcpy( pVMData->m_TextBuffer, p, textSize );
		p += textSize;
		int valueSize = GetInt( &p );
		pVMData->m_ValueSize = valueSize;
		MAPIL::SafeDeleteArray( pData );
	}

	void ScriptCompiler::LoadStageScript( const char* pFileName )
	{
		LoadScript( pFileName, &m_pStageScriptData->m_Data );
	}

	void ScriptCompiler::LoadStageScript( int archiveHandle, const char* pFilePath )
	{
		LoadScript( archiveHandle, pFilePath, &m_pStageScriptData->m_Data );
	}

	void ScriptCompiler::LoadEnemyScript( int i, const char* pFileName )
	{
		LoadScript( pFileName, &m_pEnemyScriptData[ i ].m_Data );
	}

	void ScriptCompiler::LoadEnemyScript( int archiveHandle, int i, const char* pFilePath )
	{
		LoadScript( archiveHandle, pFilePath, &m_pEnemyScriptData[ i ].m_Data );
	}

	void ScriptCompiler::LoadEnemyShotScript( int i, const char* pFileName )
	{
		LoadScript( pFileName, &m_pEnemyShotScriptData[ i ].m_Data );
	}

	void ScriptCompiler::LoadEnemyShotScript( int archiveHandle, int i, const char* pFilePath )
	{
		LoadScript( archiveHandle, pFilePath, &m_pEnemyShotScriptData[ i ].m_Data );
	}

	void ScriptCompiler::CompileResourceScript( const char* pFileName )
	{
		std::ifstream fIn( pFileName, std::ios::in );

		int type;		// スクリプトタイプ
		while( !fIn.eof() ){
			char buf[ 1024 ];
			fIn.getline( buf, sizeof( buf ) );
			if( !strcmp( buf, "[BGM]" ) ){
				type = RESOURCE_TYPE_BGM;
			}
			else if( !strcmp( buf, "[SE]" ) ){
				type = RESOURCE_TYPE_SE;
			}
			else if( !strcmp( buf, "[Texture]" ) ){
				type = RESOURCE_TYPE_TEXTURE;
			}
			else if( !strcmp( buf, "" ) ){
				// 無視
			}
			else{
				// ファイル名取得
				if( type == RESOURCE_TYPE_BGM ){
					m_ResourceScriptData.m_BGMList.insert( std::pair < int, std::string > ( GetID( buf ), GetFileName( buf ) ) );
				}
				else if( type == RESOURCE_TYPE_SE ){
					m_ResourceScriptData.m_SEList.insert( std::pair < int, std::string > ( GetID( buf ), GetFileName( buf ) ) );
				}
				else if( type == RESOURCE_TYPE_TEXTURE ){
					m_ResourceScriptData.m_TextureList.insert( std::pair < int, std::string > ( GetID( buf ), GetFileName( buf ) ) );
				}
			}
		}
	}

	void ScriptCompiler::LoadResourceScript( int archiveHandle, const char* pFilePath )
	{
		int size = MAPIL::GetContentsSizeOnArchiveFile( archiveHandle, pFilePath );
		char* pData = new char [ size ];
		MAPIL::LoadDataFromArchiveFile( archiveHandle, pFilePath, pData );
		char* pBegin = pData;
		char* pEnd = pData + size;

		int type;		// スクリプトタイプ
		while( pData != pEnd ){
			char buf[ 1024 ];
			GetLineFromString( &pData, pEnd, buf, sizeof( buf ) );
			if( !strcmp( buf, "[BGM]" ) ){
				type = RESOURCE_TYPE_BGM;
			}
			else if( !strcmp( buf, "[SE]" ) ){
				type = RESOURCE_TYPE_SE;
			}
			else if( !strcmp( buf, "[Texture]" ) ){
				type = RESOURCE_TYPE_TEXTURE;
			}
			else if( !strcmp( buf, "" ) ){
				// 無視
			}
			else{
				// ファイル名取得
				if( type == RESOURCE_TYPE_BGM ){
					m_ResourceScriptData.m_BGMList.insert( std::pair < int, std::string > ( GetID( buf ), GetFileName( buf ) ) );
				}
				else if( type == RESOURCE_TYPE_SE ){
					m_ResourceScriptData.m_SEList.insert( std::pair < int, std::string > ( GetID( buf ), GetFileName( buf ) ) );
				}
				else if( type == RESOURCE_TYPE_TEXTURE ){
					m_ResourceScriptData.m_TextureList.insert( std::pair < int, std::string > ( GetID( buf ), GetFileName( buf ) ) );
				}
			}
		}

		MAPIL::SafeDeleteArray( pBegin );
	}

	void ScriptCompiler::Cleanup()
	{
		MAPIL::SafeDelete( m_pStageScriptData );
		MAPIL::SafeDeleteArray( m_pEnemyScriptData );
		MAPIL::SafeDeleteArray( m_pEnemyShotScriptData );
		m_EnemyScirptTotal = 0;
		m_EnemyShotScriptTotal = 0;
	}

	void ScriptCompiler::BuildFileStructure( const char* pFileName )
	{
		// スクリプト構成情報を取得
		m_Loaded = false;

		std::ifstream fIn( pFileName, std::ios::in );
		if( !fIn ){
			exit( 1 );
		}

		while( !fIn.eof() ){
			char buf[ 1024 ];
			fIn.getline( buf, sizeof( buf ) );	// アトリビュートの取得
			StageTag tag;
			tag.m_StageNo = GetID( buf );
			::strcpy( tag.m_FileName, GetFileName( buf ) );
			m_StageFileList.push_back( tag );
		}

		fIn.close();
	}

	

	void ScriptCompiler::BuildFileStructure( int archiveHandle, const char* pFileName )
	{
		// スクリプト構成情報を取得
		m_Loaded = false;

		int fileSize = MAPIL::GetContentsSizeOnArchiveFile( archiveHandle, pFileName );
		char* pData = new char [ fileSize ];
		char* pBegin = pData;
		char* pEnd = pData + fileSize;
		MAPIL::LoadDataFromArchiveFile( archiveHandle, pFileName, pData );

		while( pData != pEnd ){
			char buf[ 1024 ];
			GetLineFromString( &pData, pEnd, buf, sizeof( buf ) );
			StageTag tag;
			tag.m_StageNo = GetID( buf );
			::strcpy( tag.m_FileName, GetFileName( buf ) );
			m_StageFileList.push_back( tag );
		}

		MAPIL::SafeDeleteArray( pBegin );
	}
	

	void ScriptCompiler::Load( int stage )
	{
		Cleanup();
		// ファイル構成スクリプトの検索
		unsigned int cur = 0;
		std::ifstream fIn;
		for( ; cur < m_StageFileList.size(); ++cur ){
			if( m_StageFileList[ cur ].m_StageNo == stage ){
				fIn.open( m_StageFileList[ cur ].m_FileName, std::ios::in );
				if( !fIn ){
					exit( 1 );
				}
				break;
			}
		}
		if( cur == m_StageFileList.size() ){
			exit( 1 );	// 指定されたステージのファイル構成スクリプトは存在しない。
		}

		// ファイル構成スクリプトからスクリプトファイル名を取得する
		std::vector < ScriptFileTag > enemyScriptList;		// 敵のスクリプト
		std::vector < ScriptFileTag > enemyShotScriptList;	// 敵弾のスクリプト
		char stageScriptFileName[ 1024 ];					// ステージスクリプトのファイル名
		char resourceScriptFileName[ 1024 ];				// リソーススクリプトのファイル名
		int type;		// スクリプトタイプ
		while( !fIn.eof() ){
			char buf[ 1024 ];
			fIn.getline( buf, sizeof( buf ) );
			if( !strcmp( buf, "[Enemy]" ) ){
				type = SCRIPT_TYPE_ENEMY;
			}
			else if( !strcmp( buf, "[EnemyShot]" ) ){
				type = SCRIPT_TYPE_ENEMY_SHOT;
			}
			else if( !strcmp( buf, "[Stage]" ) ){
				type = SCRIPT_TYPE_STAGE;
			}
			else if( !strcmp( buf, "[Resource]" ) ){
				type = SCRIPT_TYPE_RESOURCE;
			}
			else if( !strcmp( buf, "" ) ){
				// 無視
			}
			else{
				// ファイル名取得
				if( type == SCRIPT_TYPE_STAGE ){
					::strcpy( stageScriptFileName, buf );
				}
				else if( type == SCRIPT_TYPE_RESOURCE ){
					::strcpy( resourceScriptFileName, buf );
				}
				else{
					ScriptFileTag tag;
					tag.m_ID = GetID( buf );
					::strcpy( tag.m_FileName, GetFileName( buf ) );
					if( type == SCRIPT_TYPE_ENEMY ){
						enemyScriptList.push_back( tag );
					}
					else if( type == SCRIPT_TYPE_ENEMY_SHOT ){
						enemyShotScriptList.push_back( tag );
					}
				}
			}
		}

		m_EnemyScirptTotal = enemyScriptList.size();
		m_EnemyShotScriptTotal = enemyShotScriptList.size();

		// ステージスクリプトの読み込み
		m_pStageScriptData = new ScriptData;
		// スクリプトデータの読み込み
		LoadStageScript( stageScriptFileName );

		// リソーススクリプトの読み込み
		CompileResourceScript( resourceScriptFileName );
		
		// 敵の行動パターンスクリプトの読み込み
		m_pEnemyScriptData = new ScriptData [ m_EnemyScirptTotal ];
		for( int i = 0; i < m_EnemyScirptTotal; ++i ){
			m_pEnemyScriptData[ i ].m_ID = enemyScriptList[ i ].m_ID;
			LoadEnemyScript( i, enemyScriptList[ i ].m_FileName );
		}

		// 敵弾のスクリプトの読み込み
		m_pEnemyShotScriptData = new ScriptData [ m_EnemyShotScriptTotal ];
		for( int i = 0; i < m_EnemyShotScriptTotal; ++i ){
			m_pEnemyShotScriptData[ i ].m_ID = enemyShotScriptList[ i ].m_ID;
			LoadEnemyShotScript( i, enemyShotScriptList[ i ].m_FileName );
		}

		m_Loaded = true;
	}

	void ScriptCompiler::Load( int archiveHandle, int stage )
	{
		Cleanup();
		// ファイル構成スクリプトの検索
		unsigned int cur = 0;
		for( ; cur < m_StageFileList.size(); ++cur ){
			if( m_StageFileList[ cur ].m_StageNo == stage ){
				break;
			}
		}
		if( cur == m_StageFileList.size() ){
			exit( 1 );	// 指定されたステージのファイル構成スクリプトは存在しない。
		}

		int size = MAPIL::GetContentsSizeOnArchiveFile( archiveHandle, m_StageFileList[ cur ].m_FileName );
		char* pData = new char [ size ];
		MAPIL::LoadDataFromArchiveFile( archiveHandle, m_StageFileList[ cur ].m_FileName, pData );
		char* pBegin = pData;
		char* pEnd = pData + size;

		// ファイル構成スクリプトからスクリプトファイル名を取得する
		std::vector < ScriptFileTag > enemyScriptList;		// 敵のスクリプト
		std::vector < ScriptFileTag > enemyShotScriptList;	// 敵弾のスクリプト
		char stageScriptFileName[ 1024 ];					// ステージスクリプトのファイル名
		char resourceScriptFileName[ 1024 ];				// リソーススクリプトのファイル名
		int type;		// スクリプトタイプ
		while( pData != pEnd ){
			char buf[ 1024 ];
			GetLineFromString( &pData, pEnd, buf, sizeof( buf ) );
			//fIn.getline( buf, sizeof( buf ) );
			if( !strcmp( buf, "[Enemy]" ) ){
				type = SCRIPT_TYPE_ENEMY;
			}
			else if( !strcmp( buf, "[EnemyShot]" ) ){
				type = SCRIPT_TYPE_ENEMY_SHOT;
			}
			else if( !strcmp( buf, "[Stage]" ) ){
				type = SCRIPT_TYPE_STAGE;
			}
			else if( !strcmp( buf, "[Resource]" ) ){
				type = SCRIPT_TYPE_RESOURCE;
			}
			else if( !strcmp( buf, "" ) ){
				// 無視
			}
			else{
				// ファイル名取得
				if( type == SCRIPT_TYPE_STAGE ){
					::strcpy( stageScriptFileName, buf );
				}
				else if( type == SCRIPT_TYPE_RESOURCE ){
					::strcpy( resourceScriptFileName, buf );
				}
				else{
					ScriptFileTag tag;
					tag.m_ID = GetID( buf );
					::strcpy( tag.m_FileName, GetFileName( buf ) );
					if( type == SCRIPT_TYPE_ENEMY ){
						enemyScriptList.push_back( tag );
					}
					else if( type == SCRIPT_TYPE_ENEMY_SHOT ){
						enemyShotScriptList.push_back( tag );
					}
				}
			}
		}

		

		m_EnemyScirptTotal = enemyScriptList.size();
		m_EnemyShotScriptTotal = enemyShotScriptList.size();

		// ステージスクリプトの読み込み
		m_pStageScriptData = new ScriptData;
		// スクリプトデータの読み込み
		LoadStageScript( archiveHandle, stageScriptFileName );

		// リソーススクリプトの読み込み
		LoadResourceScript( archiveHandle, resourceScriptFileName );
		
		// 敵の行動パターンスクリプトの読み込み
		m_pEnemyScriptData = new ScriptData [ m_EnemyScirptTotal ];
		for( int i = 0; i < m_EnemyScirptTotal; ++i ){
			m_pEnemyScriptData[ i ].m_ID = enemyScriptList[ i ].m_ID;
			LoadEnemyScript( archiveHandle, i, enemyScriptList[ i ].m_FileName );
		}

		// 敵弾のスクリプトの読み込み
		m_pEnemyShotScriptData = new ScriptData [ m_EnemyShotScriptTotal ];
		for( int i = 0; i < m_EnemyShotScriptTotal; ++i ){
			m_pEnemyShotScriptData[ i ].m_ID = enemyShotScriptList[ i ].m_ID;
			LoadEnemyShotScript( archiveHandle, i, enemyShotScriptList[ i ].m_FileName );
		}

		m_Loaded = true;

		MAPIL::SafeDeleteArray( pBegin );
	}

	void ScriptCompiler::Compile( int stage )
	{
		Cleanup();

		// ファイル構成スクリプトの検索
		unsigned int cur = 0;
		std::ifstream fIn;
		for( ; cur < m_StageFileList.size(); ++cur ){
			if( m_StageFileList[ cur ].m_StageNo == stage ){
				fIn.open( m_StageFileList[ cur ].m_FileName, std::ios::in );
				if( !fIn ){
					exit( 1 );
				}
				break;
			}
		}
		if( cur == m_StageFileList.size() ){
			exit( 1 );	// 指定されたステージのファイル構成スクリプトは存在しない。
		}

		// ファイル構成スクリプトからスクリプトファイル名を取得する
		std::vector < ScriptFileTag > enemyScriptList;		// 敵のスクリプト
		std::vector < ScriptFileTag > enemyShotScriptList;	// 敵弾のスクリプト
		char stageScriptFileName[ 1024 ];					// ステージスクリプトのファイル名
		char resourceScriptFileName[ 1024 ];				// リソーススクリプトのファイル名
		int type;		// スクリプトタイプ
		while( !fIn.eof() ){
			char buf[ 1024 ];
			fIn.getline( buf, sizeof( buf ) );
			if( !strcmp( buf, "[Enemy]" ) ){
				type = SCRIPT_TYPE_ENEMY;
			}
			else if( !strcmp( buf, "[EnemyShot]" ) ){
				type = SCRIPT_TYPE_ENEMY_SHOT;
			}
			else if( !strcmp( buf, "[Stage]" ) ){
				type = SCRIPT_TYPE_STAGE;
			}
			else if( !strcmp( buf, "[Resource]" ) ){
				type = SCRIPT_TYPE_RESOURCE;
			}
			else if( !strcmp( buf, "" ) ){
				// 無視
			}
			else{
				// ファイル名取得
				if( type == SCRIPT_TYPE_STAGE ){
					::strcpy( stageScriptFileName, buf );
				}
				else if( type == SCRIPT_TYPE_RESOURCE ){
					::strcpy( resourceScriptFileName, buf );
				}
				else{
					ScriptFileTag tag;
					tag.m_ID = GetID( buf );
					::strcpy( tag.m_FileName, GetFileName( buf ) );
					if( type == SCRIPT_TYPE_ENEMY ){
						enemyScriptList.push_back( tag );
					}
					else if( type == SCRIPT_TYPE_ENEMY_SHOT ){
						enemyShotScriptList.push_back( tag );
					}
				}
			}
		}

		m_EnemyScirptTotal = enemyScriptList.size();
		m_EnemyShotScriptTotal = enemyShotScriptList.size();

		const int MAXIMUM_COMMAND = 65535;		// 最大コマンド数

		// ステージスクリプトの読み込み
		m_pStageScriptData = new ScriptData;
		CompileStageScript( stageScriptFileName );

		// リソーススクリプトの読み込み
		CompileResourceScript( resourceScriptFileName );
		
		// 敵の行動パターンスクリプトの読み込み
		m_pEnemyScriptData = new ScriptData [ m_EnemyScirptTotal ];
		for( int i = 0; i < m_EnemyScirptTotal; ++i ){
			m_pEnemyScriptData[ i ].m_ID = enemyScriptList[ i ].m_ID;
			CompileEnemyScript( i, enemyScriptList[ i ].m_FileName );
		}

		// 敵弾のスクリプトの読み込み
		m_pEnemyShotScriptData = new ScriptData [ m_EnemyShotScriptTotal ];
		for( int i = 0; i < m_EnemyShotScriptTotal; ++i ){
			m_pEnemyShotScriptData[ i ].m_ID = enemyScriptList[ i ].m_ID;
			CompileEnemyShotScript( i, enemyShotScriptList[ i ].m_FileName );
		}

		m_Loaded = true;
	}

	ResourceScriptData ScriptCompiler::GetResourceScriptData()
	{
		return m_ResourceScriptData;
	}

	VM::Data* ScriptCompiler::GetStageScript()
	{
		return &m_pStageScriptData->m_Data;
	}

	VM::Data* ScriptCompiler::GetEnemyScript( int index )
	{
		return &m_pEnemyScriptData[ index ].m_Data;
	}

	VM::Data* ScriptCompiler::GetEnemyShotScript( int index )
	{
		return &m_pEnemyShotScriptData[ index ].m_Data;
	}

	bool ScriptCompiler::Loaded() const
	{
		return m_Loaded;
	}
}