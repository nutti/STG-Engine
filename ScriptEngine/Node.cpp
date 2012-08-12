#include <functional>
#include <iostream>
#include <iomanip>
#include "Node.h"
#include "Compiler.h"
#include "Parser.hh"

// Logical optimization.
Node* Node::MakeNode( Compiler& compiler, const yy::location& location, int op, Node* pLeft, Node* pRight )
{
	// Value - Null
	if( pRight == 0 ){
		switch( op ){
			case OP_NEG:
				if( pLeft->m_OP == OP_INT_CONST ){
					pLeft->m_Value = - pLeft->m_Value;
					return pLeft;
				}
				else if( pLeft->m_OP == OP_FLOAT_CONST ){
					pLeft->m_FValue = -pLeft->m_FValue;
					return pLeft;
				}
				break;
		}
		return new Node( location, op, pLeft );
	}

	// Value - Value
	if( pLeft->m_OP == OP_INT_CONST && pRight->m_OP == OP_INT_CONST ){
		switch( op ){
			case OP_LOGAND:
				pLeft->m_Value = ( pLeft->m_Value && pRight->m_Value ) ? 1 : 0;
				break;
			case OP_LOGOR:
				pLeft->m_Value = ( pLeft->m_Value || pRight->m_Value ) ? 1 : 0;
				break;
			case OP_EQ:
				pLeft->m_Value = ( pLeft->m_Value == pRight->m_Value ) ? 1 : 0;
				break;
			case OP_NE:
				pLeft->m_Value = ( pLeft->m_Value != pRight->m_Value ) ? 1 : 0;
				break;
			case OP_GT:
				pLeft->m_Value = ( pLeft->m_Value > pRight->m_Value ) ? 1 : 0;
				break;
			case OP_GE:
				pLeft->m_Value = ( pLeft->m_Value >= pRight->m_Value ) ? 1: 0;
				break;
			case OP_LT:
				pLeft->m_Value = ( pLeft->m_Value < pRight->m_Value ) ? 1: 0;
				break;
			case OP_LE:
				pLeft->m_Value = ( pLeft->m_Value <= pRight->m_Value ) ? 1: 0;
				break;
			case OP_AND:
				pLeft->m_Value &= pRight->m_Value;
				break;
			case OP_OR:
				pLeft->m_Value |= pRight->m_Value;
				break;
			case OP_LSHIFT:
				pLeft->m_Value <<= pRight->m_Value;
				break;
			case OP_RSHIFT:
				pLeft->m_Value >>= pRight->m_Value;
				break;
			case OP_MINUS:
				pLeft->m_Value -= pRight->m_Value;
				break;
			case OP_PLUS:
				pLeft->m_Value += pRight->m_Value;
				break;
			case OP_TIMES:
				pLeft->m_Value *= pRight->m_Value;
				break;
			case OP_DIVIDE:
				if( pRight->m_Value == 0 ){
					compiler.error( location, "Error : 0 division." );
				}
				else{
					pLeft->m_Value /= pRight->m_Value;
				}
				break;
			case OP_MOD:
				if( pRight->m_Value == 0 ){
					compiler.error( location, "Error : 0 division." );
				}
				else{
					pLeft->m_Value %= pRight->m_Value;
				}
				break;
			default:
				return new Node( location, op, pLeft, pRight );
		}
		delete pRight;
		return pLeft;
	}

	// FValue - FValue
	if( pLeft->m_OP == OP_FLOAT_CONST && pRight->m_OP == OP_FLOAT_CONST ){
		bool changeAble = false;
		int value = 0;
		switch( op ){
			case OP_EQ:
				value = ( pLeft->m_FValue == pRight->m_FValue ) ? 1 : 0;
				changeAble = true;
				break;
			case OP_NE:
				value = ( pLeft->m_FValue != pRight->m_FValue ) ? 1 : 0;
				changeAble = true;
				break;
			case OP_GT:
				value = ( pLeft->m_FValue > pRight->m_FValue ) ? 1 : 0;
				changeAble = true;
				break;
			case OP_GE:
				value = ( pLeft->m_FValue >= pRight->m_FValue ) ? 1: 0;
				changeAble = true;
				break;
			case OP_LT:
				value = ( pLeft->m_FValue < pRight->m_FValue ) ? 1: 0;
				changeAble = true;
				break;
			case OP_LE:
				value = ( pLeft->m_FValue <= pRight->m_FValue ) ? 1: 0;
				changeAble = true;
				break;
			case OP_MINUS:
				pLeft->m_FValue -= pRight->m_FValue;
				break;
			case OP_PLUS:
				pLeft->m_FValue += pRight->m_FValue;
				break;
			case OP_TIMES:
				pLeft->m_FValue *= pRight->m_FValue;
				break;
			case OP_DIVIDE:
				if( pRight->m_FValue == 0.0f ){
					compiler.error( location, "Error : 0 division." );
				}
				else{
					pLeft->m_FValue /= pRight->m_FValue;
				}
				break;
			default:
				compiler.error( location, "Invalid operations" );
				break;
		}
		delete pRight;
		if( changeAble ){
			delete pLeft;
			return new Node( location, OP_INT_CONST, value );
		}
		else{
			return pLeft;
		}
	}

	// String - String
	if( pLeft->m_OP == OP_STRING && pRight->m_OP == OP_STRING ){
		if( op == OP_PLUS ){
			*( pLeft->m_pString ) += *( pRight->m_pString );
			delete pRight;
			return pLeft;
		}

		int value = 0;
		switch( op ){
			case OP_EQ:
				if( *( pLeft->m_pString ) == *( pRight->m_pString ) ){
					value = 1;
				}
				break;
			case OP_NE:
				if( *( pLeft->m_pString ) == *( pRight->m_pString ) ){
					value = 1;
				}
				break;
			case OP_GT:
				if( *( pLeft->m_pString ) > *( pRight->m_pString ) ){
					value = 1;
				}
				break;
			case OP_GE:
				if( *( pLeft->m_pString ) >= *( pRight->m_pString ) ){
					value = 1;
				}
				break;
			case OP_LT:
				if( *( pLeft->m_pString ) < *( pRight->m_pString ) ){
					value = 1;
				}
				break;
			case OP_LE:
				if( *( pLeft->m_pString ) <= *( pRight->m_pString ) ){
					value = 1;
				}
				break;
			default:
				compiler.error( location, "Invalid operations" );
				break;
		}
		delete pLeft;
		delete pRight;
		return new Node( location, OP_INT_CONST, value );
	}
	return new Node( location, op, pLeft, pRight );
}

