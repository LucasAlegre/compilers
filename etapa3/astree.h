#ifndef ASTREE
#define ASTREE

#define MAX_SONS
#define AST_LDEC
#define AST_DECVAR
#define AST_DECVEC
#define AST_DECFUNC
#define AST_TPBYTE
#define AST_TPINT
#define AST_TPFLOAT
#define AST_SYMBOL
#define AST_VECINIT
#define AST_VECELEMENTS
#define AST_PARAMINIT
#define AST_PARAMLST
#define AST_PARAM
#define AST_BLOCK
#define AST_CMDLSTINIT
#define AST_CMDLST
#define AST_ATTR
#define AST_VECATTR
#define AST_READ
#define AST_PRINT
#define AST_RETURN
#define AST_IF
#define AST_LOOP
#define AST_IFELSE
#define AST_LEAP
#define AST_VEC
#define AST_FUNC
#define AST_SUM
#define AST_DEC
#define AST_MUL
#define AST_DIV
#define AST_LESS
#define AST_GREAT
#define AST_EQ
#define AST_GE
#define AST_LE
#define AST_DIF
#define AST_AND
#define AST_OR
#define AST_NOT
#define AST_PAREN
#define AST_ARGLSTINIT
#define AST_ARGLST
#define AST_PRINTLSTINIT
#define AST_PRINTLST



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
