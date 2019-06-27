#ifndef ASM_H
#define ASM_H

#include "tac.h"
#include "astree.h"

void johannNumberConversion(char* johann, char* out);

void addTemporaries(FILE* out);

void addImmediates(FILE* out);

void addData(FILE* out, astree_node* node);

void asmGenerate(tac *firstTac, astree_node *ast);


#endif