int Node::Push( Compiler* pCompiler ) const
{
	switch( m_OP ){
		case OP_NEG:{
			int ret = m_pLeft->Push( pCompiler );
			if( ret == TYPE_STRING ){
				pCompiler->error( m_Location, "'-' can not be used to string." );
			}
			if( ret == TYPE_FLOAT ){
				pCompiler->OpFNeg();
				return TYPE_FLOAT;
			}
			else{
				pCompiler->OpNeg();
				return TYPE_INTEGER;
			}
		}
		case OP_INT_CONST:
			pCompiler->PushConst( m_Value );
			return TYPE_INTEGER;
		case OP_FLOAT_CONST:
			pCompiler->PushConst( m_FValue );
			return TYPE_FLOAT;
		case OP_STRING:
			pCompiler->PushString( *m_pString );
			return TYPE_STRING;
	}

	int leftType = m_pLeft->Push( pCompiler );
	int rightType = m_pRight->Push( pCompiler );

	if( leftType != rightType ){
		pCompiler->error( m_Location, "Type is mismatched." );
	}

	// Integer operations.
	if( leftType == TYPE_INTEGER ){
		switch( m_OP ){
			case OP_LOGAND:
				pCompiler->OpLogAnd();
				break;
			case OP_LOGOR:
				pCompiler->OpLogOr();
				break;
			case OP_EQ:
				pCompiler->OpEq();
				break;
			case OP_NE:
				pCompiler->OpNe();
				break;
			case OP_GT:
				pCompiler->OpGt();
				break;
			case OP_GE:
				pCompiler->OpGe();
				break;
			case OP_LT:
				pCompiler->OpLt();
				break;
			case OP_LE:
				pCompiler->OpLe();
				break;
			case OP_AND:
				pCompiler->OpAnd();
				break;
			case OP_OR:
				pCompiler->OpOr();
				break;
			case OP_LSHIFT:
				pCompiler->OpLShift();
				break;
			case OP_RSHIFT:
				pCompiler->OpRShift();
				break;
			case OP_MINUS:
				pCompiler->OpSub();
				break;
			case OP_PLUS:
				pCompiler->OpAdd();
				break;
			case OP_TIMES:
				pCompiler->OpMul();
				break;
			case OP_DIVIDE:
				pCompiler->OpDiv();
				break;
			case OP_MOD:
				pCompiler->OpMod();
				break;
			default:
				pCompiler->error( m_Location, "Invalid operation." );
				break;
		}
		return TYPE_INTEGER;
	}

	// Float operation.
	if( leftType == TYPE_FLOAT ){
		int type;
		switch( m_OP ){
			case OP_EQ:
				pCompiler->OpFEq();
				type = TYPE_INTEGER;
				break;
			case OP_NE:
				pCompiler->OpFNe();
				type = TYPE_INTEGER;
				break;
			case OP_GT:
				pCompiler->OpFGt();
				type = TYPE_INTEGER;
				break;
			case OP_GE:
				pCompiler->OpFGe();
				type = TYPE_INTEGER;
				break;
			case OP_LT:
				pCompiler->OpFLt();
				type = TYPE_INTEGER;
				break;
			case OP_LE:
				pCompiler->OpFLe();
				type = TYPE_INTEGER;
				break;
			case OP_MINUS:
				pCompiler->OpFSub();
				type = TYPE_FLOAT;
				break;
			case OP_PLUS:
				pCompiler->OpFAdd();
				type = TYPE_FLOAT;
				break;
			case OP_TIMES:
				pCompiler->OpFMul();
				type = TYPE_FLOAT;
				break;
			case OP_DIVIDE:
				pCompiler->OpFDiv();
				type = TYPE_FLOAT;
				break;
			default:
				pCompiler->error( m_Location, "Invalid operation." );
				break;
		}
		return type;
	}

	// String operations.
	switch( m_OP ){
		case OP_EQ:
			pCompiler->OpStrEq();
			return TYPE_INTEGER;
		case OP_NE:
			pCompiler->OpStrNe();
			return TYPE_INTEGER;
		case OP_GT:
			pCompiler->OpStrGt();
			return TYPE_INTEGER;
		case OP_GE:
			pCompiler->OpStrGe();
			return TYPE_INTEGER;
		case OP_LT:
			pCompiler->OpStrLt();
			return TYPE_INTEGER;
		case OP_LE:
			pCompiler->OpStrLe();
			return TYPE_INTEGER;
		case OP_PLUS:
			pCompiler->OpStrAdd();
			break;
		default:
			pCompiler->error( m_Location, "Invalid operation." );
			break;
	}
	return TYPE_STRING;
}

