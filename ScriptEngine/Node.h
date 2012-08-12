#ifndef INCLUDED_NODE_H
#define INCLUDED_NODE_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "location.hh"
//#include "vm.h"

class Compiler;
class Node;
class ValueNode;
class Decl;
class ArgDef;
class Statement;

// Node list
template < typename T >
class NodeList
{
private:
	std::vector < T* >	m_Nodes;	

	struct DeleteObject
	{
		void operator()( T* p )
		{
			delete p;
		}
	};

public:
	// Constructor
	NodeList( T* pNode )
	{
		m_Nodes.push_back( pNode );
	}
	// Destructor
	~NodeList()
	{
		std::for_each( m_Nodes.begin(), m_Nodes.end(), DeleteObject() );
	}
	// Add node.
	NodeList < T >* Add( T* pNode )
	{
		m_Nodes.push_back( pNode );
		return this;
	}
	// For each
	template < typename T2 >
	void ForEach( const T2& func )
	{
		std::for_each( m_Nodes.begin(), m_Nodes.end(), func );
	}
	// For each with reverse iteration.
	template < typename T2 >
	void ForEachReverse( const T2& func )
	{
		std::for_each( m_Nodes.rbegin(), m_Nodes.rend(), func );
	}
	// Get size.
	size_t Size() const { return m_Nodes.size(); }
	// Get contents.
	T* Get( size_t index ) { return m_Nodes[ index ]; }
	// Get contents.
	T* operator[]( size_t index ) { return m_Nodes[ index ]; }
	// Get contents.
	const T* Get( size_t index ) const { return m_Nodes[ index ]; }
	// Get contents.
	const T* operator[]( size_t index ) const { return m_Nodes[ index ]; }
};

typedef NodeList < Node >		Args;
typedef NodeList < ValueNode >		ValueList;
typedef NodeList < ArgDef >		ArgList;
typedef NodeList < Decl >		DeclList;
typedef NodeList < Statement >		StateList;

// Type information
enum
{
	TYPE_INTEGER = 0,		// Integer
	TYPE_STRING = 1,		// String
	TYPE_INTEGER_REF = 2,	// Reference to integer
	TYPE_STRING_REF = 3,	// Reference to string
	TYPE_FLOAT = 4,			// Float.
	TYPE_VOID = 5,		// Void
};

// Change to reference.
inline int TypeToRef( int type )
{
	return type + TYPE_INTEGER_REF - TYPE_INTEGER;
}

// Operations
enum
{
	OP_NEG,
	OP_PLUS,
	OP_MINUS,
	OP_TIMES,
	OP_DIVIDE,
	OP_MOD,
	OP_AND,
	OP_OR,
	OP_LSHIFT,
	OP_RSHIFT,
	OP_LOGAND,
	OP_LOGOR,
	OP_EQ,
	OP_NE,
	OP_GT,
	OP_GE,
	OP_LT,
	OP_LE,
	OP_VALUE,
	OP_CONST,
	OP_FLOAT_CONST,
	OP_INT_CONST,
	OP_STRING,
	OP_FUNCTION,
};

// Node class
class Node
{
protected:
	const yy::location	m_Location;
	int			m_OP;
	union{
		int			m_Value;
		float		m_FValue;
	};
	std::string*		m_pString;
	Node*			m_pLeft;
	Node*			m_pRight;
public:
	Node( const yy::location& location, int op, Node* pLeft, Node* pRight = 0 ) :	m_Location( location ),
																					m_OP( op ), m_Value( 0 ),
																					m_pString( 0 ), m_pLeft( pLeft ),
																					m_pRight( pRight )
	{
	}
	Node( const yy::location& location, int op, int value ) :	m_Location( location ),
																m_OP( op ), m_Value( value ),
																m_pString( 0 ),
																m_pLeft( 0 ), m_pRight( 0 )
	{
	}
	Node( const yy::location& location, int op, float value ) :	m_Location( location ),
																m_OP( op ),
																m_FValue( value ),
																m_pString( 0 ),
																m_pLeft( 0 ),
																m_pRight( 0 )
	{
	}
	Node( const yy::location& location, int op, std::string* pStr ) :	m_Location( location ),
																		m_OP( op ),
																		m_Value( 0 ), m_pString( pStr ),
																		m_pLeft( 0 ), m_pRight( 0 )
	{
	}
	Node( const yy::location& location, int op, std::string* pStr, Node* pNode ) :	m_Location( location ),
																					m_OP( op ),
																					m_Value( 0 ), m_pString( pStr ),
																					m_pLeft( pNode ), m_pRight( 0 )
	{
	}
	virtual ~Node()
	{
		delete m_pLeft;
		delete m_pRight;
		delete m_pString;
	}
	virtual int Push( Compiler* pCompiler ) const;
	virtual int Pop( Compiler* pCompiler ) const;

