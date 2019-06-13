#ifndef TAC_H
#define TAC_H
/* 
	ETAPA 5 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre 
*/
#include "astree.h"

#define TAC_SYMBOL 0
#define TAC_MOVE 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MUL 4
#define TAC_DIV 5
#define TAC_GREAT 6
#define TAC_LESS 7
#define TAC_GE 8
#define TAC_LE 9
#define TAC_EQ 10
#define TAC_DIF 11
#define TAC_AND 12
#define TAC_OR 13
#define TAC_NOT 14
#define TAC_LABEL 15
#define TAC_BEGINFUN 16
#define TAC_ARGPUSH 17
#define TAC_ENDFUN 18
#define TAC_IFZ 19
#define TAC_JUMP 20
#define TAC_CALL 21
#define TAC_ARG 22
#define TAC_RET 23
#define TAC_PRINT 24
#define TAC_READ 25
#define TAC_VECATTR 26
#define TAC_VEC 27

typedef struct tac_struct{
	int type;
	hash_node *res;
	hash_node *op1;
	hash_node *op2;
	struct tac_struct *prev;
	struct tac_struct *next; 
} tac;

tac* newTac(int type, hash_node *res, hash_node *op1, hash_node *op2);
tac* tacJoin(tac* l1, tac* l2);
void printAllTacs(tac* l);
tac* rewindTac(tac* l);
void printTac(tac* l);
tac* createTacs(astree_node *node, hash_node *currentLoopLabel);

tac* createBinop(int type, tac* sons[]);
tac* createIf(tac* sons[]);
tac* createLoop(tac* sons[], hash_node *label);
tac* createLeap(tac* sons[], hash_node *currentLoopLabel);
tac* createFunction(tac* symbol, tac* params, tac* code);

#endif
