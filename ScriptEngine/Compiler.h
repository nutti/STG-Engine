#ifndef INCLUDED_COMPILER_H
#define INCLUDED_COMPILER_H


//#define _DEBUG

#include "Parser.hh"
#include "VM.h"
#include "Node.h"

class Compiler;

#define YY_DECL									\
	yy::Parser::token_type						\
	yylex(	yy::Parser::semantic_type* yylval,	\
			yy::Parser::location_type* yylloc,	\
			Compiler& compiler )

YY_DECL;

class VMCode
{
public:
	unsigned char	m_Size;
	unsigned char	m_OP;
	union{
		int				m_Arg1;
		float			m_FArg1;
	};
public:
	VMCode( unsigned char op ) :	m_Size( 1 ),
									m_OP( op ),
									m_Arg1( 0 )
	{
	}
	VMCode( unsigned char op, int arg1 ) :	m_Size( 5 ),
											m_OP( op ),
											m_Arg1( arg1 )
	{
	}
	VMCode( unsigned char op, float arg1 ) :	m_Size( 5 ),
												m_OP( op ),
												m_FArg1( arg1 )
	{
	}
	unsigned char* Get( unsigned char* p ) const
	{
		if( m_OP != VM_MAXCOMMAND ){
			*p++ = m_OP;
			if( m_Size > 1 ){
				*(int *)p = m_Arg1;
				p += 4;
			}
		}
		return p;
	}
};


class Label
{
public:
	int		m_Index;
	int		m_Pos;
public:
	Label( int index ) : m_Index( index ), m_Pos( 0 )
	{
	}
	~Label()
	{
	}
};

class ValueTag
{
public:
	int		m_Addr;
	int		m_Type;
	int		m_Size;
	bool	m_Global;
public:
	ValueTag() : m_Addr( -1 ), m_Type( TYPE_INTEGER ), m_Size( 1 ), m_Global( false )
	{
	}
	ValueTag( int addr, int type, int size, bool global ) :	m_Addr( addr ),
															m_Type( type ),
															m_Size( size ),
															m_Global( global )
	{
	}
};

class ValueTable
{
private:
	std::map < std::string, ValueTag >	m_Variables;	// Variable table.
	int									m_Addr;			// Current position.
	bool								m_Global;		// Is global?

	typedef std::map < std::string, ValueTag > ::iterator iter;
	typedef std::map < std::string, ValueTag > ::const_iterator iterConst;
public:
	ValueTable( int startAddr = 0 ) : m_Addr( startAddr ), m_Global( false )
	{
	}
	void SetGlobal()
	{
		m_Global = true;
	}
	bool Add( int type, const std::string& name, int size = 1 )
	{
		std::pair < iter, bool > result = m_Variables.insert( make_pair( name, ValueTag( m_Addr, type, size, m_Global ) ) );
		if( result.second ){
			m_Addr += size;
			//std::cout << "test:" << m_Addr << std::endl;
			return true;
		}
		return false;
	}
	const ValueTag* Find( const std::string& name ) const
	{
		iterConst it = m_Variables.find( name );
		if( it != m_Variables.end() ){
			//std::cout << "t:" << name << std::endl;
			return &it->second;
		}
		return NULL;
	}
	bool AddArg( int type, const std::string& name, int addr )
	{
		std::pair < iter, bool > result = m_Variables.insert( make_pair( name, ValueTag( addr, type, 1, false ) ) );
		return result.second;
	}
	int GetSize() const { return m_Addr; }
	void Clear()
	{
		m_Variables.clear();
		m_Addr = 0;
	}
#ifdef _DEBUG
	struct DumpAction
	{
		void operator()( const std::pair < std::string, ValueTag >& it )
		{
			std::cout	<< it.first << ", addr = " << it.second.m_Addr
						<< ", type = " << it.second.m_Type
						<< ", size = " << it.second.m_Size
						<< ". global = " << it.second.m_Global << std::endl;
		}
	};
	void Dump() const
	{
		std::cout << "--------- value -----------" << std::endl;
		std::for_each( m_Variables.begin(), m_Variables.end(), DumpAction() );
	}
#endif
};

