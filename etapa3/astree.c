#include "hash.h"
#include "astree.h"
#include <stdlib.h>
#include <stdio.h>

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
  if(node == NULL)
    return;

  int i;
  for(i = 0; i < level; i++)
    fprintf(stderr, "  ");

  fprintf(stderr, "AST( ");

  switch(node->type){
    case AST_LDEC :fprintf(stderr, "AST_LDEC"); break;
    case AST_DECVAR :fprintf(stderr, "AST_DECVAR"); break;
    case AST_DECVEC :fprintf(stderr, "AST_DECVEC"); break;
    case AST_DECFUNC :fprintf(stderr, "AST_DECFUNC"); break;
    case AST_TPBYTE :fprintf(stderr, "AST_TPBYTE"); break;
    case AST_TPINT :fprintf(stderr, "AST_TPINT"); break;
    case AST_TPFLOAT :fprintf(stderr, "AST_TPFLOAT"); break;
    case AST_SYMBOL :fprintf(stderr, "AST_SYMBOL"); break;
    case AST_VECINIT :fprintf(stderr, "AST_VECINIT"); break;
    case AST_VECELEMENTS :fprintf(stderr, "AST_VECELEMENTS"); break;
    case AST_PARAMINIT :fprintf(stderr, "AST_PARAMINIT"); break;
    case AST_PARAMLST :fprintf(stderr, "AST_PARAMLST"); break;
    case AST_PARAM :fprintf(stderr, "AST_PARAM"); break;
    case AST_BLOCK :fprintf(stderr, "AST_BLOCK"); break;
    case AST_CMDLSTINIT :fprintf(stderr, "AST_CMDLSTINIT"); break;
    case AST_CMDLST :fprintf(stderr, "AST_CMDLST"); break;
    case AST_ATTR :fprintf(stderr, "AST_ATTR"); break;
    case AST_VECATTR :fprintf(stderr, "AST_VECATTR"); break;
    case AST_READ :fprintf(stderr, "AST_READ"); break;
    case AST_PRINT :fprintf(stderr, "AST_PRINT"); break;
    case AST_RETURN :fprintf(stderr, "AST_RETURN"); break;
    case AST_IF :fprintf(stderr, "AST_IF"); break;
    case AST_LOOP :fprintf(stderr, "AST_LOOP"); break;
    case AST_IFELSE :fprintf(stderr, "AST_IFELSE"); break;
    case AST_LEAP :fprintf(stderr, "AST_LEAP"); break;
    case AST_VEC :fprintf(stderr, "AST_VEC"); break;
    case AST_FUNC :fprintf(stderr, "AST_FUNC"); break;
    case AST_SUM :fprintf(stderr, "AST_SUM"); break;
    case AST_DEC :fprintf(stderr, "AST_DEC"); break;
    case AST_MUL :fprintf(stderr, "AST_MUL"); break;
    case AST_DIV :fprintf(stderr, "AST_DIV"); break;
    case AST_LESS :fprintf(stderr, "AST_LESS"); break;
    case AST_GREAT :fprintf(stderr, "AST_GREAT"); break;
    case AST_EQ :fprintf(stderr, "AST_EQ"); break;
    case AST_GE :fprintf(stderr, "AST_GE"); break;
    case AST_LE :fprintf(stderr, "AST_LE"); break;
    case AST_DIF :fprintf(stderr, "AST_DIF"); break;
    case AST_AND :fprintf(stderr, "AST_AND"); break;
    case AST_OR :fprintf(stderr, "AST_OR"); break;
    case AST_NOT :fprintf(stderr, "AST_NOT"); break;
    case AST_PAREN :fprintf(stderr, "AST_PAREN"); break;
    case AST_ARGLSTINIT :fprintf(stderr, "AST_ARGLSTINIT"); break;
    case AST_ARGLST :fprintf(stderr, "AST_ARGLST"); break;
    case AST_PRINTLSTINIT :fprintf(stderr, "AST_PRINTLSTINIT"); break;
    case AST_PRINTLST :fprintf(stderr, "AST_PRINTLST"); break;
  }

  if(node->symbol != NULL)
    fprintf(stderr, ", %s )\n", node->symbol->text);
  else
    fprintf(stderr, " )\n");

  for(i = 0; i < MAX_SONS; i++)
    astreePrint(level+1, node->sons[i]);
}

