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
%type <astree> else
%type <astree> exp
%type <astree> l_args
%type <astree> l_args_end
%type <astree> l_print
%type <astree> l_print_end
%type <astree> element_print

%start program

%%

program : l_declarations
    	;

l_declarations : declaration l_declarations            
               |
               ;

declaration : tipo TK_IDENTIFIER '=' literal ';'
            | tipo TK_IDENTIFIER '[' LIT_INTEGER ']' init_vector ';'
            | tipo TK_IDENTIFIER '(' l_param ')' bloco ';'
            ;

tipo : KW_BYTE
     | KW_INT
     | KW_FLOAT
     ;

literal : LIT_INTEGER
        | LIT_FLOAT
        | LIT_CHAR
        ;

init_vector :
            | ':' literal vector_elements
            ;

vector_elements : 
                | literal vector_elements
                ;

l_param : 
        | param param_end
        ;

param_end :
					| ',' param param_end
          ;

param : tipo TK_IDENTIFIER
      ;

bloco : '{' l_cmd '}'
      ;

l_cmd : cmd l_cmd_end
			;

l_cmd_end : 
          | ';' cmd l_cmd_end
          ;

cmd :
    | bloco
    | TK_IDENTIFIER '=' exp
    | TK_IDENTIFIER '[' exp ']' '=' exp
    | KW_READ TK_IDENTIFIER
    | KW_PRINT l_print
    | KW_RETURN exp
    | KW_IF '(' exp ')' KW_THEN cmd else
    | KW_LOOP '(' exp ')' cmd
    | KW_LEAP
    ;

else :
     | KW_ELSE cmd
     ;

exp : TK_IDENTIFIER
    | TK_IDENTIFIER '[' exp ']'
    | TK_IDENTIFIER '(' l_args ')'
    | literal
    | exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | exp '<' exp
    | exp '>' exp
    | exp OPERATOR_EQ exp  
    | exp OPERATOR_GE exp
    | exp OPERATOR_LE exp
    | exp OPERATOR_DIF exp
    | exp OPERATOR_AND exp
    | exp OPERATOR_OR exp   
    | OPERATOR_NOT exp
    | '(' exp ')' 
    ;

l_args : 
       | exp l_args_end
       ;

l_args_end :
           | ',' exp l_args_end
           ;

l_print : element_print l_print_end
        ;
 
l_print_end :
            | ',' element_print l_print_end
            ;

element_print : LIT_STRING
              | exp
              ; 

%%

int yyerror(char *err){
	
	fprintf(stderr, "ERROR in line = %d\n", getLineNumber());
	exit(3);
}
