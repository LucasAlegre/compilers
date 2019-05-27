#ifndef SEMANTIC_H
#define SEMANTIC_H

/*
	ETAPA 4 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre
*/

#include "astree.h"
#include <string.h>
#include <stdbool.h>

int semanticVerification(astree_node* root);

void setIdentifierTypes(astree_node* node);

void setNodeTypes(astree_node *node);

void checkUndeclared();

void checkUsage(astree_node* node);

bool checkEveryVecElement(astree_node * node, int datatype);

int isDatatypeCompatible(int datatype1, int datatype2);

int isInteger(int datatype);

int isNumerical(int datatype);

int isRelationalOp(int nodetype);

int isAritmeticOp(int nodetype);

int isLogicalOp(int nodetype);

int greaterDatatype(int type1, int type2);

void validateFunction(astree_node * node);

astree_node *findFunctionDeclaration(char * name, astree_node * node);

bool checkNumberOfArguments(astree_node * node, astree_node * declaration);

int getNumberOfArguments(astree_node * node);

void compareCalledArguments(astree_node * node, astree_node * declaration);

void isReturnCompatible(astree_node * node, int datatype);

void checkReturns(astree_node *node);

#endif
