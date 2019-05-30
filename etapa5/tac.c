/* 
	ETAPA 5 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre 
*/

#include "tac.h"
#include "hash.h"
#include "stdlib.h"

tac* tacCreate(int type, hash_node *res, hash_node *op1, hash_node *op2)
{
	tac *n = (tac*) calloc(1, sizeof(tac));
	n->type = type;
	n->res = res;
	n->op1 = op1;
	n->op2 = op2;
	n->prev = NULL;
	n->next = NULL;	
	return n;
}

tac* tacJoin(tac* l1, tac* l2)
{
	tac* t;
	if(!l1) return l2;
	if(!l2) return l1;
	t = l2;
	while(t->prev){
		t = t->prev;	
	}
	t->prev = l1;
	return l2;
}