#ifndef TAC_H
#define TAC_H
/* 
	ETAPA 5 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre 
*/

#include "hash.h"
#include "astree.h"

#define TAC_SYMBOL
#define TAC_MOVE
#define TAC_ADD
#define TAC_MUL
#define TAC_LABEL
#define TAC_BEGINFUN
#define TAC_ENDFUN
#define TAC_IFZ
#define TAC_JUMP
#define TAC_CALL
#define TAC_ARG
#define TAC_MUL
#define TAC_RET
#define TAC_PRINT
#define TAC_READ

typedef struct tac_struct{
	int type;
	Hash_Node *res;
	Hash_Node *op1;
	Hash_Node *op2;
	struct tac_struct *prev;
	struct tac_struct *next; 
} tac;

#endif