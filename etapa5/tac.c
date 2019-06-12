/* 
	ETAPA 5 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre 
*/

#include "tac.h"
#include "hash.h"
#include "stdlib.h"

tac* newTac(int type, hash_node *res, hash_node *op1, hash_node *op2){
	tac *n = (tac*) calloc(1, sizeof(tac));
	n->type = type;
	n->res = res;
	n->op1 = op1;
	n->op2 = op2;
	n->prev = NULL;
	n->next = NULL;	
	return n;
}

tac* tacJoin(tac* l1, tac* l2){
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

void printAllTacs(tac* l){
	tac* t;
	for(t = l; t->next; t = t->next)
		printTac(t);	
}

tac* rewindTac(tac* l){
	tac* t;
	for(t = l; t->prev; t = t->prev)
		t->prev->next = t;
	return t;
}

void printTac(tac* l){
	
	if(l->type == TAC_SYMBOL) return;
	
	fprintf(stderr, "TAC(");
	switch(l->type){
		case TAC_MOVE: fprintf(stderr, "MOVE(");break;
		case TAC_ADD: fprintf(stderr, "ADD(");break;
		case TAC_SUB: fprintf(stderr, "SUB(");break;
		case TAC_MUL: fprintf(stderr, "MUL(");break;
		case TAC_GREAT: fprintf(stderr, "GREAT(");break;
		case TAC_LESS: fprintf(stderr, "LESS(");break;
		case TAC_GE: fprintf(stderr, "GE(");break;
		case TAC_LE: fprintf(stderr, "LE(");break;
		case TAC_EQ: fprintf(stderr, "EQ(");break;
		case TAC_DIF: fprintf(stderr, "DIF(");break;
		case TAC_AND: fprintf(stderr, "AND(");break;
		case TAC_OR: fprintf(stderr, "OR(");break;
		case TAC_NOT: fprintf(stderr, "NOT(");break;
		case TAC_DIV: fprintf(stderr, "DIV(");break;
		case TAC_LABEL: fprintf(stderr, "LABEL(");break;
		case TAC_BEGINFUN: fprintf(stderr, "BEGINFUN(");break;
		case TAC_ADDPARAM: fprintf(stderr, "ADDPARAM(");break;
		case TAC_ENDFUN: fprintf(stderr, "ENDFUN(");break;
		case TAC_IFZ: fprintf(stderr, "IFZ(");break;
		case TAC_JUMP: fprintf(stderr, "JUMP(");break;
		case TAC_CALL: fprintf(stderr, "CALL(");break;
		case TAC_ARG: fprintf(stderr, "ARG(");break;
		case TAC_RET: fprintf(stderr, "RET(");break;
		case TAC_PRINT: fprintf(stderr, "PRINT(");break;
		case TAC_READ: fprintf(stderr, "READ(");break;
		default: fprintf(stderr, "UNKNOWN TAC TYPE!(");break;
	}

	if(l->res)
		fprintf(stderr, "%s, ", l->res->text);
	else
		fprintf(stderr, "0, ");

	if(l->op1)
		fprintf(stderr, "%s, ", l->op1->text);
	else
		fprintf(stderr, "0, ");

	if(l->op2)
		fprintf(stderr, "%s", l->op2->text);
	else
		fprintf(stderr, "0");

	fprintf(stderr, "))\n");
}

tac* createTacs(astree_node * node){
	if(!node) return NULL;

	tac* sons[MAX_SONS];
	for(int i = 0; i < MAX_SONS; i++)
		sons[i] = createTacs(node->sons[i]);

	switch(node->type){
		//Binary operations
		case AST_SYMBOL: return newTac(TAC_SYMBOL, node->symbol, 0, 0);
		case AST_ADD: return createBinop(TAC_ADD, sons);
		case AST_SUB: return createBinop(TAC_SUB, sons);
		case AST_MUL: return createBinop(TAC_MUL, sons);
		case AST_DIV: return createBinop(TAC_DIV, sons);
		case AST_GREAT: return createBinop(TAC_GREAT, sons);
		case AST_LESS: return createBinop(TAC_LESS, sons);
		case AST_EQ: return createBinop(TAC_EQ, sons);
		case AST_GE: return createBinop(TAC_GE, sons);
		case AST_LE: return createBinop(TAC_LE, sons);
		case AST_DIF: return createBinop(TAC_DIF, sons);
		case AST_AND: return createBinop(TAC_AND, sons);
		case AST_OR: return createBinop(TAC_OR, sons);
		case AST_NOT: return createBinop(TAC_NOT, sons);

		case AST_ATTR: return tacJoin(sons[0], newTac(TAC_MOVE, node->symbol, sons[0]?sons[0]->res:0, 0));
		case AST_READ: return newTac(TAC_READ, node->symbol, 0, 0);

		case AST_RETURN: return tacJoin(sons[0], newTac(TAC_RET, makeTemp(), sons[0]?sons[0]->res:0, 0));
		case AST_IFELSE:
		case AST_IF: return createIf(sons);
		case AST_LOOP: return createLoop(sons);

///TODO: FUNCTIONS, PARAMETERS, ARGUMENTS AND VECTORS

		default: return tacJoin(tacJoin(tacJoin(sons[0], sons[1]), sons[2]), sons[3]);
	}
}

tac* createBinop(int type, tac* sons[]){
	hash_node * op1;
	hash_node * op2;
	if(sons[0]) op1 = sons[0]->res; else op1 = 0;
	if(sons[1]) op2 = sons[1]->res; else op2 = 0;
	return tacJoin(sons[0], tacJoin(sons[1], newTac(type, makeTemp(), op1, op2)));
}

tac* createIf(tac* sons[]){
	hash_node* ifLabel = makeLabel();
	tac* ifTac = tacJoin(sons[0], newTac(TAC_IFZ, ifLabel, sons[0]?sons[0]->res:0, 0));
	tac* ifLabelTac = newTac(TAC_LABEL, ifLabel, 0, 0);
	
	if(sons[2]){
		hash_node* elseLabel = makeLabel();
		tac* elseLabelTac = newTac(TAC_LABEL, elseLabel, 0, 0);
		tac* elseJumpTac = newTac(TAC_JUMP, elseLabel, 0, 0);
		tac* ifElseTac = tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(ifTac, sons[1]), elseJumpTac), ifLabelTac), sons[2]), elseLabelTac);
		return ifElseTac;
	}else{
		return tacJoin(tacJoin(ifTac, sons[1]), ifLabelTac);
	}
}

tac* createLoop(tac* sons[]){
	hash_node* whileLabel = makeLabel();
	hash_node* jumpLabel = makeLabel();

	tac* whileTac = newTac(TAC_IFZ, whileLabel, sons[0]?sons[0]->res:0, 0);
	tac* whileLabelTac = newTac(TAC_LABEL, whileLabel, 0, 0);
	tac* jumpTac = newTac(TAC_JUMP, jumpLabel, 0, 0);
	tac* jumpLabelTac= newTac(TAC_LABEL, jumpLabel, 0, 0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(whileLabelTac, sons[0]), whileTac), sons[1]), jumpTac), jumpLabelTac);
}
