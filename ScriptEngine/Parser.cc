
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 4 "Parser.yy"

	#include <string>
	#include "Node.h"
	class Compiler;


/* Line 311 of lalr1.cc  */
#line 48 "Parser.cc"


#include "Parser.hh"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 38 "Parser.yy"

#include "Compiler.h"


/* Line 317 of lalr1.cc  */
#line 62 "Parser.cc"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace yy {

/* Line 380 of lalr1.cc  */
#line 131 "Parser.cc"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  Parser::Parser (Compiler& compiler_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      compiler (compiler_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 4: /* "\"identifier\"" */

/* Line 480 of lalr1.cc  */
#line 97 "Parser.yy"
	{ delete (yyvaluep->m_pStrVal); };

/* Line 480 of lalr1.cc  */
#line 238 "Parser.cc"
	break;
      case 5: /* "\"sval\"" */

/* Line 480 of lalr1.cc  */
#line 98 "Parser.yy"
	{ delete (yyvaluep->m_pStrVal); };

/* Line 480 of lalr1.cc  */
#line 247 "Parser.cc"
	break;
      case 54: /* "vallist" */

/* Line 480 of lalr1.cc  */
#line 99 "Parser.yy"
	{ delete (yyvaluep->m_pValueList); };

/* Line 480 of lalr1.cc  */
#line 256 "Parser.cc"
	break;
      case 55: /* "arglist" */

/* Line 480 of lalr1.cc  */
#line 100 "Parser.yy"
	{ delete (yyvaluep->m_pArgList); };

/* Line 480 of lalr1.cc  */
#line 265 "Parser.cc"
	break;
      case 56: /* "argdef" */

/* Line 480 of lalr1.cc  */
#line 101 "Parser.yy"
	{ delete (yyvaluep->m_pArgDef); };

/* Line 480 of lalr1.cc  */
#line 274 "Parser.cc"
	break;
      case 59: /* "block" */

/* Line 480 of lalr1.cc  */
#line 105 "Parser.yy"
	{ delete (yyvaluep->m_pBlock); };

/* Line 480 of lalr1.cc  */
#line 283 "Parser.cc"
	break;
      case 60: /* "decllist" */

/* Line 480 of lalr1.cc  */
#line 102 "Parser.yy"
	{ delete (yyvaluep->m_pDeclList); };

/* Line 480 of lalr1.cc  */
#line 292 "Parser.cc"
	break;
      case 61: /* "statelist" */

/* Line 480 of lalr1.cc  */
#line 103 "Parser.yy"
	{ delete (yyvaluep->m_pStateList); };

/* Line 480 of lalr1.cc  */
#line 301 "Parser.cc"
	break;
      case 62: /* "decls" */

/* Line 480 of lalr1.cc  */
#line 102 "Parser.yy"
	{ delete (yyvaluep->m_pDeclList); };

/* Line 480 of lalr1.cc  */
#line 310 "Parser.cc"
	break;
      case 63: /* "states" */

/* Line 480 of lalr1.cc  */
#line 103 "Parser.yy"
	{ delete (yyvaluep->m_pStateList); };

/* Line 480 of lalr1.cc  */
#line 319 "Parser.cc"
	break;
      case 64: /* "statement" */

/* Line 480 of lalr1.cc  */
#line 107 "Parser.yy"
	{ delete (yyvaluep->m_pStatement); };

/* Line 480 of lalr1.cc  */
#line 328 "Parser.cc"
	break;
      case 65: /* "assign" */

/* Line 480 of lalr1.cc  */
#line 106 "Parser.yy"
	{ delete (yyvaluep->m_pAssign); };

/* Line 480 of lalr1.cc  */
#line 337 "Parser.cc"
	break;
      case 66: /* "expr" */

/* Line 480 of lalr1.cc  */
#line 109 "Parser.yy"
	{ delete (yyvaluep->m_pExpr); };

/* Line 480 of lalr1.cc  */
#line 346 "Parser.cc"
	break;
      case 67: /* "value" */

/* Line 480 of lalr1.cc  */
#line 108 "Parser.yy"
	{ delete (yyvaluep->m_pVal); };