	const yy::location& GetLocation() const { return m_Location; }
	int GetOP() const { return m_OP; }
	int GetValue() const { return m_Value; }
	const std::string& GetString() const { return *m_pString; }
	const Node* GetLeft() const { return m_pLeft; }
	const Node* GetRight() const { return m_pRight; }

	static Node* MakeNode( Compiler& pCompiler, const yy::location& location, int op, Node* pLeft, Node* pRight = 0 );
};

class ValueNode : public Node
{
public:
	ValueNode( const yy::location& location, std::string* pName, Node* pNode = NULL ) :	Node( location, OP_VALUE, pName, pNode )
	{
	}
	int Push( Compiler* pCompiler ) const;
	int Pop( Compiler* pCompiler ) const;
};

class FunctionNode : public Node
{
private:
	Args*	m_pArgs;
public:
	FunctionNode( const yy::location& location, std::string* pName, Args* pArgs ) : Node( location, OP_FUNCTION, pName ), m_pArgs( pArgs )
	{
	}
	~FunctionNode()
	{
		delete m_pArgs;
	}
	int Push( Compiler* pCompiler ) const;
	int Pop( Compiler* pCompiler ) const;
};

class Assign
{
private:
	const yy::location	m_Location;
	int					m_OP;
	Node*				m_pValue;
	Node*				m_pExpr;
public:
	Assign( const yy::location& location, int op, Node* pValue, Node* pExpr ) :	m_Location( location ),
																				m_OP( op ),
																				m_pValue( pValue ),
																				m_pExpr( pExpr )
	{
	}
	~Assign()
	{
		delete m_pValue;
		delete m_pExpr;
	}
	void Analyze( Compiler* pCompiler );
};

class ArgDef
{
private:
	const yy::location		m_Location;
	int						m_Type;
	const std::string*		m_pName;
public:
	ArgDef( const yy::location& location, int type, const std::string* pName ) :	m_Location( location ),
																					m_Type( type ),
																					m_pName( pName )
	{
	}
	~ArgDef()
	{
		delete m_pName;
	}
	const yy::location& GetLocation() const { return m_Location; }
	int GetType() const { return m_Type; }
	const std::string& GetName() const { return *m_pName; }
};

class Decl
{
private:
	int			m_Type;
	ValueList*	m_pValueList;
public:
	Decl( int type, ValueList* pValueList ) :	m_Type( type ), m_pValueList( pValueList )
	{
	}
	~Decl()
	{
		delete m_pValueList;
	}
	void Analyze( Compiler* pCompiler );
};

class StateBlock
{
private:
	DeclList*		m_pDeclList;
	StateList*		m_pStateList;
public:
	StateBlock( DeclList* pDeclList, StateList* pStateList ) :	m_pDeclList( pDeclList ),
																m_pStateList( pStateList )
	{
	}
	~StateBlock()
	{
		delete m_pDeclList;
		delete m_pStateList;
	}
	void Analyze( Compiler* pCompiler );
};

struct CaseActionParam
{
	Compiler*	m_pCompiler;
	int&		m_DefaultLabel;
	CaseActionParam( Compiler* pCompiler, int& defaultLabel ) :	m_pCompiler( pCompiler ),
																m_DefaultLabel( defaultLabel )
	{
	}
};


class Statement
{
protected:
	const yy::location		m_Location;
	int						m_Code;
public:

	enum
	{
		NOP,
		ASSIGN,
		FUNCTION,
		IF,
		FOR,
		WHILE,
		SWITCH,
		CASE,
		DEFAULT,
		BREAK,
		RETURN,
		BLOCK,
	};

	Statement( const yy::location& location, int code ) :	m_Location( location ),
															m_Code( code )
	{
	}
	virtual ~Statement()
	{
	}
	virtual void Analyze( Compiler* pCompiler ) = 0;
	virtual void AnalyzeCase( CaseActionParam* pParam )
	{
	}
};


class NopStatement : public Statement
{
public:
	NopStatement( const yy::location& location ) :	Statement( location, NOP )
	{
	}
	virtual void Analyze( Compiler* pCompiler );
};


class AssignStatement : public Statement
{
private:
	Assign*		m_pAssign;
public:
	AssignStatement( const yy::location& location, Assign* pAssign ) :	Statement( location, ASSIGN ),
																		m_pAssign( pAssign )
	{
	}
	~AssignStatement()
	{
		delete m_pAssign;
	}
	virtual void Analyze( Compiler* pCompiler );
};


