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
				
	setIdentifierTypes(root); 
    setNodeTypes(root);
	checkUndeclared();
	checkUsage(root);
	checkOperands(root);

    return SemanticErrors;
}

void setIdentifierTypes(astree_node* node){
    if(node == NULL) return;

    switch (node->type){
    case AST_DECVAR:
        if(node->symbol->type != SYMBOL_IDENTIFIER){
            fprintf(stderr,"Semantic ERROR in line %d: Variable %s redeclaration.\n", node->lineNumber, node->symbol->text);
            SemanticErrors++;
        }
        else{
            node->symbol->type = SYMBOL_VAR;
            if(node->sons[0]->type == AST_TPBYTE) node->symbol->datatype = DATATYPE_BYTE;
            else if(node->sons[0]->type == AST_TPINT) node->symbol->datatype = DATATYPE_INT;
            else if(node->sons[0]->type == AST_TPFLOAT) node->symbol->datatype = DATATYPE_FLOAT;
        }
        break;
    case AST_DECVEC:
        if(node->symbol->type != SYMBOL_IDENTIFIER){
            fprintf(stderr,"Semantic ERROR in line %d: Vector %s redeclaration.\n", node->lineNumber, node->symbol->text);
            SemanticErrors++;
        }
        else{
            node->symbol->type = SYMBOL_VEC;
            if(node->sons[0]->type == AST_TPBYTE) node->symbol->datatype = DATATYPE_BYTE;
            else if(node->sons[0]->type == AST_TPINT) node->symbol->datatype = DATATYPE_INT;
            else if(node->sons[0]->type == AST_TPFLOAT) node->symbol->datatype = DATATYPE_FLOAT;
        }
        break;
    case AST_DECFUNC:
        if(node->symbol->type != SYMBOL_IDENTIFIER){
            fprintf(stderr,"Semantic ERROR in line %d: Function %s redeclaration.\n", node->lineNumber, node->symbol->text);
            SemanticErrors++;
        }
        else{
            node->symbol->type = SYMBOL_FUNC;
            if(node->sons[0]->type == AST_TPBYTE) node->symbol->datatype = DATATYPE_BYTE;
            else if(node->sons[0]->type == AST_TPINT) node->symbol->datatype = DATATYPE_INT;
            else if(node->sons[0]->type == AST_TPFLOAT) node->symbol->datatype = DATATYPE_FLOAT;
        }
        break;
    case AST_PARAM:
        if(node->symbol->type != SYMBOL_IDENTIFIER){
            fprintf(stderr,"Semantic ERROR in line %d: Parameter %s redeclaration.\n", node->lineNumber, node->symbol->text);
            SemanticErrors++;
        }
        else{
            node->symbol->type = SYMBOL_PARAM;
            if(node->sons[0]->type == AST_TPBYTE) node->symbol->datatype = DATATYPE_BYTE;
            else if(node->sons[0]->type == AST_TPINT) node->symbol->datatype = DATATYPE_INT;
            else if(node->sons[0]->type == AST_TPFLOAT) node->symbol->datatype = DATATYPE_FLOAT;
        }
        break;
    default:
        break;
    }

    for(int i = 0; i < MAX_SONS; i++)
        setIdentifierTypes(node->sons[i]);
}

void setNodeTypes(astree_node *node){
    if(node == NULL) return;

    for(int i = 0; i < MAX_SONS; i++){
        setNodeTypes(node->sons[i]);
    }

    if(node->type == AST_SYMBOL || node->type == AST_FUNC || node->type == AST_VEC){
        node->datatype = node->symbol->datatype;
    }
    else if(node->type == AST_PAREN){
        node->datatype = node->sons[0]->datatype;
    }
    else if(isAritmeticOp(node->type)){
        astree_node* son0 = node->sons[0];
        astree_node* son1 = node->sons[1];
        if(!isDatatypeCompatible(son0->datatype, son1->datatype) || son0->datatype == DATATYPE_BOOL || son1->datatype == DATATYPE_BOOL){
            fprintf(stderr, "Semantic ERROR in line %d: Aritmetic operation with incompatible data types.\n", node->lineNumber);
            SemanticErrors++;
        }
        node->datatype = greaterDatatype(son0->datatype, son1->datatype);
    }
    else if(isRelationalOp(node->type)){
        if(!isNumerical(node->sons[0]->datatype) || !isNumerical(node->sons[1]->datatype)){
            fprintf(stderr, "Semantic ERROR in line %d: Relational operation with incompatible data types.\n", node->lineNumber);
            SemanticErrors++;
        }
        node->datatype = DATATYPE_BOOL;
    }
    else if(isLogicalOp(node->type)){
        if(node->type == AST_NOT){
            if(node->sons[0]->datatype != DATATYPE_BOOL){
                fprintf(stderr, "Semantic ERROR in line %d: Logical operation with incompatible data types.\n", node->lineNumber);
                SemanticErrors++;
            }
        }
        else if(node->sons[0]->datatype != DATATYPE_BOOL || node->sons[1]->datatype != DATATYPE_BOOL){
            fprintf(stderr, "Semantic ERROR in line %d: Logical operation with incompatible data types.\n", node->lineNumber);
            SemanticErrors++;
        }
        node->datatype = DATATYPE_BOOL;
    }
}

