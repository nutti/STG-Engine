#ifdef VM_ENUMDEF
#define VMCODE0( code, name )	code,
#define VMCODE1( code, name )	code,
#define VMCODE2( code, name )	code,
#endif

#ifdef VM_CREATE
#define VMCODE0( code, name )	void name()				{ m_Statement.push_back( VMCode( code ) ); }
#define VMCODE1( code, name )	void name( int arg1 )	{ m_Statement.push_back( VMCode( code, arg1 ) ); } \
								void name( float arg1 )	{ m_Statement.push_back( VMCode( code, arg1 ) ); }
#define VMCODE2( code, name )	void name()				{ m_Statement.push_back( VMCode( code ) ); }
#endif

#ifdef VM_SWITCHTABLE
#define VMCODE0( code, name )	case code: name(); break;
#define VMCODE1( code, name )	case code: name( Value() ); break;
#define VMCODE2( code, name )	case code: name(); break;
#endif

#ifdef VM_NAMETABLE
#define VMCODE0( code, name )	#name,
#define VMCODE1( code, name )	#name,
#define VMCODE2( code, name )	#name,
#endif

VMCODE1( VM_PUSHCONST,				PushConst )
VMCODE1( VM_PUSHSTRING,				PushString )
VMCODE1( VM_PUSHVALUE,				PushValue )
VMCODE1( VM_PUSHLOCAL,				PushLocal )
VMCODE1( VM_PUSHARRAY,				PushArray )
VMCODE1( VM_PUSHLOCALARRAY,			PushLocalArray )
VMCODE1( VM_PUSHLOCALREF,			PushLocalRef )
VMCODE1( VM_PUSHLOCALARRAYREF,		PushLocalArrayRef )
VMCODE1( VM_PUSHADDR,				PushAddr )
VMCODE1( VM_PUSHARRAYADDR,			PushArrayAddr )
VMCODE1( VM_POPVALUE,				PopValue )
VMCODE1( VM_POPLOCAL,				PopLocal )
VMCODE1( VM_POPARRAY,				PopArray )
VMCODE1( VM_POPLOCALARRAY,			PopLocalArray )
VMCODE1( VM_POPLOCALREF,			PopLocalRef )
VMCODE1( VM_POPLOCALARRAYREF,		PopLocalArrayRef )
VMCODE1( VM_ALLOCSTACK,				OpAllocStack )
VMCODE0( VM_POP,					OpPop )
VMCODE2( VM_NEG,					OpNeg )
VMCODE0( VM_EQ,						OpEq )
VMCODE0( VM_NE,						OpNe )
VMCODE0( VM_GT,						OpGt )
VMCODE0( VM_GE,						OpGe )
VMCODE0( VM_LT,						OpLt )
VMCODE0( VM_LE,						OpLe )
VMCODE0( VM_LOGAND,					OpLogAnd )
VMCODE0( VM_LOGOR,					OpLogOr )
VMCODE0( VM_AND,					OpAnd )
VMCODE0( VM_OR,						OpOr )
VMCODE0( VM_LSHIFT,					OpLShift )
VMCODE0( VM_RSHIFT,					OpRShift )
VMCODE0( VM_ADD,					OpAdd )
VMCODE0( VM_SUB,					OpSub )
VMCODE0( VM_MUL,					OpMul )
VMCODE0( VM_DIV,					OpDiv )
VMCODE0( VM_MOD,					OpMod )
VMCODE0( VM_STREQ,					OpStrEq )
VMCODE0( VM_STRNE,					OpStrNe )
VMCODE0( VM_STRGT,					OpStrGt )
VMCODE0( VM_STRGE,					OpStrGe )
VMCODE0( VM_STRLT,					OpStrLt )
VMCODE0( VM_STRLE,					OpStrLe )
VMCODE0( VM_STRADD,					OpStrAdd )
VMCODE1( VM_JMP,					OpJmp )
VMCODE1( VM_JMPC,					OpJmpC )
VMCODE1( VM_JMPNC,					OpJmpNC )
VMCODE1( VM_TEST,					OpTest )
VMCODE1( VM_CALL,					OpCall )
VMCODE1( VM_SYSCALL,				OpSysCall )
VMCODE0( VM_RETURN,					OpReturn )
VMCODE0( VM_RETURNV,				OpReturnV )
VMCODE0( VM_HALT,					OpHalt )

VMCODE2( VM_FNEG,					OpFNeg )
VMCODE0( VM_FEQ,						OpFEq )
VMCODE0( VM_FNE,						OpFNe )
VMCODE0( VM_FGT,						OpFGt )
VMCODE0( VM_FGE,						OpFGe )
VMCODE0( VM_FLT,						OpFLt )
VMCODE0( VM_FLE,						OpFLe )
VMCODE0( VM_FADD,					OpFAdd )
VMCODE0( VM_FSUB,					OpFSub )
VMCODE0( VM_FMUL,					OpFMul )
VMCODE0( VM_FDIV,					OpFDiv )

#undef VMCODE0
#undef VMCODE1
#undef VMCODE2
