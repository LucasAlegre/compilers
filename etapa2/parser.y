%{
/*	ETAPA 2 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre 
*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "hash.h"
	
	int yylex();
	int yyerror(char *message);
	extern int getLineNumber();

%}

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
%token TK_IDENTIFIER 
%token LIT_INTEGER   
%token LIT_FLOAT     
%token LIT_CHAR      
%token LIT_STRING    
%token TOKEN_ERROR

%left '<' '>'
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF OPERATOR_OR OPERATOR_AND OPERATOR_NOT
%left '+' '-'
%left '*' '/'


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

l_cmd : 
			| cmd l_cmd_end
			;

l_cmd_end : 
          | ';' cmd l_cmd_end
          ;

cmd :
    | bloco
    | TK_IDENTIFIER '=' expression
    | TK_IDENTIFIER '[' expression ']' '=' expression
    | KW_READ TK_IDENTIFIER
    | KW_PRINT l_print
    | KW_RETURN expression
    | KW_IF '(' expression ')' KW_THEN cmd else
    | KW_LOOP '(' expression ')' cmd
    | KW_LEAP
    ;

else :
     | KW_ELSE cmd
     ;

expression : TK_IDENTIFIER
           | TK_IDENTIFIER '[' expression ']'
           | TK_IDENTIFIER '(' l_args ')'
           | literal
           | expression '+' expression
           | expression '-' expression
           | expression '*' expression
           | expression '/' expression
           | expression '<' expression
					 | expression '>' expression
					 | expression OPERATOR_EQ expression  
           | expression OPERATOR_GE expression
           | expression OPERATOR_LE expression
					 | expression OPERATOR_DIF expression
           | expression OPERATOR_AND expression
           | expression OPERATOR_OR expression   
					 | OPERATOR_NOT expression
					 | '(' expression ')' 
	         ;

l_args : 
       | expression l_args_end
       ;

l_args_end :
           | ',' expression l_args_end
           ;

l_print : 
        | element_print l_print_end
        ;
 
l_print_end :
            | ',' element_print l_print_end
            ;

element_print : LIT_STRING
              | expression
              ; 

%%

int yyerror(char *err){
	
	fprintf(stderr, "ERROR in line = %d\n", getLineNumber());
	exit(3);
}
