/*
	ETAPA 3 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre
*/

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"

extern FILE* yyin;
extern FILE* file();
extern int isRunning();
extern int getLineNumber();
extern int yyparse();
extern void initMe();
extern void hashPrint();
extern astree_node * getAST();

int main(int argc, char *argv[]){

    int token;

	if(argc < 2){
		fprintf(stderr,"Call: ./etapa2 nomearquivo\n");
		return 1;
	}
	if(!(file(argv[1]))){
		fprintf(stderr,"Cannot open file %s\n",argv[1]);
		return 2;
	}

	initMe();

	yyparse();

	// hashPrint();

	fprintf(stderr, "Compiled Successfully\n");

	fprintf(stderr, "Uncompiling!\n");

	FILE * out;
	out = fopen("out.txt", "w+");

	uncompileAST(getAST(), out);

 return 0;
}
