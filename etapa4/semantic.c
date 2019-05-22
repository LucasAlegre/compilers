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
	checkReturns(root);

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
			validateFunction(node);
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

void validateFunction(astree_node * node){
	astree_node* declaration = findFunctionDeclaration(node->symbol->text, ROOT);
	if(checkNumberOfArguments(node, declaration)){
		compareCalledArguments(node->sons[0], declaration->sons[1]);					
	}
}

bool checkNumberOfArguments(astree_node * node, astree_node * declaration){
	int numberOfCalledArguments = getNumberOfArguments(node->sons[0]);
	int numberOfDeclaredArguments = getNumberOfArguments(declaration->sons[1]);	
	if(numberOfCalledArguments != numberOfDeclaredArguments){
		printf("Uncompatible number Of Arguments for function %s, declared : %d, called : %d", declaration->symbol->text, numberOfDeclaredArguments, numberOfCalledArguments);
		SemanticErrors++;
		return false;
	}
	return true;
}

astree_node * findFunctionDeclaration(char * name, astree_node * node){
	if(node->symbol != NULL && node->type == AST_DECFUNC && strcmp(node->symbol->text, name) == 0)
		return node;

	for(int i = 0; i < MAX_SONS; i++){
		if(node->sons[i] == NULL)
				return NULL;
		astree_node * finding = findFunctionDeclaration(name, node->sons[i]) ;
		if(finding != NULL)
				return finding;
	}
	return NULL;
}

int getNumberOfArguments(astree_node * node){
	if(node->sons[1] != NULL )
		return 1 + getNumberOfArguments(node->sons[1]);
	else
		return 1;
}

bool hasSameType(astree_node * node1, astree_node * node2){	
	bool equalDatatypes = node1->symbol->datatype == node2->symbol->datatype;
	bool integerDatatypes = (isInteger(node1->symbol->datatype) && isInteger(node2->symbol->datatype)); 
	bool vectorTypes = (node1->symbol->type == SYMBOL_VEC || node2->symbol->type == SYMBOL_VEC);
	return (equalDatatypes || integerDatatypes) && !vectorTypes;
}

void compareCalledArguments(astree_node * node, astree_node * declaration){
	
	if(node->sons[0] != NULL){
		if(!hasSameType(node->sons[0], declaration->sons[0])){
			printf("Incompatible types %s : %s\n", node->sons[0]->symbol->text, declaration->sons[0]->symbol->text);
			SemanticErrors++;
		}
		if(node->sons[1] != NULL)
			compareCalledArguments(node->sons[1], declaration->sons[1]);
	}
}

void isReturnCompatible(astree_node * node, int datatype){
	
	if(node!=NULL && node->type == AST_RETURN){
		if(node->datatype != datatype)
				printf("Return statement with wrong datatype in line %d", node->lineNumber);
		SemanticErrors++;
	}
	for(int i = 0; i <MAX_SONS; i++){
		if(node->sons[i] == NULL)
			break;
		isReturnCompatible(node->sons[i], datatype);
	}
}

void checkReturns(astree_node * node){
	if(node != NULL && node->type == AST_DECFUNC){
		isReturnCompatible(node, node->symbol->datatype);
	}

	for(int i = 0; i < MAX_SONS; i++){
		if(node->sons[i] == NULL)
			break;
		checkReturns(node->sons[i]);
	}
}
