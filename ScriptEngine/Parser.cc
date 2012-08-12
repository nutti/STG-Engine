
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
#line 39 "Parser.yy"

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
#line 101 "Parser.yy"
	{ delete (yyvaluep->m_pStrVal); };

/* Line 480 of lalr1.cc  */
#line 238 "Parser.cc"
	break;
      case 5: /* "\"sval\"" */

/* Line 480 of lalr1.cc  */
#line 102 "Parser.yy"
	{ delete (yyvaluep->m_pStrVal); };

/* Line 480 of lalr1.cc  */
#line 247 "Parser.cc"
	break;
      case 57: /* "vallist" */

/* Line 480 of lalr1.cc  */
#line 103 "Parser.yy"
	{ delete (yyvaluep->m_pValueList); };

/* Line 480 of lalr1.cc  */
#line 256 "Parser.cc"
	break;
      case 58: /* "arglist" */

/* Line 480 of lalr1.cc  */
#line 104 "Parser.yy"
	{ delete (yyvaluep->m_pArgList); };

/* Line 480 of lalr1.cc  */
#line 265 "Parser.cc"
	break;
      case 59: /* "argdef" */

/* Line 480 of lalr1.cc  */
#line 105 "Parser.yy"
	{ delete (yyvaluep->m_pArgDef); };

/* Line 480 of lalr1.cc  */
#line 274 "Parser.cc"
	break;
      case 62: /* "block" */

/* Line 480 of lalr1.cc  */
#line 109 "Parser.yy"
	{ delete (yyvaluep->m_pBlock); };

/* Line 480 of lalr1.cc  */
#line 283 "Parser.cc"
	break;
      case 63: /* "decllist" */

/* Line 480 of lalr1.cc  */
#line 106 "Parser.yy"
	{ delete (yyvaluep->m_pDeclList); };

/* Line 480 of lalr1.cc  */
#line 292 "Parser.cc"
	break;
      case 64: /* "statelist" */

/* Line 480 of lalr1.cc  */
#line 107 "Parser.yy"
	{ delete (yyvaluep->m_pStateList); };

/* Line 480 of lalr1.cc  */
#line 301 "Parser.cc"
	break;
      case 65: /* "decls" */

/* Line 480 of lalr1.cc  */
#line 106 "Parser.yy"
	{ delete (yyvaluep->m_pDeclList); };

/* Line 480 of lalr1.cc  */
#line 310 "Parser.cc"
	break;
      case 66: /* "states" */

/* Line 480 of lalr1.cc  */
#line 107 "Parser.yy"
	{ delete (yyvaluep->m_pStateList); };

/* Line 480 of lalr1.cc  */
#line 319 "Parser.cc"
	break;
      case 67: /* "statement" */

/* Line 480 of lalr1.cc  */
#line 111 "Parser.yy"
	{ delete (yyvaluep->m_pStatement); };

/* Line 480 of lalr1.cc  */
#line 328 "Parser.cc"
	break;
      case 68: /* "assign" */

/* Line 480 of lalr1.cc  */
#line 110 "Parser.yy"
	{ delete (yyvaluep->m_pAssign); };

/* Line 480 of lalr1.cc  */
#line 337 "Parser.cc"
	break;
      case 69: /* "expr" */

/* Line 480 of lalr1.cc  */
#line 113 "Parser.yy"
	{ delete (yyvaluep->m_pExpr); };

/* Line 480 of lalr1.cc  */
#line 346 "Parser.cc"
	break;
      case 70: /* "value" */

/* Line 480 of lalr1.cc  */
#line 112 "Parser.yy"
	{ delete (yyvaluep->m_pVal); };

/* Line 480 of lalr1.cc  */
#line 355 "Parser.cc"
	break;
      case 71: /* "args" */