int Node::Pop( Compiler* pCompiler ) const
{
	pCompiler->error( m_Location, "Invalid call" );
	return TYPE_INTEGER;
}

int ValueNode::Push( Compiler* pCompiler ) const
{
	if( m_OP != OP_VALUE ){
		pCompiler->error( m_Location, "Value is not registered." );
	}
	else{
		const ValueTag* pTag = pCompiler->GetValueTag( *m_pString );
		if( pTag == 0 ){
			pCompiler->error( m_Location, "Variable : " + *m_pString + " is not decleared." );
		}
		else{
			// Array or reference.
			if( pTag->m_Type >= TYPE_INTEGER_REF && pTag->m_Type != TYPE_FLOAT ){
				// Array.
				if( m_pLeft ){
					m_pLeft->Push( pCompiler );
					pCompiler->PushLocalArrayRef( pTag->m_Addr );
				}
				else{
					pCompiler->PushLocalRef( pTag->m_Addr );
				}
				return pTag->m_Type - TYPE_INTEGER_REF;
			}
			// Gloval variable.
			if( pTag->m_Global ){
				if( m_pLeft ){
					m_pLeft->Push( pCompiler );
					pCompiler->PushArray( pTag->m_Addr );
				}
				
				else{
					pCompiler->PushValue( pTag->m_Addr );
				}
			}
			// Local variable.
			else{
				if( m_pLeft ){
					m_pLeft->Push( pCompiler );
					pCompiler->PushLocalArray( pTag->m_Addr );
				}
				else{
					pCompiler->PushLocal( pTag->m_Addr );
				}
			}
			return pTag->m_Type;
		}
	}
	return TYPE_INTEGER;
}