/* Line 480 of lalr1.cc  */
#line 355 "Parser.cc"
	break;
      case 68: /* "args" */

/* Line 480 of lalr1.cc  */
#line 104 "Parser.yy"
	{ delete (yyvaluep->m_pArgs); };

/* Line 480 of lalr1.cc  */
#line 364 "Parser.cc"
	break;

	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 553 of lalr1.cc  */
#line 14 "Parser.yy"
{
	/* Initialize locations */
	yylloc.begin.filename = yylloc.end.filename = &compiler.GetFileName();
}

/* Line 553 of lalr1.cc  */
#line 450 "Parser.cc"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, compiler);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 7:

/* Line 678 of lalr1.cc  */
#line 137 "Parser.yy"
    { compiler.DefineValue( (yylocation_stack_[(3) - (2)]), (yysemantic_stack_[(3) - (1)].m_Type), (yysemantic_stack_[(3) - (2)].m_pValueList) ); }
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 138 "Parser.yy"
    { compiler.DefineFunction( (yylocation_stack_[(5) - (2)]), (yysemantic_stack_[(5) - (1)].m_Type), (yysemantic_stack_[(5) - (2)].m_pStrVal), NULL ); }
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 139 "Parser.yy"
    { compiler.DefineFunction( (yylocation_stack_[(6) - (2)]), (yysemantic_stack_[(6) - (1)].m_Type), (yysemantic_stack_[(6) - (2)].m_pStrVal), (yysemantic_stack_[(6) - (4)].m_pArgList) ); }
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 140 "Parser.yy"
    { compiler.DefineFunction( (yylocation_stack_[(5) - (2)]), TYPE_VOID, (yysemantic_stack_[(5) - (2)].m_pStrVal), NULL ); }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 141 "Parser.yy"
    { compiler.DefineFunction( (yylocation_stack_[(6) - (2)]), TYPE_VOID, (yysemantic_stack_[(6) - (2)].m_pStrVal), (yysemantic_stack_[(6) - (4)].m_pArgList) ); }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 144 "Parser.yy"
    { (yyval.m_pValueList) = new ValueList( (yysemantic_stack_[(1) - (1)].m_pVal) ); }
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 145 "Parser.yy"
    { (yyval.m_pValueList) = (yysemantic_stack_[(3) - (1)].m_pValueList)->Add( (yysemantic_stack_[(3) - (3)].m_pVal) ); }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 148 "Parser.yy"
    { (yyval.m_pArgList) = new ArgList( (yysemantic_stack_[(1) - (1)].m_pArgDef) ); }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 149 "Parser.yy"
    { (yyval.m_pArgList) = (yysemantic_stack_[(3) - (1)].m_pArgList)->Add( (yysemantic_stack_[(3) - (3)].m_pArgDef) ); }
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 152 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].m_Type), NULL ); }
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 153 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(2) - (1)]), TypeToRef( (yysemantic_stack_[(2) - (1)].m_Type) ), NULL ); }
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 154 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(2) - (1)]), (yysemantic_stack_[(2) - (1)].m_Type), (yysemantic_stack_[(2) - (2)].m_pStrVal) ); }
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 155 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(3) - (1)]), TypeToRef( (yysemantic_stack_[(3) - (1)].m_Type) ), (yysemantic_stack_[(3) - (3)].m_pStrVal) ); }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 156 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(4) - (1)]), TypeToRef( (yysemantic_stack_[(4) - (1)].m_Type) ), (yysemantic_stack_[(4) - (2)].m_pStrVal) ); }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 157 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(5) - (1)]), TypeToRef( (yysemantic_stack_[(5) - (1)].m_Type) ), (yysemantic_stack_[(5) - (3)].m_pStrVal) ); }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 160 "Parser.yy"
    { compiler.AddFunction( (yylocation_stack_[(5) - (1)]), (yysemantic_stack_[(5) - (1)].m_Type), (yysemantic_stack_[(5) - (2)].m_pStrVal), NULL, (yysemantic_stack_[(5) - (5)].m_pBlock) ); }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 161 "Parser.yy"
    { compiler.AddFunction( (yylocation_stack_[(6) - (1)]), (yysemantic_stack_[(6) - (1)].m_Type), (yysemantic_stack_[(6) - (2)].m_pStrVal), (yysemantic_stack_[(6) - (4)].m_pArgList), (yysemantic_stack_[(6) - (6)].m_pBlock) ); }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 162 "Parser.yy"
    { compiler.AddFunction( (yylocation_stack_[(5) - (1)]), TYPE_VOID, (yysemantic_stack_[(5) - (2)].m_pStrVal), NULL, (yysemantic_stack_[(5) - (5)].m_pBlock) ); }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 163 "Parser.yy"
    { compiler.AddFunction( (yylocation_stack_[(6) - (1)]), TYPE_VOID, (yysemantic_stack_[(6) - (2)].m_pStrVal), (yysemantic_stack_[(6) - (4)].m_pArgList), (yysemantic_stack_[(6) - (6)].m_pBlock) ); }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 166 "Parser.yy"
    { (yyval.m_Type) = TYPE_INTEGER; }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 167 "Parser.yy"
    { (yyval.m_Type) = TYPE_STRING; }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 170 "Parser.yy"
    { (yyval.m_pBlock) = new StateBlock( (yysemantic_stack_[(4) - (2)].m_pDeclList), (yysemantic_stack_[(4) - (3)].m_pStateList) ); }
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 173 "Parser.yy"
    { (yyval.m_pDeclList) = NULL; }
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 174 "Parser.yy"
    { (yyval.m_pDeclList) = (yysemantic_stack_[(1) - (1)].m_pDeclList); }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 177 "Parser.yy"
    { (yyval.m_pStateList) = NULL; }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 178 "Parser.yy"
    { (yyval.m_pStateList) = (yysemantic_stack_[(1) - (1)].m_pStateList); }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 181 "Parser.yy"
    { (yyval.m_pDeclList) = new DeclList( new Decl( (yysemantic_stack_[(3) - (1)].m_Type), (yysemantic_stack_[(3) - (2)].m_pValueList) ) ); }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 182 "Parser.yy"
    { (yyval.m_pDeclList) = (yysemantic_stack_[(4) - (1)].m_pDeclList)->Add( new Decl( (yysemantic_stack_[(4) - (2)].m_Type), (yysemantic_stack_[(4) - (3)].m_pValueList) ) ); }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 185 "Parser.yy"
    { (yyval.m_pStateList) = new StateList( (yysemantic_stack_[(1) - (1)].m_pStatement) ); }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 186 "Parser.yy"
    { (yyval.m_pStateList) = (yysemantic_stack_[(2) - (1)].m_pStateList)->Add( (yysemantic_stack_[(2) - (2)].m_pStatement) ); }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 189 "Parser.yy"
    { (yyval.m_pStatement) = new NopStatement( (yylocation_stack_[(1) - (1)]) ); }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 190 "Parser.yy"
    { (yyval.m_pStatement) = new AssignStatement( (yylocation_stack_[(2) - (1)]), (yysemantic_stack_[(2) - (1)].m_pAssign) ); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 191 "Parser.yy"
    { (yyval.m_pStatement) = new FunctionStatement( (yylocation_stack_[(5) - (1)]), (yysemantic_stack_[(5) - (1)].m_pStrVal), (yysemantic_stack_[(5) - (3)].m_pArgs) ); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 192 "Parser.yy"
    { (yyval.m_pStatement) = new FunctionStatement( (yylocation_stack_[(4) - (1)]), (yysemantic_stack_[(4) - (1)].m_pStrVal), NULL ); }
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 193 "Parser.yy"
    { (yyval.m_pStatement) = new CaseStatement( (yylocation_stack_[(3) - (1)]), (yysemantic_stack_[(3) - (2)].m_pExpr) ); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 194 "Parser.yy"
    { (yyval.m_pStatement) = new DefaultStatement( (yylocation_stack_[(2) - (1)]) ); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 195 "Parser.yy"
    { (yyval.m_pStatement) = new BreakStatement( (yylocation_stack_[(2) - (1)]) ); }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 196 "Parser.yy"
    { (yyval.m_pStatement) = new ReturnStatement( (yylocation_stack_[(2) - (1)]), NULL ); }
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 197 "Parser.yy"
    { (yyval.m_pStatement) = new ReturnStatement( (yylocation_stack_[(3) - (1)]), (yysemantic_stack_[(3) - (2)].m_pExpr) ); }
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 198 "Parser.yy"
    { (yyval.m_pStatement) = new IfStatement( (yylocation_stack_[(5) - (1)]), (yysemantic_stack_[(5) - (3)].m_pExpr), (yysemantic_stack_[(5) - (5)].m_pStatement) ); }
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 199 "Parser.yy"
    { (yyval.m_pStatement) = new IfStatement( (yylocation_stack_[(7) - (1)]), (yysemantic_stack_[(7) - (3)].m_pExpr), (yysemantic_stack_[(7) - (5)].m_pStatement), (yysemantic_stack_[(7) - (7)].m_pStatement) ); }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 200 "Parser.yy"
    { (yyval.m_pStatement) = new ForStatement( (yylocation_stack_[(9) - (1)]), (yysemantic_stack_[(9) - (3)].m_pAssign), (yysemantic_stack_[(9) - (5)].m_pExpr), (yysemantic_stack_[(9) - (7)].m_pAssign), (yysemantic_stack_[(9) - (9)].m_pStatement) ); }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 201 "Parser.yy"
    { (yyval.m_pStatement) = new WhileStatement( (yylocation_stack_[(5) - (1)]), (yysemantic_stack_[(5) - (3)].m_pExpr), (yysemantic_stack_[(5) - (5)].m_pStatement) ); }
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 202 "Parser.yy"
    { (yyval.m_pStatement) = new SwitchStatement( (yylocation_stack_[(7) - (1)]), (yysemantic_stack_[(7) - (3)].m_pExpr), (yysemantic_stack_[(7) - (6)].m_pStateList) ); }
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 203 "Parser.yy"
    { (yyval.m_pStatement) = new BlockStatement( (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].m_pBlock) ); }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 206 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '=', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 207 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '+', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 208 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '-', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 209 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '*', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 210 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '/', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 211 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '%', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 214 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LOGAND, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 215 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LOGOR, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 216 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_EQ, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 217 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_NE, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 218 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_GT, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 219 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_GE, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 220 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LT, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 221 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LE, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 66:

/* Line 678 of lalr1.cc  */
#line 222 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_AND, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 223 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_OR, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 224 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LSHIFT, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 225 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_RSHIFT, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 226 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_MINUS, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 227 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_PLUS, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 228 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_TIMES, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 229 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_DIVIDE, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 230 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_MOD, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 231 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(2) - (2)]), OP_NEG, (yysemantic_stack_[(2) - (2)].m_pExpr) ); }
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 232 "Parser.yy"
    { (yyval.m_pExpr) = (yysemantic_stack_[(3) - (2)].m_pExpr); }
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 233 "Parser.yy"
    { (yyval.m_pExpr) = (yysemantic_stack_[(1) - (1)].m_pVal); }
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 234 "Parser.yy"
    { (yyval.m_pExpr) = new Node( (yylocation_stack_[(1) - (1)]), OP_CONST, (yysemantic_stack_[(1) - (1)].m_IntVal) ); }
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 235 "Parser.yy"
    { (yyval.m_pExpr) = new Node( (yylocation_stack_[(1) - (1)]), OP_STRING, (yysemantic_stack_[(1) - (1)].m_pStrVal) ); }
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 236 "Parser.yy"
    { (yyval.m_pExpr) = new FunctionNode( (yylocation_stack_[(4) - (1)]), (yysemantic_stack_[(4) - (1)].m_pStrVal), (yysemantic_stack_[(4) - (3)].m_pArgs) ); }
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 237 "Parser.yy"
    { (yyval.m_pExpr) = new FunctionNode( (yylocation_stack_[(3) - (1)]), (yysemantic_stack_[(3) - (1)].m_pStrVal), NULL ); }
    break;

  case 82:

/* Line 678 of lalr1.cc  */
#line 240 "Parser.yy"
    { (yyval.m_pVal) = new ValueNode( (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].m_pStrVal) ); }
    break;

  case 83:

/* Line 678 of lalr1.cc  */
#line 241 "Parser.yy"
    { (yyval.m_pVal) = new ValueNode( (yylocation_stack_[(4) - (1)]), (yysemantic_stack_[(4) - (1)].m_pStrVal), (yysemantic_stack_[(4) - (3)].m_pExpr) ); }
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 244 "Parser.yy"
    { (yyval.m_pArgs) = new Args( (yysemantic_stack_[(1) - (1)].m_pExpr) ); }
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 245 "Parser.yy"
    { (yyval.m_pArgs) = (yysemantic_stack_[(3) - (1)].m_pArgs)->Add( (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;



/* Line 678 of lalr1.cc  */
#line 1122 "Parser.cc"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char Parser::yypact_ninf_ = -121;
  const short int
  Parser::yypact_[] =
  {
       128,   -33,  -121,  -121,    25,    84,  -121,  -121,  -121,    27,
    -121,    28,  -121,  -121,   -25,   -14,  -121,   -22,    37,   123,
    -121,   100,   -37,    14,  -121,    22,   -32,    35,  -121,    41,
    -121,   123,   123,   162,  -121,    70,  -121,  -121,   -10,  -121,
     -19,   -10,    85,   139,  -121,  -121,    48,    20,  -121,   178,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,  -121,   100,    50,
     -10,  -121,  -121,  -121,    54,    99,  -121,  -121,  -121,   363,
      80,  -121,   372,   404,   413,   413,   413,   413,    98,    98,
     413,   413,   142,   142,   112,   112,  -121,  -121,  -121,    55,
      56,   104,   121,   122,   124,   123,   135,   141,   106,  -121,
    -121,   144,    50,  -121,   161,   328,   100,  -121,   137,  -121,
     123,  -121,    89,   123,   123,   100,   123,   280,  -121,  -121,
    -121,   316,  -121,  -121,  -121,   123,   123,   123,   123,   123,
     123,    97,  -121,   363,   163,    96,   216,   229,   164,   267,
    -121,  -121,   363,   363,   363,   363,   363,   363,  -121,  -121,
     165,    50,    50,   123,   156,  -121,   187,  -121,   327,    50,
      50,   100,   170,  -121,   176,  -121,    50,  -121
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,    26,    27,     0,     0,     2,     6,     5,     0,
       4,     0,     1,     3,    82,     0,    12,     0,     0,     0,
       7,     0,     0,     0,    14,    16,     0,     0,    78,    82,
      79,     0,     0,     0,    77,    82,    13,    10,    29,    24,
       0,     0,    18,    17,     8,    22,     0,     0,    75,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     0,    31,
      30,    11,    25,    15,     0,    19,     9,    23,    81,    84,
       0,    76,    59,    58,    60,    61,    63,    65,    68,    69,
      62,    64,    66,    67,    71,    70,    72,    73,    74,     0,
      82,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      51,     0,    32,    35,     0,     0,     0,    20,     0,    80,
       0,    33,     0,     0,     0,     0,     0,     0,    42,    43,
      44,     0,    28,    36,    38,     0,     0,     0,     0,     0,
       0,     0,    21,    85,     0,     0,     0,     0,     0,     0,
      41,    45,    53,    54,    55,    56,    57,    52,    34,    40,
       0,     0,     0,     0,     0,    39,    46,    49,     0,    31,
       0,     0,     0,    47,     0,    50,     0,    48
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -121,  -121,   215,  -121,   -66,   212,   190,  -121,    11,    42,
    -121,    63,  -121,  -121,  -109,  -120,   -18,    -9,   111
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     5,     6,     7,    15,    23,    24,     8,    25,   110,
      69,   111,    70,   112,   113,   114,    79,    34,    80
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const short int
  Parser::yytable_[] =
  {
        16,    33,    99,   133,    37,   148,     2,     3,    10,    44,
      38,     9,    36,    48,    49,    38,     9,    18,     2,     3,
      19,    22,    71,    28,    29,    30,    42,    20,    38,    11,
      21,    14,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    68,
     141,   174,   166,   167,   100,    43,    31,    40,    41,    16,
     115,   173,    32,    78,    39,     2,     3,   177,    45,   101,
      17,   102,   103,   104,   105,   106,   107,   108,    46,    41,
      26,   116,    72,    47,    12,     1,    19,   127,    77,    76,
     131,   109,    28,    29,    30,    38,   121,    38,   122,    21,
     117,    19,   143,   115,    35,   146,   147,    16,   149,    28,
      29,    30,     2,     3,     4,    19,   115,   152,   153,   154,
     155,   156,   157,   119,   120,    31,    28,    29,    30,     1,
      74,    32,   144,    62,    63,    64,    65,    66,   158,   160,
     120,    21,    31,    75,   118,   168,   123,   130,    32,    64,
      65,    66,   115,   115,    56,    57,     2,     3,     4,    31,
     115,   115,   115,   124,   125,    32,   126,   115,    50,    51,
      52,    53,    54,    55,    56,    57,   128,    62,    63,    64,
      65,    66,   129,   142,    50,    51,    52,    53,    54,    55,
      56,    57,   132,    58,    59,    60,    61,    62,    63,    64,
      65,    66,   134,   169,   159,   163,   165,   170,    67,    58,
      59,    60,    61,    62,    63,    64,    65,    66,   175,   176,
      13,    81,    50,    51,    52,    53,    54,    55,    56,    57,
      27,    73,   172,   145,     0,    50,    51,    52,    53,    54,
      55,    56,    57,     0,     0,     0,     0,    58,    59,    60,
      61,    62,    63,    64,    65,    66,     0,     0,     0,   161,
      58,    59,    60,    61,    62,    63,    64,    65,    66,     0,
       0,     0,   162,    50,    51,    52,    53,    54,    55,    56,
      57,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    56,    57,     0,     0,     0,     0,    58,    59,
      60,    61,    62,    63,    64,    65,    66,     0,     0,     0,
     164,    58,    59,    60,    61,    62,    63,    64,    65,    66,
       0,   150,    50,    51,    52,    53,    54,    55,    56,    57,
       0,     0,     0,    50,    51,    52,    53,    54,    55,    56,
      57,     0,   135,   136,   137,   138,   139,    58,    59,    60,
      61,    62,    63,    64,    65,    66,     0,   151,    58,    59,
      60,    61,    62,    63,    64,    65,    66,     0,   171,    50,
      51,    52,    53,    54,    55,    56,    57,   140,     0,    51,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     0,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    52,    53,    54,    55,    56,    57,     0,     0,
       0,    -1,    -1,    -1,    -1,    56,    57,     0,     0,     0,
       0,     0,     0,     0,     0,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         9,    19,    68,   112,    41,   125,    28,    29,    41,    41,
      47,     0,    21,    31,    32,    47,     5,    42,    28,    29,
      45,    43,    41,     3,     4,     5,     4,    41,    47,     4,
      44,     4,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    38,
     116,   171,   161,   162,     4,    33,    36,    43,    44,    68,
      69,   170,    42,    43,    22,    28,    29,   176,    26,    19,
      42,    21,    22,    23,    24,    25,    26,    27,    43,    44,
      43,    70,    40,    42,     0,     1,    45,   105,    46,    41,
     108,    41,     3,     4,     5,    47,    41,    47,    42,    44,
      46,    45,   120,   112,     4,   123,   124,   116,   126,     3,
       4,     5,    28,    29,    30,    45,   125,   135,   136,   137,
     138,   139,   140,    43,    44,    36,     3,     4,     5,     1,
      45,    42,    43,    35,    36,    37,    38,    39,    41,    43,
      44,    44,    36,     4,    45,   163,    42,    41,    42,    37,
      38,    39,   161,   162,    12,    13,    28,    29,    30,    36,
     169,   170,   171,    42,    42,    42,    42,   176,     6,     7,
       8,     9,    10,    11,    12,    13,    41,    35,    36,    37,
      38,    39,    41,    46,     6,     7,     8,     9,    10,    11,
      12,    13,    48,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    41,    47,    41,    41,    41,    20,    46,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    48,    43,
       5,    43,     6,     7,     8,     9,    10,    11,    12,    13,
      18,    41,   169,   122,    -1,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    43,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    43,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    41,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    14,    15,    16,    17,    18,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    41,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    41,     6,
       7,     8,     9,    10,    11,    12,    13,    49,    -1,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    31,    32,    33,    34,    35,    36,
      37,    38,    39
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,     1,    28,    29,    30,    51,    52,    53,    57,    58,
      41,     4,     0,    52,     4,    54,    67,    42,    42,    45,
      41,    44,    43,    55,    56,    58,    43,    55,     3,     4,
       5,    36,    42,    66,    67,     4,    67,    41,    47,    59,
      43,    44,     4,    33,    41,    59,    43,    42,    66,    66,
       6,     7,     8,     9,    10,    11,    12,    13,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    46,    58,    60,
      62,    41,    59,    56,    45,     4,    41,    59,    43,    66,
      68,    43,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    54,
       4,    19,    21,    22,    23,    24,    25,    26,    27,    41,
      59,    61,    63,    64,    65,    67,    58,    46,    45,    43,
      44,    41,    42,    42,    42,    42,    42,    66,    41,    41,
      41,    66,    48,    64,    41,    14,    15,    16,    17,    18,
      49,    54,    46,    66,    43,    68,    66,    66,    65,    66,
      41,    41,    66,    66,    66,    66,    66,    66,    41,    41,
      43,    43,    43,    41,    43,    41,    64,    64,    66,    47,
      20,    41,    61,    64,    65,    48,    43,    64
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    62,    60,    38,   124,    43,    45,    42,    47,    37,
     286,    59,    40,    41,    44,    91,    93,   123,   125,    61
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    50,    51,    51,    52,    52,    52,    53,    53,    53,
      53,    53,    54,    54,    55,    55,    56,    56,    56,    56,
      56,    56,    57,    57,    57,    57,    58,    58,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    65,    65,    65,    65,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    67,    67,    68,    68
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     2,     2,     1,     1,     3,     5,     6,
       5,     6,     1,     3,     1,     3,     1,     2,     2,     3,
       4,     5,     5,     6,     5,     6,     1,     1,     4,     0,
       1,     0,     1,     3,     4,     1,     2,     1,     2,     5,
       4,     3,     2,     2,     2,     3,     5,     7,     9,     5,
       7,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     1,     1,     1,
       4,     3,     1,     4,     1,     3
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"ival\"", "\"identifier\"",
  "\"sval\"", "\"||\"", "\"&&\"", "\"==\"", "\"!=\"", "\">=\"", "\"<=\"",
  "\"<<\"", "\">>\"", "\"+=\"", "\"-=\"", "\"*=\"", "\"/=\"", "\"%=\"",
  "\"if\"", "\"else\"", "\"while\"", "\"for\"", "\"switch\"", "\"case\"",
  "\"default\"", "\"break\"", "\"return\"", "\"int\"", "\"string\"",
  "\"void\"", "'>'", "'<'", "'&'", "'|'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "NEG", "';'", "'('", "')'", "','", "'['", "']'", "'{'", "'}'",
  "'='", "$accept", "unit", "sentence", "declaration", "vallist",
  "arglist", "argdef", "function", "type", "block", "decllist",
  "statelist", "decls", "states", "statement", "assign", "expr", "value",
  "args", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        51,     0,    -1,    52,    -1,    51,    52,    -1,     1,    41,
      -1,    57,    -1,    53,    -1,    58,    54,    41,    -1,    58,
       4,    42,    43,    41,    -1,    58,     4,    42,    55,    43,
      41,    -1,    30,     4,    42,    43,    41,    -1,    30,     4,
      42,    55,    43,    41,    -1,    67,    -1,    54,    44,    67,
      -1,    56,    -1,    55,    44,    56,    -1,    58,    -1,    58,
      33,    -1,    58,     4,    -1,    58,    33,     4,    -1,    58,
       4,    45,    46,    -1,    58,    33,     4,    45,    46,    -1,
      58,     4,    42,    43,    59,    -1,    58,     4,    42,    55,
      43,    59,    -1,    30,     4,    42,    43,    59,    -1,    30,
       4,    42,    55,    43,    59,    -1,    28,    -1,    29,    -1,
      47,    60,    61,    48,    -1,    -1,    62,    -1,    -1,    63,
      -1,    58,    54,    41,    -1,    62,    58,    54,    41,    -1,
      64,    -1,    63,    64,    -1,    41,    -1,    65,    41,    -1,
       4,    42,    68,    43,    41,    -1,     4,    42,    43,    41,
      -1,    24,    66,    41,    -1,    25,    41,    -1,    26,    41,
      -1,    27,    41,    -1,    27,    66,    41,    -1,    19,    42,
      66,    43,    64,    -1,    19,    42,    66,    43,    64,    20,
      64,    -1,    22,    42,    65,    41,    66,    41,    65,    43,
      64,    -1,    21,    42,    66,    43,    64,    -1,    23,    42,
      66,    43,    47,    61,    48,    -1,    59,    -1,    67,    49,
      66,    -1,    67,    14,    66,    -1,    67,    15,    66,    -1,
      67,    16,    66,    -1,    67,    17,    66,    -1,    67,    18,
      66,    -1,    66,     7,    66,    -1,    66,     6,    66,    -1,
      66,     8,    66,    -1,    66,     9,    66,    -1,    66,    31,
      66,    -1,    66,    10,    66,    -1,    66,    32,    66,    -1,
      66,    11,    66,    -1,    66,    33,    66,    -1,    66,    34,
      66,    -1,    66,    12,    66,    -1,    66,    13,    66,    -1,
      66,    36,    66,    -1,    66,    35,    66,    -1,    66,    37,
      66,    -1,    66,    38,    66,    -1,    66,    39,    66,    -1,
      36,    66,    -1,    42,    66,    43,    -1,    67,    -1,     3,
      -1,     5,    -1,     4,    42,    68,    43,    -1,     4,    42,
      43,    -1,     4,    -1,     4,    45,    66,    46,    -1,    66,
      -1,    68,    44,    66,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    11,    13,    15,    19,    25,
      32,    38,    45,    47,    51,    53,    57,    59,    62,    65,
      69,    74,    80,    86,    93,    99,   106,   108,   110,   115,
     116,   118,   119,   121,   125,   130,   132,   135,   137,   140,
     146,   151,   155,   158,   161,   164,   168,   174,   182,   192,
     198,   206,   208,   212,   216,   220,   224,   228,   232,   236,
     240,   244,   248,   252,   256,   260,   264,   268,   272,   276,
     280,   284,   288,   292,   296,   300,   303,   307,   309,   311,
     313,   318,   322,   324,   329,   331
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  Parser::yyrline_[] =
  {
         0,   128,   128,   129,   132,   133,   134,   137,   138,   139,
     140,   141,   144,   145,   148,   149,   152,   153,   154,   155,
     156,   157,   160,   161,   162,   163,   166,   167,   170,   173,
     174,   177,   178,   181,   182,   185,   186,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   206,   207,   208,   209,   210,   211,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   240,   241,   244,   245
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    39,    33,     2,
      42,    43,    37,    35,    44,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
      32,    49,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,    34,    48,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    40
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 452;
  const int Parser::yynnts_ = 19;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 12;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 50;

  const unsigned int Parser::yyuser_token_number_max_ = 286;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // yy

/* Line 1054 of lalr1.cc  */
#line 1753 "Parser.cc"


/* Line 1056 of lalr1.cc  */
#line 247 "Parser.yy"


void yy::Parser::error( const yy::Parser::location_type& l, const std::string& m )
{
	compiler.error( l, m );
}

