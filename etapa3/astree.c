#include "hash.h"
#include "astree.h"
#include <stdlib.h>

astree_node* astreeCreate(int type, hash_node* symbol, astree_node* son0, astree_node* son1, astree_node* son2, astree_node* son3){
    astree_node *node = calloc(1, sizeof(astree_node));
    node->type = type;
    node->symbol = symbol;
    node->sons[0] = son0;
    node->sons[1] = son1;
    node->sons[2] = son2;
    node->sons[3] = son3;

    return node;
}

void astreePrint(int level, astree_node *node){

}