int ValueNode::Pop( Compiler* pCompiler ) const
{
	if( m_OP != OP_VALUE ){
		pCompiler->error( m_Location, "Value is not registered." );
	}
	else{
		const ValueTag* pTag = pCompiler->GetValueTag( *m_pString );
		if( pTag == 0 ){
			pCompiler->error( m_Location, "Variable : " + *m_pString + " is not decleared." );
		}
		else{
			if( pTag->m_Type >= TYPE_INTEGER_REF && pTag->m_Type != TYPE_FLOAT ){
				// Array or reference.
				if( m_pLeft ){
					m_pLeft->Push( pCompiler );
					pCompiler->PopLocalArrayRef( pTag->m_Addr );
				}
				else{
					pCompiler->PopLocalRef( pTag->m_Addr );
				}
				return pTag->m_Type - TYPE_INTEGER_REF;
			}
			// Global variables
			if( pTag->m_Global ){
				if( m_pLeft ){
					m_pLeft->Push( pCompiler );
					pCompiler->PopArray( pTag->m_Addr );
				}
				else{
					pCompiler->PopValue( pTag->m_Addr );
				}
			}
			// Local variables
			else{
				if( m_pLeft ){
					m_pLeft->Push( pCompiler );
					pCompiler->PopLocalArray( pTag->m_Addr );
				}
				else{
					pCompiler->PopLocal( pTag->m_Addr );
				}
			}
			return pTag->m_Type;
		}
	}
	return TYPE_INTEGER;
}

struct SetArg
{
	Compiler*			m_pCompiler;
	const FunctionTag*	m_pFunc;
	mutable int			m_Index;
	SetArg( Compiler* pCompiler, const FunctionTag* pFunc ) :	m_pCompiler( pCompiler ),
																m_pFunc( pFunc ),
																m_Index( 0 )
	{
	}
	void operator()( Node* pNode ) const
	{
		int type = m_pFunc->GetArg( m_Index++ );
		if( type >= TYPE_INTEGER_REF && type != TYPE_FLOAT ){
			if( pNode->GetOP() != OP_VALUE ){
				m_pCompiler->error( pNode->GetLocation(), "Value is not registered." );
			}
			else{
				const ValueTag* pTag = m_pCompiler->GetValueTag( pNode->GetString() );
				if( pTag == 0 ){
					m_pCompiler->error( pNode->GetLocation(), "Variable : " + pNode->GetString() + " is not registered." );
				}
				// Reference
				else if( pTag->m_Type >= TYPE_INTEGER_REF && pTag->m_Type != TYPE_FLOAT ){
					if( pNode->GetLeft() ){
						pNode->GetLeft()->Push( m_pCompiler );
						m_pCompiler->PushLocal( pTag->m_Addr );
						m_pCompiler->OpAdd();
					}
					else{
						m_pCompiler->PushLocal( pTag->m_Addr );
					}
				}
				else{
					if( TypeToRef( pTag->m_Type ) != type ){
						m_pCompiler->error( pNode->GetLocation(), "Type is mismatched." );
					}
					int addr = pTag->m_Addr;
					// Global variable.
					if( pTag->m_Global ){
						addr |= VM::VCPU::GLOBAL_FLAG;
					}
					if( pNode->GetLeft() ){
						// Expression
						if( pNode->GetLeft()->GetOP() == OP_INT_CONST ){
							m_pCompiler->PushAddr( addr + pNode->GetLeft()->GetValue() );
						}
						// Array
						else{
							pNode->GetLeft()->Push( m_pCompiler );
							m_pCompiler->PushArrayAddr( addr );
						}
					}
					else{
						m_pCompiler->PushAddr( addr );
					}
				}
			}
		}
		else{
			if( pNode->Push( m_pCompiler ) != type ){
				m_pCompiler->error( pNode->GetLocation(), "Type is not correct." );
			}
		}
	}
};

int FunctionNode::Push( Compiler* pCompiler ) const
{
	const FunctionTag* pTag = pCompiler->GetFunctionTag( *m_pString );
	if( pTag == NULL ){
		pCompiler->error( m_Location, "Variable : " + *m_pString + " is not registered." );
	}
	
	int argSize = m_pArgs ? m_pArgs->Size() : 0;
	if( pTag->ArgSize() != argSize ){
		pCompiler->error( m_Location, "Size of argument is incorrect." );
	}

	// Push arguments.
	if( m_pArgs && pTag->ArgSize() == argSize ){
		m_pArgs->ForEach( SetArg( pCompiler, pTag ) );
	}

	// Push number of arguments.
	pCompiler->PushConst( argSize );

	// System call.
	if( pTag->IsSystem() ){
		pCompiler->OpSysCall( pTag->GetIndex() );
	}
	// Normal function call.
	else{
		pCompiler->OpCall( pTag->GetIndex() );
	}

	return pTag->m_Type;
}

int FunctionNode::Pop( Compiler* pCompiler ) const
{
	pCompiler->error( m_Location, "Invalid operation : pop." );
	return TYPE_INTEGER;
}

