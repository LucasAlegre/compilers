#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "astree.h"

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

#endif
