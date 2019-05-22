#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "astree.h"
#include <string.h>
#include <stdbool.h>

int semanticVerification(astree_node* root);

void setIdentifierTypes(astree_node* node);

void setNodeTypes(astree_node *node);

void checkUndeclared();

void checkUsage(astree_node* node);

void checkOperands(astree_node* node);

int isDatatypeCompatible(int datatype1, int datatype2);

int isInteger(int datatype);

int isNumerical(int datatype);

int isRelationalOp(int nodetype);

int isAritmeticOp(int nodetype);

int isLogicalOp(int nodetype);

int greaterDatatype(int type1, int type2);

void validateFunction(astree_node * node);

astree_node * findFunctionDeclaration(char * name, astree_node * node);

bool checkNumberOfArguments(astree_node * node, astree_node * declaration);

int getNumberOfArguments(astree_node * node);

bool hasSameDatatype(astree_node * node1, astree_node * node2);

void compareCalledArguments(astree_node * node, astree_node * declaration);

void isReturnCompatible(astree_node * node, int datatype);

void checkReturns(astree_node * node);

#endif