class FunctionStatement : public Statement
{
private:
	FunctionNode	m_Node;
public:
	FunctionStatement( const yy::location& location, std::string* pName, Args* pArgs ) :	Statement( location, FUNCTION ),
																							m_Node( location, pName, pArgs )
	{
	}
	~FunctionStatement()
	{
	}
	virtual void Analyze( Compiler* pCompiler );
};


class IfStatement : public Statement
{
private:
	Node*			m_pExpr;
	Statement*		m_pThenStatement;
	Statement*		m_pElseStatement;
public:
	IfStatement(	const yy::location& location,
					Node* pExpr,
					Statement* pThenStatement,
					Statement* pElseStatement = NULL ) :	Statement( location, IF ),
															m_pExpr( pExpr ),
															m_pThenStatement( pThenStatement ),
															m_pElseStatement( pElseStatement )
	{
	}
	~IfStatement()
	{
		delete m_pExpr;
		delete m_pThenStatement;
		delete m_pElseStatement;
	}
	virtual void Analyze( Compiler* pCompiler );
};

class ForStatement : public Statement
{
private:
	Assign*		m_pInit;
	Node*		m_pExpr;
	Assign*		m_pNext;
	Statement*	m_pStatement;
public:
	ForStatement(	const yy::location& location,
					Assign* pInit,
					Node* pExpr,
					Assign* pNext,
					Statement* pStatement ) :	Statement( location, FOR ),
												m_pInit( pInit ),
												m_pExpr( pExpr ),
												m_pNext( pNext ),
												m_pStatement( pStatement )
	{
	}
	~ForStatement()
	{
		delete m_pInit;
		delete m_pExpr;
		delete m_pNext;
		delete m_pStatement;
	}
	virtual void Analyze( Compiler* pCompiler );
};


class WhileStatement : public Statement
{
private:
	Node*			m_pExpr;
	Statement*		m_pStatement;
public:
	WhileStatement(	const yy::location& location,
					Node* pExpr,
					Statement* pStatement ) :	Statement( location, WHILE ),
												m_pExpr( pExpr ),
												m_pStatement( pStatement )
	{
	}
	~WhileStatement()
	{
		delete m_pExpr;
		delete m_pStatement;
	}
	virtual void Analyze( Compiler* pCompiler );
};

class SwitchStatement : public Statement
{
private:
	Node*		m_pExpr;
	StateList*	m_pStateList;
public:
	SwitchStatement( const yy::location& location, Node* pExpr, StateList* pStateList ) :	Statement( location, SWITCH ),
																							m_pExpr( pExpr ),
																							m_pStateList( pStateList )
	{
	}
	~SwitchStatement()
	{
		delete m_pExpr;
		delete m_pStateList;
	}
	virtual void Analyze( Compiler* pCompiler );
};

class CaseStatement : public Statement
{
private:
	Node*		m_pExpr;
	int			m_Label;
public:
	CaseStatement( const yy::location& location, Node* pExpr ) : Statement( location, CASE ), m_pExpr( pExpr )
	{
	}
	~CaseStatement()
	{
		delete m_pExpr;
	}
	virtual void Analyze( Compiler* pCompiler );
	virtual void AnalyzeCase( CaseActionParam* pParam );
};

class DefaultStatement : public Statement
{
private:
	int			m_Label;
public:
	DefaultStatement( const yy::location& location ) : Statement( location, DEFAULT )
	{
	}
	virtual void Analyze( Compiler* pCompiler );
	virtual void AnalyzeCase( CaseActionParam* pParam );
};


class BreakStatement : public Statement
{
public:
	BreakStatement( const yy::location& l ) : Statement( l, BREAK )
	{
	}
	virtual void Analyze( Compiler* pCompiler );
};


class ReturnStatement : public Statement
{
private:
	Node*	m_pExpr;
public:
	ReturnStatement( const yy::location& location, Node* pExpr ) :	Statement( location, RETURN ),
																	m_pExpr( pExpr )
	{
	}
	~ReturnStatement()
	{
		delete m_pExpr;
	}
	virtual void Analyze( Compiler* pCompiler );
};


class BlockStatement : public Statement
{
private:
	StateBlock*		m_pBlock;
public:
	BlockStatement( const yy::location& location, StateBlock* pBlock ) :	Statement( location, BLOCK ),
																			m_pBlock( pBlock )
	{
	}
	~BlockStatement()
	{
		delete m_pBlock;
	}
	virtual void Analyze( Compiler* pCompiler );
};


#endif
