#include "Defines.h"

#include "ScriptCompiler.h"

#include "ScriptEngine/Compiler.h"

#include <fstream>
#include <string.h>

#pragma warning ( disable : 4996 )

namespace RTG
{
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