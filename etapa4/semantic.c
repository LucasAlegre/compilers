/*
	ETAPA 4 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre
*/

#include "semantic.h"
#include "astree.h"

int SemanticErrors = 0;
astree_node* ROOT;

int semanticVerification(astree_node* root){
    ROOT = root;	
				
	setTypes(root); 
	checkUndeclared();
	/*checkUsage(root);
	checkOperands(root); */

    return SemanticErrors;
}

void setTypes(astree_node* node){
    if(!node) return;

    if(node->type == AST_DECVAR){
        if(node->symbol->type != SYMBOL_IDENTIFIER){
            fprintf(stderr,"Semantic ERROR in line %d: Variable %s redeclaration.\n", node->lineNumber, node->symbol->text);
            SemanticErrors++;
        }
        else{
            node->symbol->type = SYMBOL_VAR;
            if(node->sons[0]->type == AST_TPBYTE) node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
            else if(node->sons[0]->type == AST_TPINT) node->symbol->datatype = SYMBOL_DATATYPE_INT;
            else if(node->sons[0]->type == AST_TPFLOAT) node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
        }
    }
    else if(node->type == AST_DECVEC){
        if(node->symbol->type != SYMBOL_IDENTIFIER){
            fprintf(stderr,"Semantic ERROR in line %d: Vector %s redeclaration.\n", node->lineNumber, node->symbol->text);
            SemanticErrors++;
        }
        else{
            node->symbol->type = SYMBOL_VEC;
            if(node->sons[0]->type == AST_TPBYTE) node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
            else if(node->sons[0]->type == AST_TPINT) node->symbol->datatype = SYMBOL_DATATYPE_INT;
            else if(node->sons[0]->type == AST_TPFLOAT) node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
        }
    }
    else if(node->type == AST_DECFUNC){
        if(node->symbol->type != SYMBOL_IDENTIFIER){
            fprintf(stderr,"Semantic ERROR in line %d: Function %s redeclaration.\n", node->lineNumber, node->symbol->text);
            SemanticErrors++;
        }
        else{
            node->symbol->type = SYMBOL_FUNC;
            if(node->sons[0]->type == AST_TPBYTE) node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
            else if(node->sons[0]->type == AST_TPINT) node->symbol->datatype = SYMBOL_DATATYPE_INT;
            else if(node->sons[0]->type == AST_TPFLOAT) node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
        }
    }
    else if(node->type == AST_PARAM){
        if(node->symbol->type != SYMBOL_IDENTIFIER){
            fprintf(stderr,"Semantic ERROR in line %d: Parameter %s redeclaration.\n", node->lineNumber, node->symbol->text);
            SemanticErrors++;
        }
        else{
            node->symbol->type = SYMBOL_PARAM;
            if(node->sons[0]->type == AST_TPBYTE) node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
            else if(node->sons[0]->type == AST_TPINT) node->symbol->datatype = SYMBOL_DATATYPE_INT;
            else if(node->sons[0]->type == AST_TPFLOAT) node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
        }
    }
    for(int i = 0; i < MAX_SONS; i++)
        setTypes(node->sons[i]);
}


void checkUndeclared(){
	int undeclaredVariables = hashCheckUndeclared();
 	SemanticErrors += undeclaredVariables;	
}
