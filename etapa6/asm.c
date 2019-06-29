#include <stdio.h>
#include <string.h>
#include "asm.h"
#include "semantic.h"
#include "astree.h"
#include "hash.h"


void johannNumberConversion(char* johann, char* out){
    for(int i = 0; i < strlen(johann); i++){
        switch (johann[i]){
            case 'O': out[i] = '0'; break;
            case 'I': out[i] = '1'; break;
            case 'H': out[i] = '2'; break;
            case 'G': out[i] = '3'; break;
            case 'F': out[i] = '4'; break;
            case 'E': out[i] = '5'; break;
            case 'D': out[i] = '6'; break;
            case 'C': out[i] = '7'; break;
            case 'B': out[i] = '8'; break;
            case 'A': out[i] = '9'; break;
            case '.': out[i] = '.'; break;
        }
    }
}

void addTemporaries(FILE* out){
    hash_node** Table = getTable();

    for(int i = 0; i < HASH_SIZE; i++) {	
		for(hash_node *aux = Table[i]; aux; aux = aux->next){
			if(strncmp(aux->text, "_temp", 5) == 0) { 
				fprintf(out, "\t.globl	_%s\n"
                             "\t.data\n"
                             "\t.type	_%s, @object\n"
                             "\t.size	_%s, 4\n"
                             "_%s:\n", aux->text, aux->text, aux->text, aux->text);
                if(aux->datatype == DATATYPE_FLOAT){
                    fprintf(out, "\t.float  0.0\n");
                }
                else{
                    fprintf(out, "\t.long  0\n");
                }
			}
		}
	}	
}

void addImmediates(FILE* out){
    hash_node** Table = getTable();

	for(int i = 0; i < HASH_SIZE; i++) {	
		for(hash_node *aux = Table[i]; aux; aux = aux->next){
			if((aux->type == SYMBOL_LIT_INT || aux->type == SYMBOL_LIT_FLOAT) || aux->type == SYMBOL_LIT_CHAR) { 
                fprintf(out, "\t.globl	_%s\n"
                             "\t.data\n"
                             "\t.type	_%s, @object\n"
                             "\t.size	_%s, 4\n"
                             "_%s:\n", aux->text, aux->text, aux->text, aux->text);

                if(aux->type == SYMBOL_LIT_FLOAT) {
                    char *conversion = malloc(sizeof(strlen(aux->text)+1));
                    johannNumberConversion(aux->text, conversion);
                    fprintf(out, "\t.float  %s\n", conversion);
                    free(conversion);
                }
                else if(aux->type == SYMBOL_LIT_INT){
                    char *conversion = malloc(sizeof(strlen(aux->text)+1));
                    johannNumberConversion(aux->text, conversion);
                    fprintf(out, "\t.long   %s\n", conversion);
                    free(conversion);
                }
                else if(aux->type == SYMBOL_LIT_CHAR){
                    fprintf(out, "\t.long   %d\n", aux->text[1]);  // 'x' will print ascii of x only
                }
			}
		}
	}	
}

