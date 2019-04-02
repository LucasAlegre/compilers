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

%%

prog:
    ;

%%

int yyerror(char *err){
	
	fprintf(stderr, "ERRO na linha = %d\n", getLineNumber());
	exit(3);
}