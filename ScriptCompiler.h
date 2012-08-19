#ifndef INCLUDED_RTG_SCRIPTCOMPILER_H
#define INCLUDED_RTG_SCRIPTCOMPILER_H

#include <vector>
#include <map>

#include "ScriptEngine/VM.h"

namespace RTG
{
	// リソースタイプ
	enum ResourceType
	{
		RESOURCE_TYPE_BGM	= 0,		// BGM
		RESOURCE_TYPE_SE	= 1,		// 効果音
	};

	// リソースタグ
	struct ResourceTag
	{
		int		m_ID;					// 識別番号
		int		m_Type;					// リソースタイプ
		char	m_FileName[ 1024 ];		// ファイルタイプ
	};

	// ステージタグ
	struct StageTag
	{
		int		m_StageNo;				// ステージ番号
		char	m_FileName[ 1024 ];		// ファイル名
	};

	struct ResourceScriptData
	{
		std::map < int, std::string >		m_BGMList;
		std::map < int, std::string >		m_SEList;
		std::map < int, std::string >		m_TextureList;
	};

	// スクリプトファイル構成図
	//
	//	Stage構成情報ファイル ------> Stage1構成ファイル --------> リソーススクリプトファイル
	//							|							|
	//							|							---> 敵スクリプトファイル 0 ...
	//							|							|
	//							|							---> 敵弾スクリプトファイル 0 ...
	//							|							|
	//							|							---> ステージスクリプトファイル
	//							|
	//							---> Stage2構成ファイル
	//							|

	class ScriptCompiler
	{
	private:
		// 個別のスクリプトファイルのための構造体
		struct ScriptFileTag
		{
			int		m_ID;					// 識別番号
			char	m_FileName[ 1024 ];		// ファイル名
		};
		// スクリプトファイルの種類
		enum ScriptType
		{
			SCRIPT_TYPE_ENEMY		= 0,
			SCRIPT_TYPE_ENEMY_SHOT	= 1,
			SCRIPT_TYPE_STAGE		= 2,
			SCRIPT_TYPE_RESOURCE	= 3,
		};
		// リソーススクリプトのリソースの種類
		enum ResourceType
		{
			RESOURCE_TYPE_BGM		= 0,
			RESOURCE_TYPE_SE		= 1,
			RESOURCE_TYPE_TEXTURE	= 2,
		};

		// スクリプトデータ
		struct ScriptData
		{
			int			m_ID;		// 識別番号
			VM::Data	m_Data;		// スクリプトデータ本体
		};

		bool							m_Loaded;				// 読み込み完了フラグ

		std::vector < StageTag >		m_StageFileList;		// ステージファイル名のリスト

		// スクリプト本体
		ScriptData*						m_pStageScriptData;			// ステージスクリプト
		// map( index, filename ) => vector( index, val->handle)
		ResourceScriptData				m_ResourceScriptData;		// ロードするリソースリスト
		ScriptData*						m_pEnemyScriptData;			// 敵のスクリプト本体
		int								m_EnemyScirptTotal;			// 敵のスクリプト数
		ScriptData*						m_pEnemyShotScriptData;		// 敵弾のスクリプト本体
		int								m_EnemyShotScriptTotal;		// 敵弾のスクリプト数


		// 非公開関数
		void CompileEnemyShotScript( int id, const char* pFileName );	// 敵弾のスクリプトのコンパイル
		void CompileEnemyScript( int id, const char* pFileName );		// 敵のスクリプトのコンパイル
		void CompileStageScript( const char* pFileName );				// ステージのスクリプトのコンパイル
		void LoadStageScript( const char* pFileName );						// ステージスクリプトのロード
		void LoadStageScript( int archiveHandle, const char* pFilePath );		// ステージスクリプトのロード（アーカイブから）
		void LoadEnemyScript( int i, const char* pFileName );					// 敵のスクリプトのロード
		void LoadEnemyScript( int archiveHandle, int i, const char* pFilePath );	// 敵のスクリプトのロード（アーカイブから）
		void LoadEnemyShotScript( int i, const char* pFileName );				// 敵弾のスクリプトのロード
		void LoadEnemyShotScript( int archiveHandle, int i, const char* pFilePath );	// 敵弾のスクリプトのロード（アーカイブから）
		void LoadScript( const char* pFileName, VM::Data* pVMData );			// スクリプトのロード
		void LoadScript( int archiveHandle, const char* pFileName, VM::Data* pVMData );	// スクリプトのロード（アーカイブから）
		void CompileResourceScript( const char* pFileName );					// リソーススクリプトのコンパイル
		void LoadResourceScript( int archiveHandle, const char* pFilePath );	// リソーススクリプトのロード（アーカイブから）
		void Cleanup();															// 現在のステージ構成スクリプトを削除
	public:
		ScriptCompiler();
		~ScriptCompiler();
		void BuildFileStructure( const char* pFileName );						// スクリプトファイルの構成を作成
		void BuildFileStructure( int archiveHandle, const char* pFileName );	// スクリプトファイルの構成を作成（アーカイブファイルから）
		void Load( int stage );													// コンパイル済みのスクリプトデータの読み込み
		void Load( int archiveHandle, int stage );								// コンパイル済みのスクリプトデータの読み込み（アーカイブファイルから）
		void Compile( int stage );												// ステージを指定してコンパイル
		ResourceScriptData GetResourceScriptData();								// リソーススクリプトデータを取得する
		VM::Data* GetStageScript();												// ステージスクリプトを取得
		VM::Data* GetEnemyScript( int index );									// 敵のスクリプトを取得
		VM::Data* GetEnemyShotScript( int index );								// 敵弾のスクリプトを取得
		bool Loaded() const;													// 読み込みが完了したか
	};
}

#endif