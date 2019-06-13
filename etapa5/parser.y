%{
/*	ETAPA 4 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre
*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "hash.h"
	#include "astree.h"
	#include "semantic.h"
	#include "tac.h"

	int yylex();
	int yyerror(char *message);
	extern int getLineNumber();

  int SemanticErrors;
	astree_node *Root;

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

program : l_declarations                                                  {Root=$$; astree_print(0, Root); SemanticErrors=semanticVerification(Root); printAllTacs(rewindTac(createTacs(Root, 0)));}
    		;

l_declarations : declaration l_declarations                               {$$=astree_create(AST_LDEC, 0, $1, $2, 0, 0, getLineNumber());}
							 | 																													{$$=0;}
               ;

declaration : tipo TK_IDENTIFIER '=' literal ';'													{$$=astree_create(AST_DECVAR, $2, $1, $4, 0, 0, getLineNumber());}
            | tipo TK_IDENTIFIER '[' LIT_INTEGER ']' init_vector ';'			{$$=astree_create(AST_DECVEC, $2, $1, astree_create(AST_SYMBOL, $4, 0, 0, 0, 0, getLineNumber()), $6, 0, getLineNumber());}
            | tipo TK_IDENTIFIER '(' l_param ')' bloco ';'								{$$=astree_create(AST_DECFUNC, $2, $1, $4, $6, 0, getLineNumber());}
            ;

tipo : KW_BYTE																														{$$=astree_create(AST_TPBYTE, 0, 0, 0, 0, 0, getLineNumber());}
     | KW_INT																															{$$=astree_create(AST_TPINT, 0, 0, 0, 0, 0, getLineNumber());}
     | KW_FLOAT																														{$$=astree_create(AST_TPFLOAT, 0, 0, 0, 0, 0, getLineNumber());}
     ;

literal : LIT_INTEGER																											{$$=astree_create(AST_SYMBOL, $1, 0, 0, 0, 0, getLineNumber());}
        | LIT_FLOAT																												{$$=astree_create(AST_SYMBOL, $1, 0, 0, 0, 0, getLineNumber());}
        | LIT_CHAR																												{$$=astree_create(AST_SYMBOL, $1, 0, 0, 0, 0, getLineNumber());}
        ;

init_vector :																															{$$=0;}
            | ':' literal vector_elements																	{$$=astree_create(AST_VECINIT, 0, $2, $3, 0, 0, getLineNumber());}
            ;

vector_elements :																													{$$=0;}
                | literal vector_elements																	{$$=astree_create(AST_VECELEMENTS, 0, $1, $2, 0, 0, getLineNumber());}
                ;

l_param :																																	{$$=0;}
        | param param_end																									{$$=astree_create(AST_PARAMINIT, 0, $1, $2, 0, 0, getLineNumber());}
        ;

param_end :																																{$$=0;}
					| ',' param param_end																						{$$=astree_create(AST_PARAMLST, 0, $2, $3, 0, 0, getLineNumber());}
          ;

param : tipo TK_IDENTIFIER																								{$$=astree_create(AST_PARAM, $2, $1, 0, 0, 0, getLineNumber());}
      ;

bloco : '{' l_cmd '}'																											{$$=astree_create(AST_BLOCK, 0, $2, 0, 0, 0, getLineNumber());}
      ;

l_cmd : cmd l_cmd_end																											{$$=astree_create(AST_CMDLSTINIT, 0, $1, $2, 0, 0, getLineNumber());}
			;

l_cmd_end :																																{$$=0;}
          | ';' cmd l_cmd_end																							{$$=astree_create(AST_CMDLST, 0, $2, $3, 0, 0, getLineNumber());}
          ;

cmd :																																			{$$=0;}
    | bloco																																{$$=$1;}
    | TK_IDENTIFIER '=' exp																								{$$=astree_create(AST_ATTR, $1, $3, 0, 0, 0, getLineNumber());}
    | TK_IDENTIFIER '[' exp ']' '=' exp																		{$$=astree_create(AST_VECATTR, $1, $3, $6, 0, 0, getLineNumber());}
    | KW_READ TK_IDENTIFIER																								{$$=astree_create(AST_READ, $2, 0, 0, 0, 0, getLineNumber());}
    | KW_PRINT l_print																										{$$=astree_create(AST_PRINT, 0, $2, 0, 0, 0, getLineNumber());}
    | KW_RETURN exp																												{$$=astree_create(AST_RETURN, 0, $2, 0, 0, 0, getLineNumber());}
    | KW_IF '(' exp ')' KW_THEN cmd																				{$$=astree_create(AST_IF, 0, $3, $6, 0, 0, getLineNumber());}
    | KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd														{$$=astree_create(AST_IFELSE, 0, $3, $6, $8, 0, getLineNumber());}
    | KW_LOOP '(' exp ')' cmd																							{$$=astree_create(AST_LOOP, 0, $3, $5, 0, 0, getLineNumber());}
    | KW_LEAP 																														{$$=astree_create(AST_LEAP, 0, 0, 0, 0, 0, getLineNumber());}
    ;

exp : TK_IDENTIFIER																												{$$=astree_create(AST_SYMBOL, $1, 0, 0, 0, 0, getLineNumber());}
    | TK_IDENTIFIER '[' exp ']'																						{$$=astree_create(AST_VEC, $1, $3, 0, 0, 0, getLineNumber());}
    | TK_IDENTIFIER '(' l_args ')'																				{$$=astree_create(AST_FUNC, $1, $3, 0, 0, 0, getLineNumber());}
    | literal																															{$$=$1;}
    | exp '+' exp																													{$$=astree_create(AST_ADD, 0, $1, $3, 0, 0, getLineNumber());}
    | exp '-' exp																													{$$=astree_create(AST_SUB, 0, $1, $3, 0, 0, getLineNumber());}
    | exp '*' exp																													{$$=astree_create(AST_MUL, 0, $1, $3, 0, 0, getLineNumber());}
    | exp '/' exp																													{$$=astree_create(AST_DIV, 0, $1, $3, 0, 0, getLineNumber());}
    | exp '<' exp																													{$$=astree_create(AST_LESS, 0, $1, $3, 0, 0, getLineNumber());}
    | exp '>' exp																													{$$=astree_create(AST_GREAT, 0, $1, $3, 0, 0, getLineNumber());}
    | exp OPERATOR_EQ exp																									{$$=astree_create(AST_EQ, 0, $1, $3, 0, 0, getLineNumber());}
    | exp OPERATOR_GE exp																									{$$=astree_create(AST_GE, 0, $1, $3, 0, 0, getLineNumber());}
    | exp OPERATOR_LE exp																									{$$=astree_create(AST_LE, 0, $1, $3, 0, 0, getLineNumber());}
    | exp OPERATOR_DIF exp																								{$$=astree_create(AST_DIF, 0, $1, $3, 0, 0, getLineNumber());}
    | exp OPERATOR_AND exp																								{$$=astree_create(AST_AND, 0, $1, $3, 0, 0, getLineNumber());}
    | exp OPERATOR_OR exp																									{$$=astree_create(AST_OR, 0, $1, $3, 0, 0, getLineNumber());}
    | OPERATOR_NOT exp																										{$$=astree_create(AST_NOT, 0, $2, 0, 0, 0, getLineNumber());}
    | '(' exp ')'																													{$$=astree_create(AST_PAREN, 0, $2, 0, 0, 0, getLineNumber());}
    ;

l_args :																																	{$$=0;}
       | exp l_args_end																										{$$=astree_create(AST_ARGLSTINIT, 0, $1, $2, 0, 0, getLineNumber());}
       ;

l_args_end :																															{$$=0;}
           | ',' exp l_args_end																						{$$=astree_create(AST_ARGLST, 0, $2, $3, 0, 0, getLineNumber());}
           ;

l_print : element_print l_print_end																				{$$=astree_create(AST_PRINTLSTINIT, 0, $1, $2, 0, 0, getLineNumber());}
				;

l_print_end :																															{$$=0;}
	          | ',' element_print l_print_end																{$$=astree_create(AST_PRINTLST, 0, $2, $3, 0, 0, getLineNumber());}
            ;

element_print : LIT_STRING																								{$$=astree_create(AST_SYMBOL, $1, 0, 0, 0, 0, getLineNumber());}
              | exp																												{$$=$1;}
              ;

%%

void checkSemantic(){
  if(SemanticErrors > 0){
    fprintf(stderr, "%d Semantic Errors in Total.\n", SemanticErrors);
    exit(4);
  }
}

int yyerror(char *err){

	fprintf(stderr, "Syntactic ERROR in line %d.\n", getLineNumber());
	exit(3);
}

astree_node* getAST(){
	return Root;
}
