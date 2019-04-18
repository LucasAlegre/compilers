#ifndef ASTREE
#define ASTREE

#define MAX_SONS

#include "hash.h"

typedef struct astree
{
    int type;
    hash_node *symbol;
    struct astree *sons[MAX_SONS];
} astree_node;


astree_node* astreeCreate(int type, hash_node* symbol, astree_node* son0, astree_node* son1, astree_node* son2, astree_node* son3);

void astreePrint(int level, astree_node *node);


#endif