void uncompileAST(astree_node * root, FILE * file){

  if(node == NULL)
    return;

  int i;
  for(i = 0; i < level; i++)
    fprintf(stderr, "  ");

  fprintf(stderr, "AST( ");

  switch(node->type){
    case AST_LDEC :
      uncompileAST(root->son[0], FILE *file);
      uncompileAST(root->son[1], FILE *file);
      break;
    case AST_DECVAR :
      uncompileAST(root->son[0], FILE *file);
      fprintf(file, " %s = ", root->symbol->text);
      uncompileAST(root->son[1], FILE *file);
      fprintf(file, ";\n");
      break;
    case AST_DECVEC :
      fprintf(file, "AST_DECVEC");
      break;
    case AST_DECFUNC :
      fprintf(file, "AST_DECFUNC");
      break;
    case AST_TPBYTE :
      fprintf(file, "AST_TPBYTE");
      break;
    case AST_TPINT :
      fprintf(file, "AST_TPINT");
      break;
    case AST_TPFLOAT :
      fprintf(file, "AST_TPFLOAT");
      break;
    case AST_SYMBOL :
      fprintf(file, "AST_SYMBOL");
      break;
    case AST_VECINIT :
      fprintf(file, "AST_VECINIT");
      break;
    case AST_VECELEMENTS :
      fprintf(file, "AST_VECELEMENTS");
      break;
    case AST_PARAMINIT :
      fprintf(file, "AST_PARAMINIT");
      break;
    case AST_PARAMLST :
      fprintf(file, "AST_PARAMLST");
      break;
    case AST_PARAM :
      fprintf(file, "AST_PARAM");
      break;
    case AST_BLOCK :
      fprintf(file, "AST_BLOCK");
      break;
    case AST_CMDLSTINIT :
      fprintf(file, "AST_CMDLSTINIT");
      break;
    case AST_CMDLST :
      fprintf(file, "AST_CMDLST");
      break;
    case AST_ATTR :
      fprintf(file, "AST_ATTR");
      break;
    case AST_VECATTR :
      fprintf(file, "AST_VECATTR");
      break;
    case AST_READ :
      fprintf(file, "AST_READ");
      break;
    case AST_PRINT :
      fprintf(file, "AST_PRINT");
      break;
    case AST_RETURN :
      fprintf(file, "AST_RETURN");
      break;
    case AST_IF :
      fprintf(file, "AST_IF");
      break;
    case AST_LOOP :
      fprintf(file, "AST_LOOP");
      break;
    case AST_IFELSE :
      fprintf(file, "AST_IFELSE");
      break;
    case AST_LEAP :
      fprintf(file, "AST_LEAP");
      break;
    case AST_VEC :
      fprintf(file, "AST_VEC");
      break;
    case AST_FUNC :
      fprintf(file, "AST_FUNC");
      break;
    case AST_SUM :
      fprintf(file, "AST_SUM");
      break;
    case AST_DEC :
      fprintf(file, "AST_DEC");
      break;
    case AST_MUL :
      fprintf(file, "AST_MUL");
      break;
    case AST_DIV :
      fprintf(file, "AST_DIV");
      break;
    case AST_LESS :
      fprintf(file, "AST_LESS");
      break;
    case AST_GREAT :
      fprintf(file, "AST_GREAT");
      break;
    case AST_EQ :
      fprintf(file, "AST_EQ");
      break;
    case AST_GE :
      fprintf(file, "AST_GE");
      break;
    case AST_LE :
      fprintf(file, "AST_LE");
      break;
    case AST_DIF :
      fprintf(file, "AST_DIF");
      break;
    case AST_AND :
      fprintf(file, "AST_AND");
      break;
    case AST_OR :
      fprintf(file, "AST_OR");
      break;
    case AST_NOT :
      fprintf(file, "AST_NOT");
      break;
    case AST_PAREN :
      fprintf(file, "AST_PAREN");
      break;
    case AST_ARGLSTINIT :
      fprintf(file, "AST_ARGLSTINIT");
      break;
    case AST_ARGLST :
      fprintf(file, "AST_ARGLST");
      break;
    case AST_PRINTLSTINIT :
      fprintf(file, "AST_PRINTLSTINIT");
      break;
    case AST_PRINTLST :
      fprintf(file, "AST_PRINTLST");
      break;
  }
}