class FunctionTag
{
public:
	int						m_Type;
	int						m_Flags;
	int						m_Index;
	std::vector < char >	m_Args;
private:
	enum
	{
		FLAG_DECLARATION		= 1 << 0,
		FLAG_DEFINITION			= 1 << 1,
		FLAG_SYSTEM				= 1 << 2,
	};
public:
	FunctionTag()
	{
	}
	FunctionTag( int type ) : m_Type( type ), m_Flags( 0 ), m_Index( 0 )
	{	
	}
	void SetArg( int type )
	{
		m_Args.push_back( ( char ) type );
	}
	void SetArgs( const ArgList* pArgs )
	{
		if( pArgs ){
			size_t size = pArgs->Size();
			for( size_t i = 0; i < size; ++i ){
				m_Args.push_back( ( char ) pArgs->Get( i )->GetType() );
			}
		}
	}
	bool SetArgs( const char* pArgs )
	{
		if( pArgs ){
			for( int i = 0; pArgs[ i ] != 0; ++i ){
				switch( pArgs[ i ] ){
					case 'I':
					case 'i':
						m_Args.push_back( TYPE_INTEGER );
						break;
					case 'S':
					case 's':
						m_Args.push_back( TYPE_STRING );
						break;
					case 'F':
					case 'f':
						m_Args.push_back( TYPE_FLOAT );
						break;
					default:
						return false;
				}
			}
		}
		return true;
	}
	bool CheckArgList( const ArgList* pArgs ) const
	{
		// Argments are not existed.
		if( pArgs == 0 ){
			return m_Args.empty();
		}

		// Size of argments is mismatched.
		if( m_Args.size() != pArgs->Size() ){
			return false;
		}

		// All argument types are checked.
		size_t size = m_Args.size();
		for( size_t i = 0; i < size; ++i ){
			if( pArgs->Get( i )->GetType() != ( int ) m_Args[ i ] ){
				return false;
			}
		}

		return true;
	}
	int GetArg( int index ) const
	{
		return m_Args[ index ];
	}
	int ArgSize() const
	{
		return m_Args.size();
	}
	void SetIndex( int index )
	{
		m_Index = index;
	}
	void SetDeclaration()
	{
		m_Flags |= FLAG_DECLARATION;
	}
	void SetDefinition()
	{
		m_Flags |= FLAG_DEFINITION;
	}
	void SetSystem()
	{
		m_Flags |= FLAG_SYSTEM;
	}
	int GetIndex() const
	{
		return m_Index;
	}
	bool IsDeclaration() const
	{
		return ( m_Flags & FLAG_DECLARATION ) != 0;
	}
	bool IsDefinition() const
	{
		return ( m_Flags & FLAG_DEFINITION ) != 0;
	}
	bool IsSystem() const
	{
		return ( m_Flags & FLAG_SYSTEM ) != 0;
	}
};

class FunctionTable
{
private:
	std::map < std::string, FunctionTag >	m_Functions;

	typedef std::map < std::string, FunctionTag > ::iterator	iter;
	typedef std::map < std::string, FunctionTag > ::const_iterator iterConst;
public:
	FunctionTable()
	{
	}
	FunctionTag* Add( const std::string& name, const FunctionTag& tag )
	{
		std::pair < iter, bool > result = m_Functions.insert( make_pair( name, tag ) );
		if( result.second ){
			return &result.first->second;
		}
		return NULL;
	}
	const FunctionTag* Find( const std::string& name ) const
	{
		iterConst it = m_Functions.find( name );
		if( it != m_Functions.end() ){
			return &it->second;
		}
		return NULL;
	}
	FunctionTag* Find( const std::string& name )
	{
		iter it = m_Functions.find( name );
		if( it != m_Functions.end() ){
			return &it->second;
		}
		return NULL;
	}
	void Clear()
	{
		m_Functions.clear();
	}
};

class Compiler
{
private:
	FunctionTable					m_Functions;
	std::vector < ValueTable >		m_Variables;
	std::vector < VMCode >			m_Statement;
	std::vector < Label >			m_Labels;
	std::vector < char >			m_TextTable;
	int								m_BreakIndex;
	int								m_ErrorCount;
	std::string						m_CurFunctionName;
	int								m_CurFunctionType;
	std::string						m_File;
	
	void ScanBegin();
	void ScanEnd();
public:
	Compiler();
	virtual ~Compiler();
	std::string& GetFileName()
	{
		return m_File;
	}
	bool Compile( const std::string& f, VM::Data& data );
#ifdef _DEBUG
	void DebugDump();
#endif
	bool AddFunction( int index, int type, const char* pName, const char* pArgs );
	void DefineValue( const yy::location& location, int type, ValueList* pValueList );
	void DefineFunction( const yy::location& location, int type, const std::string* pName,ArgList* pArgs );
	void AddFunction( const yy::location& location, int type, const std::string* pName, ArgList* pArgs, StateBlock* pState );
	// Search variables from internal blocks.
	const ValueTag* GetValueTag( const std::string& name ) const
	{
		int size = ( int ) m_Variables.size();
		for( int i = size - 1; i >= 0; --i ){
			const ValueTag* pTag = m_Variables[ i ].Find( name );
			if( pTag ){
				return pTag;
			}
		}
		return NULL;
	}
	const FunctionTag* GetFunctionTag( const std::string& name ) const
	{
		return m_Functions.Find( name );
	}

#define VM_CREATE
#include "VMCode.h"
#undef VM_CREATE

	void BlockIn();
	void BlockOut();
	void AllocStack();
	int LabelSetting();
	int SetBreakLabel( int label )
	{
		int oldIndex = m_BreakIndex;
		m_BreakIndex = label;
		return oldIndex;
	}
	void AddValue( const yy::location& location, int type, const std::string& name, const Node* pNode );
	void SetLabel( int label );
	void PushString( const std::string& name );
	int GetFunctionType() const
	{
		return m_CurFunctionType;
	}
	bool CreateData( VM::Data& data, int codeSize );
	void error( const yy::location& location, const std::string& m );
	void error( const std::string& m );
	int MakeLabel();
	bool JmpBreakLabel();

};


#endif