/* Line 480 of lalr1.cc  */
#line 108 "Parser.yy"
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
#line 141 "Parser.yy"
    { compiler.DefineValue( (yylocation_stack_[(3) - (2)]), (yysemantic_stack_[(3) - (1)].m_Type), (yysemantic_stack_[(3) - (2)].m_pValueList) ); }
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 142 "Parser.yy"
    { compiler.DefineFunction( (yylocation_stack_[(5) - (2)]), (yysemantic_stack_[(5) - (1)].m_Type), (yysemantic_stack_[(5) - (2)].m_pStrVal), NULL ); }
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 143 "Parser.yy"
    { compiler.DefineFunction( (yylocation_stack_[(6) - (2)]), (yysemantic_stack_[(6) - (1)].m_Type), (yysemantic_stack_[(6) - (2)].m_pStrVal), (yysemantic_stack_[(6) - (4)].m_pArgList) ); }
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 144 "Parser.yy"
    { compiler.DefineFunction( (yylocation_stack_[(5) - (2)]), TYPE_VOID, (yysemantic_stack_[(5) - (2)].m_pStrVal), NULL ); }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 145 "Parser.yy"
    { compiler.DefineFunction( (yylocation_stack_[(6) - (2)]), TYPE_VOID, (yysemantic_stack_[(6) - (2)].m_pStrVal), (yysemantic_stack_[(6) - (4)].m_pArgList) ); }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 148 "Parser.yy"
    { (yyval.m_pValueList) = new ValueList( (yysemantic_stack_[(1) - (1)].m_pVal) ); }
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 149 "Parser.yy"
    { (yyval.m_pValueList) = (yysemantic_stack_[(3) - (1)].m_pValueList)->Add( (yysemantic_stack_[(3) - (3)].m_pVal) ); }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 152 "Parser.yy"
    { (yyval.m_pArgList) = new ArgList( (yysemantic_stack_[(1) - (1)].m_pArgDef) ); }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 153 "Parser.yy"
    { (yyval.m_pArgList) = (yysemantic_stack_[(3) - (1)].m_pArgList)->Add( (yysemantic_stack_[(3) - (3)].m_pArgDef) ); }
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 156 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].m_Type), NULL ); }
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 157 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(2) - (1)]), TypeToRef( (yysemantic_stack_[(2) - (1)].m_Type) ), NULL ); }
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 158 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(2) - (1)]), (yysemantic_stack_[(2) - (1)].m_Type), (yysemantic_stack_[(2) - (2)].m_pStrVal) ); }
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 159 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(3) - (1)]), TypeToRef( (yysemantic_stack_[(3) - (1)].m_Type) ), (yysemantic_stack_[(3) - (3)].m_pStrVal) ); }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 160 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(4) - (1)]), TypeToRef( (yysemantic_stack_[(4) - (1)].m_Type) ), (yysemantic_stack_[(4) - (2)].m_pStrVal) ); }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 161 "Parser.yy"
    { (yyval.m_pArgDef) = new ArgDef( (yylocation_stack_[(5) - (1)]), TypeToRef( (yysemantic_stack_[(5) - (1)].m_Type) ), (yysemantic_stack_[(5) - (3)].m_pStrVal) ); }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 164 "Parser.yy"
    { compiler.AddFunction( (yylocation_stack_[(5) - (1)]), (yysemantic_stack_[(5) - (1)].m_Type), (yysemantic_stack_[(5) - (2)].m_pStrVal), NULL, (yysemantic_stack_[(5) - (5)].m_pBlock) ); }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 165 "Parser.yy"
    { compiler.AddFunction( (yylocation_stack_[(6) - (1)]), (yysemantic_stack_[(6) - (1)].m_Type), (yysemantic_stack_[(6) - (2)].m_pStrVal), (yysemantic_stack_[(6) - (4)].m_pArgList), (yysemantic_stack_[(6) - (6)].m_pBlock) ); }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 166 "Parser.yy"
    { compiler.AddFunction( (yylocation_stack_[(5) - (1)]), TYPE_VOID, (yysemantic_stack_[(5) - (2)].m_pStrVal), NULL, (yysemantic_stack_[(5) - (5)].m_pBlock) ); }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 167 "Parser.yy"
    { compiler.AddFunction( (yylocation_stack_[(6) - (1)]), TYPE_VOID, (yysemantic_stack_[(6) - (2)].m_pStrVal), (yysemantic_stack_[(6) - (4)].m_pArgList), (yysemantic_stack_[(6) - (6)].m_pBlock) ); }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 170 "Parser.yy"
    { (yyval.m_Type) = TYPE_INTEGER; }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 171 "Parser.yy"
    { (yyval.m_Type) = TYPE_STRING; }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 172 "Parser.yy"
    { (yyval.m_Type) = TYPE_FLOAT; }
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 175 "Parser.yy"
    { (yyval.m_pBlock) = new StateBlock( (yysemantic_stack_[(4) - (2)].m_pDeclList), (yysemantic_stack_[(4) - (3)].m_pStateList) ); }
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 178 "Parser.yy"
    { (yyval.m_pDeclList) = NULL; }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 179 "Parser.yy"
    { (yyval.m_pDeclList) = (yysemantic_stack_[(1) - (1)].m_pDeclList); }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 182 "Parser.yy"
    { (yyval.m_pStateList) = NULL; }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 183 "Parser.yy"
    { (yyval.m_pStateList) = (yysemantic_stack_[(1) - (1)].m_pStateList); }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 186 "Parser.yy"
    { (yyval.m_pDeclList) = new DeclList( new Decl( (yysemantic_stack_[(3) - (1)].m_Type), (yysemantic_stack_[(3) - (2)].m_pValueList) ) ); }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 187 "Parser.yy"
    { (yyval.m_pDeclList) = (yysemantic_stack_[(4) - (1)].m_pDeclList)->Add( new Decl( (yysemantic_stack_[(4) - (2)].m_Type), (yysemantic_stack_[(4) - (3)].m_pValueList) ) ); }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 190 "Parser.yy"
    { (yyval.m_pStateList) = new StateList( (yysemantic_stack_[(1) - (1)].m_pStatement) ); }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 191 "Parser.yy"
    { (yyval.m_pStateList) = (yysemantic_stack_[(2) - (1)].m_pStateList)->Add( (yysemantic_stack_[(2) - (2)].m_pStatement) ); }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 194 "Parser.yy"
    { (yyval.m_pStatement) = new NopStatement( (yylocation_stack_[(1) - (1)]) ); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 195 "Parser.yy"
    { (yyval.m_pStatement) = new AssignStatement( (yylocation_stack_[(2) - (1)]), (yysemantic_stack_[(2) - (1)].m_pAssign) ); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 196 "Parser.yy"
    { (yyval.m_pStatement) = new FunctionStatement( (yylocation_stack_[(5) - (1)]), (yysemantic_stack_[(5) - (1)].m_pStrVal), (yysemantic_stack_[(5) - (3)].m_pArgs) ); }
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 197 "Parser.yy"
    { (yyval.m_pStatement) = new FunctionStatement( (yylocation_stack_[(4) - (1)]), (yysemantic_stack_[(4) - (1)].m_pStrVal), NULL ); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 198 "Parser.yy"
    { (yyval.m_pStatement) = new CaseStatement( (yylocation_stack_[(3) - (1)]), (yysemantic_stack_[(3) - (2)].m_pExpr) ); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 199 "Parser.yy"
    { (yyval.m_pStatement) = new DefaultStatement( (yylocation_stack_[(2) - (1)]) ); }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 200 "Parser.yy"
    { (yyval.m_pStatement) = new BreakStatement( (yylocation_stack_[(2) - (1)]) ); }
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 201 "Parser.yy"
    { (yyval.m_pStatement) = new ReturnStatement( (yylocation_stack_[(2) - (1)]), NULL ); }
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 202 "Parser.yy"
    { (yyval.m_pStatement) = new ReturnStatement( (yylocation_stack_[(3) - (1)]), (yysemantic_stack_[(3) - (2)].m_pExpr) ); }
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 203 "Parser.yy"
    { (yyval.m_pStatement) = new IfStatement( (yylocation_stack_[(5) - (1)]), (yysemantic_stack_[(5) - (3)].m_pExpr), (yysemantic_stack_[(5) - (5)].m_pStatement) ); }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 204 "Parser.yy"
    { (yyval.m_pStatement) = new IfStatement( (yylocation_stack_[(7) - (1)]), (yysemantic_stack_[(7) - (3)].m_pExpr), (yysemantic_stack_[(7) - (5)].m_pStatement), (yysemantic_stack_[(7) - (7)].m_pStatement) ); }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 205 "Parser.yy"
    { (yyval.m_pStatement) = new ForStatement( (yylocation_stack_[(9) - (1)]), (yysemantic_stack_[(9) - (3)].m_pAssign), (yysemantic_stack_[(9) - (5)].m_pExpr), (yysemantic_stack_[(9) - (7)].m_pAssign), (yysemantic_stack_[(9) - (9)].m_pStatement) ); }
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 206 "Parser.yy"
    { (yyval.m_pStatement) = new WhileStatement( (yylocation_stack_[(5) - (1)]), (yysemantic_stack_[(5) - (3)].m_pExpr), (yysemantic_stack_[(5) - (5)].m_pStatement) ); }
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 207 "Parser.yy"
    { (yyval.m_pStatement) = new SwitchStatement( (yylocation_stack_[(7) - (1)]), (yysemantic_stack_[(7) - (3)].m_pExpr), (yysemantic_stack_[(7) - (6)].m_pStateList) ); }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 208 "Parser.yy"
    { (yyval.m_pStatement) = new BlockStatement( (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].m_pBlock) ); }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 211 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '=', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 212 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '+', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 213 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '-', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 214 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '*', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 215 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '/', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 216 "Parser.yy"
    { (yyval.m_pAssign) = new Assign( (yylocation_stack_[(3) - (1)]), '%', (yysemantic_stack_[(3) - (1)].m_pVal), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 219 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LOGAND, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 220 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LOGOR, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 221 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_EQ, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 222 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_NE, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 223 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_GT, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 224 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_GE, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 225 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LT, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 66:

/* Line 678 of lalr1.cc  */
#line 226 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LE, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 227 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_AND, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 228 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_OR, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 229 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_LSHIFT, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 230 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_RSHIFT, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 231 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_MINUS, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 232 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_PLUS, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 233 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_TIMES, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 234 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_DIVIDE, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 235 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(3) - (2)]), OP_MOD, (yysemantic_stack_[(3) - (1)].m_pExpr), (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 236 "Parser.yy"
    { (yyval.m_pExpr) = Node::MakeNode( compiler, (yylocation_stack_[(2) - (2)]), OP_NEG, (yysemantic_stack_[(2) - (2)].m_pExpr) ); }
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 237 "Parser.yy"
    { (yyval.m_pExpr) = (yysemantic_stack_[(3) - (2)].m_pExpr); }
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 238 "Parser.yy"
    { (yyval.m_pExpr) = (yysemantic_stack_[(1) - (1)].m_pVal); }
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 239 "Parser.yy"
    { (yyval.m_pExpr) = new Node( (yylocation_stack_[(1) - (1)]), OP_INT_CONST, (yysemantic_stack_[(1) - (1)].m_IntVal) ); }
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 240 "Parser.yy"
    { (yyval.m_pExpr) = new Node( (yylocation_stack_[(1) - (1)]), OP_STRING, (yysemantic_stack_[(1) - (1)].m_pStrVal) ); }
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 241 "Parser.yy"
    { (yyval.m_pExpr) = new Node( (yylocation_stack_[(1) - (1)]), OP_FLOAT_CONST, (yysemantic_stack_[(1) - (1)].m_FloatVal) ); }
    break;

  case 82:

/* Line 678 of lalr1.cc  */
#line 242 "Parser.yy"
    { (yyval.m_pExpr) = new FunctionNode( (yylocation_stack_[(4) - (1)]), (yysemantic_stack_[(4) - (1)].m_pStrVal), (yysemantic_stack_[(4) - (3)].m_pArgs) ); }
    break;

  case 83:

/* Line 678 of lalr1.cc  */
#line 243 "Parser.yy"
    { (yyval.m_pExpr) = new FunctionNode( (yylocation_stack_[(3) - (1)]), (yysemantic_stack_[(3) - (1)].m_pStrVal), NULL ); }
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 246 "Parser.yy"
    { (yyval.m_pVal) = new ValueNode( (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].m_pStrVal) ); }
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 247 "Parser.yy"
    { (yyval.m_pVal) = new ValueNode( (yylocation_stack_[(4) - (1)]), (yysemantic_stack_[(4) - (1)].m_pStrVal), (yysemantic_stack_[(4) - (3)].m_pExpr) ); }
    break;

  case 86:

/* Line 678 of lalr1.cc  */
#line 250 "Parser.yy"
    { (yyval.m_pArgs) = new Args( (yysemantic_stack_[(1) - (1)].m_pExpr) ); }
    break;

  case 87:

/* Line 678 of lalr1.cc  */
#line 251 "Parser.yy"
    { (yyval.m_pArgs) = (yysemantic_stack_[(3) - (1)].m_pArgs)->Add( (yysemantic_stack_[(3) - (3)].m_pExpr) ); }
    break;



/* Line 678 of lalr1.cc  */
#line 1136 "Parser.cc"
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
  const signed char Parser::yypact_ninf_ = -122;
  const short int
  Parser::yypact_[] =
  {
        55,   -34,  -122,  -122,  -122,    15,   157,  -122,  -122,  -122,
      68,  -122,   -27,  -122,  -122,   -26,    24,  -122,   102,   185,
     121,  -122,    77,   -41,    56,  -122,    23,   -38,    83,  -122,
      22,  -122,  -122,   121,   121,   171,  -122,    12,  -122,  -122,
     212,  -122,   -36,   212,    52,   112,  -122,  -122,   -23,    19,
    -122,   213,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,  -122,
      77,    51,   212,  -122,  -122,  -122,    57,   105,  -122,  -122,
    -122,   365,    89,  -122,   374,   383,   416,   416,   416,   416,
     153,   153,   416,   416,   101,   101,   216,   216,  -122,  -122,
    -122,    37,    45,   104,   111,   116,   120,   121,   115,   106,
     107,  -122,  -122,   117,    51,  -122,   113,    13,    77,  -122,
     129,  -122,   121,  -122,    92,   121,   121,    77,   121,   162,
    -122,  -122,  -122,   317,  -122,  -122,  -122,   121,   121,   121,
     121,   121,   121,    47,  -122,   365,   174,    98,   226,   265,
     175,   278,  -122,  -122,   365,   365,   365,   365,   365,   365,
    -122,  -122,   186,    51,    51,   121,   179,  -122,   210,  -122,
     328,    51,    51,    77,   182,  -122,   199,  -122,    51,  -122
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,    26,    27,    28,     0,     0,     2,     6,     5,
       0,     4,     0,     1,     3,    84,     0,    12,     0,     0,
       0,     7,     0,     0,     0,    14,    16,     0,     0,    79,
      84,    80,    81,     0,     0,     0,    78,    84,    13,    10,
      30,    24,     0,     0,    18,    17,     8,    22,     0,     0,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
       0,    32,    31,    11,    25,    15,     0,    19,     9,    23,
      83,    86,     0,    77,    60,    59,    61,    62,    64,    66,
      69,    70,    63,    65,    67,    68,    72,    71,    73,    74,
      75,     0,    84,     0,     0,     0,     0,     0,     0,     0,
       0,    38,    52,     0,    33,    36,     0,     0,     0,    20,
       0,    82,     0,    34,     0,     0,     0,     0,     0,     0,
      43,    44,    45,     0,    29,    37,    39,     0,     0,     0,
       0,     0,     0,     0,    21,    87,     0,     0,     0,     0,
       0,     0,    42,    46,    54,    55,    56,    57,    58,    53,
      35,    41,     0,     0,     0,     0,     0,    40,    47,    50,
       0,    32,     0,     0,     0,    48,     0,    51,     0,    49
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -122,  -122,   239,  -122,   -67,   249,   227,  -122,    10,   417,
    -122,   109,  -122,  -122,  -110,  -121,   -19,   -10,   145
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     6,     7,     8,    16,    24,    25,     9,    26,   112,
      71,   113,    72,   114,   115,   116,    81,    36,    82
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const short int
  Parser::yytable_[] =
  {
        17,    35,    39,   101,   135,    46,   150,    73,    40,    11,
      10,    40,    38,    40,    50,    51,    10,    18,    19,    12,
      78,    20,    29,    30,    31,    32,    40,    44,   137,   138,
     139,   140,   141,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
      70,   143,   176,   168,   169,   102,     1,    33,    45,    20,
      17,   117,   175,    34,    80,   142,    49,    21,   179,    20,
      22,   103,    15,   104,   105,   106,   107,   108,   109,   110,
     123,    37,   118,    22,     2,     3,     4,     5,   129,   124,
     160,   133,    20,    22,   111,    29,    30,    31,    32,    76,
      40,    42,    43,   145,   117,   119,   148,   149,    17,   151,
      29,    30,    31,    32,    58,    59,    77,   117,   154,   155,
     156,   157,   158,   159,    29,    30,    31,    32,    48,    43,
      33,     2,     3,     4,   121,   122,    34,   146,    64,    65,
      66,    67,    68,   162,   122,    33,   170,    23,   125,   131,
     132,    34,   120,   117,   117,   126,   136,    13,     1,    33,
     127,   117,   117,   117,   128,    34,   130,   134,   117,    52,
      53,    54,    55,    56,    57,    58,    59,   144,    52,    53,
      54,    55,    56,    57,    58,    59,     2,     3,     4,     5,
      64,    65,    66,    67,    68,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    60,    61,    62,    63,    64,    65,
      66,    67,    68,   152,     2,     3,     4,   161,   165,    69,
      52,    53,    54,    55,    56,    57,    58,    59,   171,   167,
      27,   172,   177,    52,    53,    54,    55,    56,    57,    58,
      59,     2,     3,     4,   178,    14,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    66,    67,    68,    83,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    28,   147,
      75,   163,    52,    53,    54,    55,    56,    57,    58,    59,
     174,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,     0,     0,     0,     0,     0,    60,    61,
      62,    63,    64,    65,    66,    67,    68,     0,     0,     0,
     164,    60,    61,    62,    63,    64,    65,    66,    67,    68,
       0,     0,     0,   166,    52,    53,    54,    55,    56,    57,
      58,    59,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    62,    63,    64,    65,    66,    67,    68,     0,
     153,    60,    61,    62,    63,    64,    65,    66,    67,    68,
       0,   173,    52,    53,    54,    55,    56,    57,    58,    59,
       0,     0,    53,    54,    55,    56,    57,    58,    59,     0,
       0,     0,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    58,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,     0,     0,     0,    47,     0,     0,     0,     0,    -1,
      -1,    62,    63,    64,    65,    66,    67,    68,     0,    74,
       0,     0,     0,     0,     0,    79
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        10,    20,    43,    70,   114,    43,   127,    43,    49,    43,
       0,    49,    22,    49,    33,    34,     6,    44,    44,     4,
      43,    47,     3,     4,     5,     6,    49,     4,    15,    16,
      17,    18,    19,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      40,   118,   173,   163,   164,     4,     1,    38,    35,    47,
      70,    71,   172,    44,    45,    52,    44,    43,   178,    47,
      46,    20,     4,    22,    23,    24,    25,    26,    27,    28,
      43,     4,    72,    46,    29,    30,    31,    32,   107,    44,
      43,   110,    47,    46,    43,     3,     4,     5,     6,    47,
      49,    45,    46,   122,   114,    48,   125,   126,   118,   128,
       3,     4,     5,     6,    13,    14,     4,   127,   137,   138,
     139,   140,   141,   142,     3,     4,     5,     6,    45,    46,
      38,    29,    30,    31,    45,    46,    44,    45,    37,    38,
      39,    40,    41,    45,    46,    38,   165,    45,    44,    43,
      43,    44,    47,   163,   164,    44,    43,     0,     1,    38,
      44,   171,   172,   173,    44,    44,    51,    50,   178,     7,
       8,     9,    10,    11,    12,    13,    14,    48,     7,     8,
       9,    10,    11,    12,    13,    14,    29,    30,    31,    32,
      37,    38,    39,    40,    41,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    51,    29,    30,    31,    43,    43,    48,
       7,     8,     9,    10,    11,    12,    13,    14,    49,    43,
      45,    21,    50,     7,     8,     9,    10,    11,    12,    13,
      14,    29,    30,    31,    45,     6,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    39,    40,    41,    45,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    19,   124,
      43,    45,     7,     8,     9,    10,    11,    12,    13,    14,
     171,    -1,    -1,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      45,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    45,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    48
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,     1,    29,    30,    31,    32,    54,    55,    56,    60,
      61,    43,     4,     0,    55,     4,    57,    70,    44,    44,
      47,    43,    46,    45,    58,    59,    61,    45,    58,     3,
       4,     5,     6,    38,    44,    69,    70,     4,    70,    43,
      49,    62,    45,    46,     4,    35,    43,    62,    45,    44,
      69,    69,     7,     8,     9,    10,    11,    12,    13,    14,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    48,
      61,    63,    65,    43,    62,    59,    47,     4,    43,    62,
      45,    69,    71,    45,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    57,     4,    20,    22,    23,    24,    25,    26,    27,
      28,    43,    62,    64,    66,    67,    68,    70,    61,    48,
      47,    45,    46,    43,    44,    44,    44,    44,    44,    69,
      51,    43,    43,    69,    50,    67,    43,    15,    16,    17,
      18,    19,    52,    57,    48,    69,    45,    71,    69,    69,
      68,    69,    51,    43,    69,    69,    69,    69,    69,    69,
      43,    43,    45,    45,    45,    43,    45,    43,    67,    67,
      69,    49,    21,    43,    64,    67,    68,    50,    45,    67
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
     285,   286,   287,    62,    60,    38,   124,    43,    45,    42,
      47,    37,   288,    59,    40,    41,    44,    91,    93,   123,
     125,    58,    61
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    53,    54,    54,    55,    55,    55,    56,    56,    56,
      56,    56,    57,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    60,    60,    60,    60,    61,    61,    61,    62,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    68,    68,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    71,    71
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     2,     2,     1,     1,     3,     5,     6,
       5,     6,     1,     3,     1,     3,     1,     2,     2,     3,
       4,     5,     5,     6,     5,     6,     1,     1,     1,     4,
       0,     1,     0,     1,     3,     4,     1,     2,     1,     2,
       5,     4,     3,     2,     2,     2,     3,     5,     7,     9,
       5,     7,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     1,     1,
       1,     1,     4,     3,     1,     4,     1,     3
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"ival\"", "\"identifier\"",
  "\"sval\"", "\"fval\"", "\"||\"", "\"&&\"", "\"==\"", "\"!=\"", "\">=\"",
  "\"<=\"", "\"<<\"", "\">>\"", "\"+=\"", "\"-=\"", "\"*=\"", "\"/=\"",
  "\"%=\"", "\"if\"", "\"else\"", "\"while\"", "\"for\"", "\"switch\"",
  "\"case\"", "\"default\"", "\"break\"", "\"return\"", "\"int\"",
  "\"string\"", "\"float\"", "\"void\"", "'>'", "'<'", "'&'", "'|'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "NEG", "';'", "'('", "')'", "','", "'['",
  "']'", "'{'", "'}'", "':'", "'='", "$accept", "unit", "sentence",
  "declaration", "vallist", "arglist", "argdef", "function", "type",
  "block", "decllist", "statelist", "decls", "states", "statement",
  "assign", "expr", "value", "args", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        54,     0,    -1,    55,    -1,    54,    55,    -1,     1,    43,
      -1,    60,    -1,    56,    -1,    61,    57,    43,    -1,    61,
       4,    44,    45,    43,    -1,    61,     4,    44,    58,    45,
      43,    -1,    32,     4,    44,    45,    43,    -1,    32,     4,
      44,    58,    45,    43,    -1,    70,    -1,    57,    46,    70,
      -1,    59,    -1,    58,    46,    59,    -1,    61,    -1,    61,
      35,    -1,    61,     4,    -1,    61,    35,     4,    -1,    61,
       4,    47,    48,    -1,    61,    35,     4,    47,    48,    -1,
      61,     4,    44,    45,    62,    -1,    61,     4,    44,    58,
      45,    62,    -1,    32,     4,    44,    45,    62,    -1,    32,
       4,    44,    58,    45,    62,    -1,    29,    -1,    30,    -1,
      31,    -1,    49,    63,    64,    50,    -1,    -1,    65,    -1,
      -1,    66,    -1,    61,    57,    43,    -1,    65,    61,    57,
      43,    -1,    67,    -1,    66,    67,    -1,    43,    -1,    68,
      43,    -1,     4,    44,    71,    45,    43,    -1,     4,    44,
      45,    43,    -1,    25,    69,    51,    -1,    26,    51,    -1,
      27,    43,    -1,    28,    43,    -1,    28,    69,    43,    -1,
      20,    44,    69,    45,    67,    -1,    20,    44,    69,    45,
      67,    21,    67,    -1,    23,    44,    68,    43,    69,    43,
      68,    45,    67,    -1,    22,    44,    69,    45,    67,    -1,
      24,    44,    69,    45,    49,    64,    50,    -1,    62,    -1,
      70,    52,    69,    -1,    70,    15,    69,    -1,    70,    16,
      69,    -1,    70,    17,    69,    -1,    70,    18,    69,    -1,
      70,    19,    69,    -1,    69,     8,    69,    -1,    69,     7,
      69,    -1,    69,     9,    69,    -1,    69,    10,    69,    -1,
      69,    33,    69,    -1,    69,    11,    69,    -1,    69,    34,
      69,    -1,    69,    12,    69,    -1,    69,    35,    69,    -1,
      69,    36,    69,    -1,    69,    13,    69,    -1,    69,    14,
      69,    -1,    69,    38,    69,    -1,    69,    37,    69,    -1,
      69,    39,    69,    -1,    69,    40,    69,    -1,    69,    41,
      69,    -1,    38,    69,    -1,    44,    69,    45,    -1,    70,
      -1,     3,    -1,     5,    -1,     6,    -1,     4,    44,    71,
      45,    -1,     4,    44,    45,    -1,     4,    -1,     4,    47,
      69,    48,    -1,    69,    -1,    71,    46,    69,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    11,    13,    15,    19,    25,
      32,    38,    45,    47,    51,    53,    57,    59,    62,    65,
      69,    74,    80,    86,    93,    99,   106,   108,   110,   112,
     117,   118,   120,   121,   123,   127,   132,   134,   137,   139,
     142,   148,   153,   157,   160,   163,   166,   170,   176,   184,
     194,   200,   208,   210,   214,   218,   222,   226,   230,   234,
     238,   242,   246,   250,   254,   258,   262,   266,   270,   274,
     278,   282,   286,   290,   294,   298,   302,   305,   309,   311,
     313,   315,   317,   322,   326,   328,   333,   335
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  Parser::yyrline_[] =
  {
         0,   132,   132,   133,   136,   137,   138,   141,   142,   143,
     144,   145,   148,   149,   152,   153,   156,   157,   158,   159,
     160,   161,   164,   165,   166,   167,   170,   171,   172,   175,
     178,   179,   182,   183,   186,   187,   190,   191,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   211,   212,   213,   214,   215,   216,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   246,   247,   250,   251
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
       2,     2,     2,     2,     2,     2,     2,    41,    35,     2,
      44,    45,    39,    37,    46,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    43,
      34,    52,    33,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,    36,    50,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    42
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 465;
  const int Parser::yynnts_ = 19;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 13;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 53;

  const unsigned int Parser::yyuser_token_number_max_ = 288;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // yy

/* Line 1054 of lalr1.cc  */
#line 1770 "Parser.cc"


/* Line 1056 of lalr1.cc  */
#line 253 "Parser.yy"


void yy::Parser::error( const yy::Parser::location_type& l, const std::string& m )
{
	compiler.error( l, m );
}