struct AddValue
{
	Compiler*	m_pCompiler;
	int			m_Type;
	AddValue( Compiler* pCompiler, int type ) : m_pCompiler( pCompiler ), m_Type( type )
	{
	}
	void operator()( ValueNode* pNode )
	{
		m_pCompiler->AddValue( pNode->GetLocation(), m_Type, pNode->GetString(), pNode->GetLeft() );
	}
};

void Decl::Analyze( Compiler* pCompiler )
{
	m_pValueList->ForEach( AddValue( pCompiler, m_Type ) );
}

// Assignment
// a = b -> push b, pop a
// a += b -> push a, push b, add, pop a
void Assign::Analyze( Compiler* pCompiler )
{
	if( m_OP != '=' ){
		m_pValue->Push( pCompiler );
	}

	int ret = m_pExpr->Push( pCompiler );

	if( ret == TYPE_INTEGER ){
		switch( m_OP ){
			case '+':
				pCompiler->OpAdd();
				break;
			case '-':
				pCompiler->OpSub();
				break;
			case '*':
				pCompiler->OpMul();
				break;
			case '/':
				pCompiler->OpDiv();
				break;
			case '%':
				pCompiler->OpMod();
				break;
		}
		if( m_pValue->Pop( pCompiler ) == TYPE_STRING ){
			pCompiler->error( m_Location, "Assign the string to integer." );
		}
		return;
	}
	if( ret == TYPE_FLOAT ){
		switch( m_OP ){
			case '+':
				pCompiler->OpFAdd();
				break;
			case '-':
				pCompiler->OpFSub();
				break;
			case '*':
				pCompiler->OpFMul();
				break;
			case '/':
				pCompiler->OpFDiv();
				break;
			case '%':
				pCompiler->error( m_Location, "Operation is invalid" );
				break;
		}
		if( m_pValue->Pop( pCompiler ) == TYPE_STRING ){
			pCompiler->error( m_Location, "Assign the string to integer." );
		}
		return;
	}

	switch( m_OP ){
		case '+':
			pCompiler->OpStrAdd();
			break;
		case '=':
			break;
		default:
			pCompiler->error( m_Location, "Invalid operations." );
			break;
	}
	
	if( m_pValue->Pop( pCompiler ) != TYPE_STRING ){
		pCompiler->error( m_Location, "Assign integer to string" );
	}
}

void StateBlock::Analyze( Compiler* pCompiler )
{
	// Define local variable.
	if( m_pDeclList ){
		m_pDeclList->ForEach( std::bind2nd( std::mem_fun( &Decl::Analyze ), pCompiler ) );
		pCompiler->AllocStack();
	}

	// Generate statement code.
	if( m_pStateList ){
		m_pStateList->ForEach( std::bind2nd( std::mem_fun( &Statement::Analyze ), pCompiler ) );
	}
}

void NopStatement::Analyze( Compiler* pCompiler )
{
	// No operations.
}

void AssignStatement::Analyze( Compiler* pCompiler )
{
	m_pAssign->Analyze( pCompiler );
}

void FunctionStatement::Analyze( Compiler* pCompiler )
{
	int type = m_Node.Push( pCompiler );		// Return value.
	if( type != TYPE_VOID ){
		pCompiler->OpPop();						// If return value type is void, return value is discarded.
	}
}

// If statement
// if( expr ) state		-> push expr, jmp_nc L1, A, L1:
// if( expr ) state		-> push expr, jmp_nc L1, A, jmp L2, L1:, B, L2:
void IfStatement::Analyze( Compiler* pCompiler )
{
	m_pExpr->Push( pCompiler );
	int label1 = pCompiler->MakeLabel();
	pCompiler->OpJmpNC( label1 );
	m_pThenStatement->Analyze( pCompiler );

	if( m_pElseStatement ){
		int label2 = pCompiler->MakeLabel();
		pCompiler->OpJmp( label2 );
		pCompiler->SetLabel( label1 );
		m_pElseStatement->Analyze( pCompiler );
		pCompiler->SetLabel( label2 );
	}
	else{
		pCompiler->SetLabel( label1 );
	}
}

// For statement.
// for( init; expr; next ) A	-> init, L1:, push expr, jmp_nc L2, A, next, jmp L1, L2:
void ForStatement::Analyze( Compiler* pCompiler )
{
	int label1 = pCompiler->MakeLabel();
	int label2 = pCompiler->MakeLabel();

	int labelBreak = pCompiler->SetBreakLabel( label2 );

	m_pInit->Analyze( pCompiler );
	pCompiler->SetLabel( label1 );
	m_pExpr->Push( pCompiler );
	pCompiler->OpJmpNC( label2 );
	m_pStatement->Analyze( pCompiler );
	m_pNext->Analyze( pCompiler );
	pCompiler->OpJmp( label1 );
	pCompiler->SetLabel( label2 );

	pCompiler->SetBreakLabel( labelBreak );
}

