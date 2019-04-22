%{
/*	ETAPA 3 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre
*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "hash.h"
  #include "astree.h"

	int yylex();
	int yyerror(char *message);
	extern int getLineNumber();

  astree_node *root;

%}

%union{
	hash_node *symbol;
	astree_node *astree;
}

%token KW_BYTE
%token KW_INT
%token KW_FLOAT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_LOOP
%token KW_LEAP
%token KW_READ
%token KW_RETURN
%token KW_PRINT

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token OPERATOR_OR
%token OPERATOR_AND
%token OPERATOR_NOT

%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_FLOAT
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR

%left OPERATOR_OR OPERATOR_AND OPERATOR_NOT
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'

%type <astree> program
%type <astree> l_declarations
%type <astree> declaration
%type <astree> tipo
%type <astree> literal
%type <astree> init_vector
%type <astree> vector_elements
%type <astree> l_param
%type <astree> param_end
%type <astree> param
%type <astree> bloco
%type <astree> l_cmd
%type <astree> l_cmd_end
%type <astree> cmd
%type <astree> exp
%type <astree> l_args
%type <astree> l_args_end
%type <astree> l_print
%type <astree> l_print_end
%type <astree> element_print

%start program

%%

program : l_declarations                                                  {root=$$;astreePrint(0, root);}
    		;

l_declarations : declaration l_declarations                               {$$=astreeCreate(AST_LDEC, 0, $1, $2, 0, 0);}
							 | 																													{$$=0;}
               ;

declaration : tipo TK_IDENTIFIER '=' literal ';'													{$$=astreeCreate(AST_DECVAR, $2, $1, $4, 0, 0);}
            | tipo TK_IDENTIFIER '[' LIT_INTEGER ']' init_vector ';'			{$$=astreeCreate(AST_DECVEC, $2, $1,
																																								astreeCreate(AST_SYMBOL, $4, 0, 0, 0, 0),
																																								$6, 0);}
            | tipo TK_IDENTIFIER '(' l_param ')' bloco ';'								{$$=astreeCreate(AST_DECFUNC, $2, $1, $4, $6, 0);}
            ;

tipo : KW_BYTE																														{$$=astreeCreate(AST_TPBYTE, 0, 0, 0, 0, 0);}
     | KW_INT																															{$$=astreeCreate(AST_TPINT, 0, 0, 0, 0, 0);}
     | KW_FLOAT																														{$$=astreeCreate(AST_TPFLOAT, 0, 0, 0, 0, 0);}
     ;

literal : LIT_INTEGER																											{$$=astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
        | LIT_FLOAT																												{$$=astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
        | LIT_CHAR																												{$$=astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
        ;

init_vector :																															{$$=0;}
            | ':' literal vector_elements																	{$$=astreeCreate(AST_VECINIT, 0, $2, $3, 0, 0);}
            ;

vector_elements :																													{$$=0;}
                | literal vector_elements																	{$$=astreeCreate(AST_VECELEMENTS, 0, $1, $2, 0, 0);}
                ;

l_param :																																	{$$=0;}
        | param param_end																									{$$=astreeCreate(AST_PARAMINIT, 0, $1, $2, 0, 0);}
        ;

param_end :																																{$$=0;}
					| ',' param param_end																						{$$=astreeCreate(AST_PARAMLST, 0, $2, $3, 0, 0);}
          ;

param : tipo TK_IDENTIFIER																								{$$=astreeCreate(AST_PARAM, $2, $1, 0, 0, 0);}
      ;

bloco : '{' l_cmd '}'																											{$$=astreeCreate(AST_BLOCK, 0, $2, 0, 0, 0);}
      ;

l_cmd : cmd l_cmd_end																											{$$=astreeCreate(AST_CMDLSTINIT, 0, $1, $2, 0, 0);}
			;

l_cmd_end :																																{$$=0;}
          | ';' cmd l_cmd_end																							{$$=astreeCreate(AST_CMDLST, 0, $2, $3, 0, 0);}
          ;

cmd :																																			{$$=0;}
    | bloco																																{$$=$1;}
    | TK_IDENTIFIER '=' exp																								{$$=astreeCreate(AST_ATTR, $1, $3, 0, 0, 0);}
    | TK_IDENTIFIER '[' exp ']' '=' exp																		{$$=astreeCreate(AST_VECATTR, $1, $3, $6, 0, 0);}
    | KW_READ TK_IDENTIFIER																								{$$=astreeCreate(AST_READ, $2, 0, 0, 0, 0);}
    | KW_PRINT l_print																										{$$=astreeCreate(AST_PRINT, 0, $2, 0, 0, 0);}
    | KW_RETURN exp																												{$$=astreeCreate(AST_RETURN, 0, $2, 0, 0, 0);}
    | KW_IF '(' exp ')' KW_THEN cmd																				{$$=astreeCreate(AST_IF, 0, $3, $6, 0, 0);}
    | KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd														{$$=astreeCreate(AST_IFELSE, 0, $3, $6, $8, 0);}
    | KW_LOOP '(' exp ')' cmd																							{$$=astreeCreate(AST_LOOP, 0, $3, $5, 0, 0);}
    | KW_LEAP																															{$$=astreeCreate(AST_LEAP, 0, 0, 0, 0, 0);}
    ;

exp : TK_IDENTIFIER																												{$$=astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
    | TK_IDENTIFIER '[' exp ']'																						{$$=astreeCreate(AST_VEC, $1, $3, 0, 0, 0);}
    | TK_IDENTIFIER '(' l_args ')'																				{$$=astreeCreate(AST_FUNC, $1, $3, 0, 0, 0);}
    | literal																															{$$=$1;}
    | exp '+' exp																													{$$=astreeCreate(AST_SUM, 0, $1, $3, 0, 0);}
    | exp '-' exp																													{$$=astreeCreate(AST_DEC, 0, $1, $3, 0, 0);}
    | exp '*' exp																													{$$=astreeCreate(AST_MUL, 0, $1, $3, 0, 0);}
    | exp '/' exp																													{$$=astreeCreate(AST_DIV, 0, $1, $3, 0, 0);}
    | exp '<' exp																													{$$=astreeCreate(AST_LESS, 0, $1, $3, 0, 0);}
    | exp '>' exp																													{$$=astreeCreate(AST_GREAT, 0, $1, $3, 0, 0);}
    | exp OPERATOR_EQ exp																									{$$=astreeCreate(AST_EQ, 0, $1, $3, 0, 0);}
    | exp OPERATOR_GE exp																									{$$=astreeCreate(AST_GE, 0, $1, $3, 0, 0);}
    | exp OPERATOR_LE exp																									{$$=astreeCreate(AST_LE, 0, $1, $3, 0, 0);}
    | exp OPERATOR_DIF exp																								{$$=astreeCreate(AST_DIF, 0, $1, $3, 0, 0);}
    | exp OPERATOR_AND exp																								{$$=astreeCreate(AST_AND, 0, $1, $3, 0, 0);}
    | exp OPERATOR_OR exp																									{$$=astreeCreate(AST_OR, 0, $1, $3, 0, 0);}
    | OPERATOR_NOT exp																										{$$=astreeCreate(AST_NOT, 0, $2, 0, 0, 0);}
    | '(' exp ')'																													{$$=astreeCreate(AST_PAREN, 0, $2, 0, 0, 0);}
    ;

l_args :																																	{$$=0;}
       | exp l_args_end																										{$$=astreeCreate(AST_ARGLSTINIT, 0, $1, $2, 0, 0);}
       ;

l_args_end :																															{$$=0;}
           | ',' exp l_args_end																						{$$=astreeCreate(AST_ARGLST, 0, $2, $3, 0, 0);}
           ;

l_print : element_print l_print_end																				{$$=astreeCreate(AST_PRINTLSTINIT, 0, $1, $2, 0, 0);}
				;

l_print_end :																															{$$=0;}
	          | ',' element_print l_print_end																{$$=astreeCreate(AST_PRINTLST, 0, $2, $3, 0, 0);}
            ;

element_print : LIT_STRING																								{$$=astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
              | exp																												{$$=$1;}
              ;

%%

int yyerror(char *err){

	fprintf(stderr, "ERROR in line = %d\n", getLineNumber());
	exit(3);
}

astree_node * getAST(){
	return root;
}