void addData(FILE *out, astree_node* node){
    static int LC = 2;

    if(!node) return;
	if(node->type == AST_DECVAR) {   
    	fprintf(out, "\t.globl	_%s\n"
                     "\t.data\n"
                     "\t.type	_%s, @object\n"
                     "\t.size	_%s, 4\n"
                     "_%s:\n", node->symbol->text, node->symbol->text, node->symbol->text, node->symbol->text);
		
        char *conversion = malloc(sizeof(strlen(node->sons[1]->symbol->text)+1));
        johannNumberConversion(node->sons[1]->symbol->text, conversion);
		if(node->sons[0]->type == AST_TPFLOAT) {
			fprintf(out, "\t.float	%s\n", conversion);
		}
		else {
			fprintf(out, "\t.long	%s\n", conversion);
		}
        free(conversion);
	}
    else if (node->type == AST_PARAM){  // Params are global variables!
    	fprintf(out, "\t.globl	_%s\n"
                     "\t.data\n"
                     "\t.type	_%s, @object\n"
                     "\t.size	_%s, 4\n"
                     "_%s:\n", node->symbol->text, node->symbol->text, node->symbol->text, node->symbol->text);
        if(node->sons[0]->type == AST_TPFLOAT) {
			fprintf(out, "\t.float	0\n");
		}
		else {
			fprintf(out, "\t.long	0\n");
		}
    }
	else if(node->type == AST_DECVEC){
        char *conversion = malloc(sizeof(strlen(node->sons[1]->symbol->text)+1));
        johannNumberConversion(node->sons[1]->symbol->text, conversion);
        fprintf(out, "\t.globl	_%s\n"
                     "\t.data\n"
                     "\t.type	_%s, @object\n"
                     "\t.size	_%s, %d\n"
                     "_%s:\n", node->symbol->text, node->symbol->text, node->symbol->text, 4*atoi(conversion), node->symbol->text);
        free(conversion);
        for(astree_node* aux = node->sons[2]; aux; aux = aux->sons[1]) {
            char *conversion = malloc(sizeof(strlen(aux->sons[0]->symbol->text)+1));
            johannNumberConversion(aux->sons[0]->symbol->text, conversion);
            if(node->sons[0]->type == AST_TPFLOAT){
                fprintf(out, "\t.float	%s\n", conversion);
            }
            else{
                fprintf(out, "\t.long	%s\n", conversion);
            }
            free(conversion);
        }
	}
    else if(node->type == AST_SYMBOL){
        if(node->symbol->type == SYMBOL_LIT_STRING){
            fprintf(out, "\t.section\t .rodata\n.LC%d:\n\t.string %s \n", LC, node->symbol->text);
            LC++;          
        }
    }
    
	for(int i = 0; i < MAX_SONS; i++){
		addData(out, node->sons[i]);
	}
}

void asmGenerate(tac *firstTac, astree_node* ast){
    FILE* out = fopen("asm.s", "w");
    int LC = 2;

    addTemporaries(out);
    addImmediates(out);
    fprintf(out, "\t.section	.rodata\n"
		         ".LC0:\n"
		         "\t.string	\"%%d\"\n");
    fprintf(out, "\t.section	.rodata\n"
                 ".LC1:\n"
                 "\t.string	\"%%f\"\n");
    addData(out, ast);

    for(tac* tac = firstTac; tac; tac = tac->next){
        switch (tac->type) {
            case TAC_PRINT:
                if(tac->res->text[0] == '\"'){
                    fprintf(out, 	"\tleaq	.LC%d(%%rip), %%rdi\n"
                                    "\tmovl	$0, %%eax\n"
                                    "\tcall	printf@PLT\n", LC++);
                }
                else if(tac->res->datatype == DATATYPE_FLOAT) {
                    fprintf(out,	"movss	_%s(%%rip), %%xmm0\n"
                                    "cvtss2sd	%%xmm0, %%xmm0\n"
                                    "leaq	.LC1(%%rip), %%rdi\n"
                                    "movl	$1, %%eax\n"
                                    "call	printf@PLT\n", tac->res->text);
                }
                else{
                    fprintf(out, 	"\tmovl	_%s(%%rip), %%eax\n"
                                    "\tmovl	%%eax, %%esi\n"
                                    "\tleaq	.LC0(%%rip), %%rdi\n"
                                    "\tmovl	$0, %%eax\n"
                                    "\tcall	printf@PLT\n", tac->res->text);
                }
                break;
            
		    case TAC_BEGINFUN: 
                fprintf(out, "\t.text\n"
						     "\t.globl %s\n"
						     "\t.type	%s, @function\n" 
						     "%s:\n"
						     "\tpushq	%%rbp\n"
						     "\tmovq	%%rsp, %%rbp\n",  tac->res->text, tac->res->text, tac->res->text); 
                break;
	
		    case TAC_ENDFUN: 
                fprintf(out, "\tpopq	%%rbp\n"
					         "\tret\n");
                break;

            case TAC_CALL: 
                fprintf(out, "\tcall	%s\n"
				             "\tmovl	%%eax, _%s(%%rip)\n" , tac->op1->text, tac->res->text);
                break;

		    case TAC_RET: 
                fprintf(out, "\tmovl	_%s(%%rip), %%eax\n" , tac->op1->text); 
                break;

            default:
                break;
        }
    }

    fclose(out);
}