// While statement.
// while( expr ) A		-> L1:, push expr, jmp_nc L2, A, jmp L1, L2:
void WhileStatement::Analyze( Compiler* pCompiler )
{
	int label1 = pCompiler->MakeLabel();
	int label2 = pCompiler->MakeLabel();

	int breakLabel = pCompiler->SetBreakLabel( label2 );

	pCompiler->SetLabel( label1 );
	m_pExpr->Push( pCompiler );
	pCompiler->OpJmpNC( label2 );
	m_pStatement->Analyze( pCompiler );
	pCompiler->OpJmp( label1 );
	pCompiler->SetLabel( label2 );

	pCompiler->SetBreakLabel( breakLabel );
}

// Switch statement
// switch( expr ){
//		case A:
//			STATE_A
//			break;
//		case B:
//			STATE_B
//			break;
//		default:
//			STATE_C
//			break;
// }
//
//	push expr
//	push A
//	test L1
//	push B
//	test L2
//	pop
//	jmp L3
//	L1:
//		STATE_A
//		jmp L0
//	L2:
//		STATE_B
//		jmp L0
//	L3:
//		STATE_C
//		jmp L0
//	L0:
void SwitchStatement::Analyze( Compiler* pCompiler )
{
	m_pExpr->Push( pCompiler );

	printf( "\n\nkiojds" );

	if( m_pStateList ){
		int label = pCompiler->MakeLabel();
		int breakLabel = pCompiler->SetBreakLabel( label );
		int defaultLabel = label;

		printf( "\n\niojofei" );

		CaseActionParam param( pCompiler, defaultLabel );

		m_pStateList->ForEach( std::bind2nd( std::mem_fun( &Statement::AnalyzeCase ), &param ) );
		pCompiler->OpPop();
		pCompiler->OpJmp( defaultLabel );

		m_pStateList->ForEach( std::bind2nd( std::mem_fun( &Statement::Analyze ), pCompiler ) );
		pCompiler->SetLabel( label );

		pCompiler->SetBreakLabel( breakLabel );
	}
}

// Case statement
void CaseStatement::Analyze( Compiler* pCompiler )
{
	pCompiler->SetLabel( m_Label );
}

// Case statement
void CaseStatement::AnalyzeCase( CaseActionParam* pParam )
{
	Compiler* pCompiler = pParam->m_pCompiler;
	m_Label = pCompiler->MakeLabel();
	if( m_pExpr->GetOP() != OP_INT_CONST ){
		pCompiler->error( m_Location, "Invalid case parameter." );
	}
	m_pExpr->Push( pCompiler );
	pCompiler->OpTest( m_Label );
}

// Default statement
void DefaultStatement::Analyze( Compiler* pCompiler )
{
	pCompiler->SetLabel( m_Label );
}

// Default statement
void DefaultStatement::AnalyzeCase( CaseActionParam* pParam )
{
	m_Label = pParam->m_pCompiler->MakeLabel();
	pParam->m_DefaultLabel = m_Label;
}

// Break statement
void BreakStatement::Analyze( Compiler* pCompiler )
{
	if( !pCompiler->JmpBreakLabel() ){
		pCompiler->error( m_Location, "break is located at invalid position." );
	}
}

// Return statement
void ReturnStatement::Analyze( Compiler* pCompiler )
{
	if( pCompiler->GetFunctionType() == TYPE_VOID ){
		if( m_pExpr != 0 ){
			pCompiler->error( m_Location, "Return value is set on void return type." );
		}
		pCompiler->OpReturn();
	}
	else{
		if( m_pExpr == 0 ){
			pCompiler->error( m_Location, "Return value is not registered." );
		}
		else{
			int type = m_pExpr->Push( pCompiler );
			if( type != pCompiler->GetFunctionType() ){
				pCompiler->error( m_Location, "Function type and return value type is mismatched." );
			}
		}
		pCompiler->OpReturnV();
	}
}

void BlockStatement::Analyze( Compiler* pCompiler )
{
	pCompiler->BlockIn();
	m_pBlock->Analyze( pCompiler );
	pCompiler->BlockOut();
}







