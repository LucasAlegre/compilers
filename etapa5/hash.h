/* 
	ETAPA 1 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre 
*/

#ifndef HASH_H
#define HASH_H

#define HASH_SIZE 997

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_FLOAT 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_IDENTIFIER 5

#define SYMBOL_VAR 10
#define SYMBOL_VEC 11
#define SYMBOL_FUNC 12
#define SYMBOL_PARAM 13

#define DATATYPE_BYTE 14
#define DATATYPE_INT 15
#define DATATYPE_FLOAT 16
#define DATATYPE_BOOL 17

typedef struct hash_node{
    int type;
    int datatype;
    char* text;
    struct hash_node* next;
} hash_node;

hash_node* Table[HASH_SIZE];


void hashInit(void);

hash_node* hashInsert(int type, char* text);

hash_node* hashFind(char *text);

int hashAddress(char *text);

void hashPrint(void);

int hashCheckUndeclared();

hash_node * makeTemp();
hash_node * makeLabel();

#endif