void checkUndeclared(){
	int undeclaredVariables = hashCheckUndeclared();
 	SemanticErrors += undeclaredVariables;	
}

void checkUsage(astree_node *node){
    if(node == NULL) return;

    switch (node->type){
        case AST_ATTR:
            if(node->symbol->type != SYMBOL_VAR){
                fprintf(stderr, "Semantic ERROR in line %d: Attribution must be to a scalar variable.\n", node->lineNumber);
                SemanticErrors++;
            }
            if(!isDatatypeCompatible(node->symbol->datatype, node->sons[0]->datatype)){
                fprintf(stderr, "Semantic ERROR in line %d: Attribution with incompatible data type.\n", node->lineNumber);
                SemanticErrors++;
            }
            break;
        
        case AST_VECATTR:
            if(node->symbol->type != SYMBOL_VEC){
                fprintf(stderr, "Semantic ERROR in line %d: Indexing only allowed for vectors.\n", node->lineNumber);
                SemanticErrors++;
            }
            if(!isDatatypeCompatible(node->symbol->datatype, node->sons[1]->datatype)){
                fprintf(stderr, "Semantic ERROR in line %d: Attribution with incompatible data type.\n", node->lineNumber);
                SemanticErrors++;
            }
            if(!isInteger(node->sons[0]->datatype)){
                fprintf(stderr, "Semantic ERROR in line %d: Index must be an integer.\n", node->lineNumber);
                SemanticErrors++;
            }
            break;
        case AST_FUNC:
            // TODO checar tipo dos parametros, numero de parametros e tipo do retorno
            break;
        case AST_READ:
            if(node->symbol->type != SYMBOL_VAR){
				fprintf(stderr, "Semantic ERROR in line %d: read only allowed to scalar variables.\n", node->lineNumber);
				SemanticErrors++;
			}
            break;
        case AST_PRINT:
            // Acho que a análise sintática já filtra todos os erros do print, checar isso.
            break;
        case AST_IF:
        case AST_IFELSE:
        case AST_LOOP:
            if(node->sons[0]->datatype != DATATYPE_BOOL){
                fprintf(stderr, "Semantic ERROR in line %d: Condidtion must be a boolean expression.\n", node->lineNumber);
				SemanticErrors++;
            }
            break;
        default:
            break;
    }

    for(int i = 0; i < MAX_SONS; i++)
		checkUsage(node->sons[i]);
}

void checkOperands(astree_node *node){

}

int isDatatypeCompatible(int datatype1, int datatype2){
    return (isInteger(datatype1) && isInteger(datatype2)) || (datatype1 == datatype2);
}

int isInteger(int datatype){
    return (datatype == DATATYPE_BYTE || datatype == DATATYPE_INT);
}

int isNumerical(int datatype){
    return (datatype == DATATYPE_BYTE || datatype == DATATYPE_INT || datatype == DATATYPE_FLOAT);
}

int isRelationalOp(int nodetype){
    return (nodetype == AST_LESS || nodetype == AST_GREAT || nodetype == AST_EQ || nodetype == AST_LE || nodetype == AST_GE || nodetype == AST_DIF);
}

int isAritmeticOp(int nodetype){
    return (nodetype == AST_ADD || nodetype == AST_SUB || nodetype == AST_MUL || nodetype == AST_DIV);
}

int isLogicalOp(int nodetype){
    return (nodetype == AST_AND || nodetype == AST_OR || nodetype == AST_NOT);
}

int greaterDatatype(int type1, int type2){
    return type1 > type2 ? type1 : type2;
}