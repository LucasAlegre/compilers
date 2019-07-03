#include <stdio.h>
#include <string.h>
#include "asm.h"
#include "semantic.h"
#include "astree.h"
#include "hash.h"
#include "function_hash.h"


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
                    char *conversion = calloc(strlen(aux->text)+1, sizeof(char));
                    johannNumberConversion(aux->text, conversion);
                    fprintf(out, "\t.float  %s\n", conversion);
                    free(conversion);
                }
                else if(aux->type == SYMBOL_LIT_INT){
                    char *conversion = calloc(strlen(aux->text)+1, sizeof(char));
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
		
        char *conversion = calloc(strlen(node->sons[1]->symbol->text)+1, sizeof(char));
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
        char *conversion = calloc(strlen(node->sons[1]->symbol->text)+1, sizeof(char));
        johannNumberConversion(node->sons[1]->symbol->text, conversion);
        fprintf(out, "\t.globl	_%s\n"
                     "\t.data\n"
                     "\t.type	_%s, @object\n"
                     "\t.size	_%s, %d\n"
                     "_%s:\n", node->symbol->text, node->symbol->text, node->symbol->text, 4*atoi(conversion), node->symbol->text);
        free(conversion);
        for(astree_node* aux = node->sons[2]; aux; aux = aux->sons[1]) {
            char *conversion = calloc(strlen(aux->sons[0]->symbol->text)+1, sizeof(char));
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

    function_hashInit();
    char * function_name = NULL;
    int arg_index = 0;
    function_hash_node * node = NULL;
    function_argument * argument = NULL;
    char * argumentBuffer[100];


    FILE* out = fopen("asm.s", "w");
    int LC = 2;
    int BL = 0;

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
            case TAC_MOVE:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                           "\tmovl %%eax, _%s(%%rip)\n", tac->op1->text, tac->res->text);
              break;

            case TAC_ADD:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                           "\tmovl _%s(%%rip), %%edx\n"
                           "\taddl %%eax, %%edx\n"
                           "\tmovl %%edx, _%s(%%rip)\n", tac->op1->text, tac->op2->text, tac->res->text);
              break;

            case TAC_SUB:
               fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                            "\tmovl _%s(%%rip), %%edx\n"
                            "\tsubl %%eax, %%edx\n"
                            "\tmovl %%edx, _%s(%%rip)\n", tac->op2->text, tac->op1->text, tac->res->text);
               break;

            case TAC_MUL:
               fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                            "\tmovl _%s(%%rip), %%edx\n"
                            "\timull %%eax, %%edx\n"
                            "\tmovl %%edx, _%s(%%rip)\n", tac->op1->text, tac->op2->text, tac->res->text);
               break;

            case TAC_DIV:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                           "\tmovl _%s(%%rip), %%ecx\n"
                           "\tcltd\n"
                           "\tidivl %%ecx\n"
                           "\tmovl %%eax, _%s(%%rip)\n", tac->op1->text, tac->op2->text, tac->res->text);
              break;

            case TAC_GREAT:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                      "\tmovl _%s(%%rip), %%edx\n"
                      "\tcmpl %%eax, %%edx\n"
                      "\tjg .BL%d\n"
                      "\tmovl $0, %%eax\n"
                      "\tjmp .BL%d\n"
                      ".BL%d:\n"
                      "\tmovl $1, %%eax\n"
                      ".BL%d:\n"
                      "\tmovl %%eax, _%s(%%rip)\n", tac->op2->text, tac->op1->text, BL, BL+1, BL, BL+1, tac->res->text);
              BL+=2;
              break;

            case TAC_LESS:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                      "\tmovl _%s(%%rip), %%edx\n"
                      "\tcmpl %%eax, %%edx\n"
                      "\tjl .BL%d\n"
                      "\tmovl $0, %%eax\n"
                      "\tjmp .BL%d\n"
                      ".BL%d:\n"
                      "\tmovl $1, %%eax\n"
                      ".BL%d:\n"
                      "\tmovl %%eax, _%s(%%rip)\n", tac->op2->text, tac->op1->text, BL, BL+1, BL, BL+1, tac->res->text);
              BL+=2;
              break;

            case TAC_GE:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                           "\tmovl _%s(%%rip), %%edx\n"
                           "\tcmpl %%eax, %%edx\n"
                           "\tjge .BL%d\n"
                           "\tmovl $0, %%eax\n"
                           "\tjmp .BL%d\n"
                           ".BL%d:\n"
                           "\tmovl $1, %%eax\n"
                           ".BL%d:\n"
                           "\tmovl %%eax, _%s(%%rip)\n", tac->op2->text, tac->op1->text, BL, BL+1, BL, BL+1, tac->res->text);
              BL+=2;
              break;

            case TAC_LE:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                           "\tmovl _%s(%%rip), %%edx\n"
                           "\tcmpl %%eax, %%edx\n"
                           "\tjle .BL%d\n"
                           "\tmovl $0, %%eax\n"
                           "\tjmp .BL%d\n"
                           ".BL%d:\n"
                           "\tmovl $1, %%eax\n"
                           ".BL%d:\n"
                           "\tmovl %%eax, _%s(%%rip)\n", tac->op2->text, tac->op1->text, BL, BL+1, BL, BL+1, tac->res->text);
                BL+=2;
                break;

            case TAC_EQ:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                      "\tmovl _%s(%%rip), %%edx\n"
                      "\tcmpl %%eax, %%edx\n"
                      "\tje .BL%d\n"
                      "\tmovl $0, %%eax\n"
                      "\tjmp .BL%d\n"
                      ".BL%d:\n"
                      "\tmovl $1, %%eax\n"
                      ".BL%d:\n"
                      "\tmovl %%eax, _%s(%%rip)\n", tac->op2->text, tac->op1->text, BL, BL+1, BL, BL+1, tac->res->text);
              BL+=2;
              break;

            case TAC_DIF:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                      "\tmovl _%s(%%rip), %%edx\n"
                      "\tcmpl %%eax, %%edx\n"
                      "\tjne .BL%d\n"
                      "\tmovl $0, %%eax\n"
                      "\tjmp .BL%d\n"
                      ".BL%d:\n"
                      "\tmovl $1, %%eax\n"
                      ".BL%d:\n"
                      "\tmovl %%eax, _%s(%%rip)\n", tac->op2->text, tac->op1->text, BL, BL+1, BL, BL+1, tac->res->text);
              BL+=2;
              break;

            case TAC_AND:
                fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                             "\tmovl _%s(%%rip), %%edx\n"
                             "\tandl %%eax, %%edx\n"
                             "\tjz .BL%d\n"
                             "\tmovl $1, %%eax\n"
                             "\tjmp .BL%d\n"
                             ".BL%d:\n"
                             "\tmovl $0, %%eax\n"
                             ".BL%d:\n"
                             "\tmovl %%eax, _%s(%%rip)\n", tac->op1->text, tac->op2->text, BL, BL+1, BL, BL+1, tac->res->text);
                BL+=2;
                break;

            case TAC_OR:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                      "\tmovl _%s(%%rip), %%edx\n"
                      "\torl %%eax, %%edx\n"
                      "\tjz .BL%d\n"
                      "\tmovl $1, %%eax\n"
                      "\tjmp .BL%d\n"
                      ".BL%d:\n"
                      "\tmovl $0, %%eax\n"
                      ".BL%d:\n"
                      "\tmovl %%eax, _%s(%%rip)\n", tac->op1->text, tac->op2->text, BL, BL+1, BL, BL+1, tac->res->text);
              BL+=2;
              break;

            case TAC_NOT:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                      "\tmovl $1, %%edx\n"
                      "\tandl %%eax, %%edx\n"
                      "\tjz .BL%d\n"
                      "\tmovl $0, %%eax\n"
                      "\tjmp .BL%d\n"
                      ".BL%d:\n"
                      "\tmovl $1, %%eax\n"
                      ".BL%d:\n"
                      "\tmovl %%eax, _%s(%%rip)\n", tac->op1->text, BL, BL+1, BL, BL+1, tac->res->text);
              BL+=2;
              break;


            case TAC_LABEL:
              fprintf(out, ".%s:\n", tac->res->text);
              break;

            case TAC_JUMP:
              fprintf(out, "\tjmp .%s\n", tac->res->text);
              break;

            case TAC_IFZ:
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                     "\tmovl $1, %%edx\n"
                     "\tandl %%eax, %%edx\n"
                     "\tjz .%s\n", tac->op1->text, tac->res->text);
             break;

            case TAC_PRINT:
                if(tac->res->text[0] == '\"'){
                    fprintf(out, 	"\tleaq	.LC%d(%%rip), %%rdi\n"
                                    "\tmovl	$0, %%eax\n"
                                    "\tcall	printf@PLT\n", LC++);
                }
                else if(tac->res->datatype == DATATYPE_FLOAT) {
                    fprintf(out,  "\tmovss	_%s(%%rip), %%xmm0\n"
                                  "\tcvtss2sd	%%xmm0, %%xmm0\n"
                                  "\tleaq	.LC1(%%rip), %%rdi\n"
                                  "\tmovl	$1, %%eax\n"
                                  "\tcall	printf@PLT\n", tac->res->text);
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
                function_hashInsert(tac->res->text);
                if(function_name != NULL) free(function_name);
                function_name = (char*) calloc(1, sizeof(tac->res->text));
                strcpy(function_name, tac->res->text);
                fprintf(out, "\t.text\n"
						     "\t.globl %s\n"
						     "\t.type	%s, @function\n"
						     "%s:\n"
						     "\tpushq	%%rbp\n"
						     "\tmovq	%%rsp, %%rbp\n",  tac->res->text, tac->res->text, tac->res->text);
                break;

        case TAC_PARAMPOP:
          node = getNode(function_name);
          addNewArgument(tac->res->text, node);
          break;

        case TAC_ARGPUSH:

          argumentBuffer[arg_index] = (char*) calloc(1, sizeof(tac->res->text));
          strcpy(argumentBuffer[arg_index], tac->res->text);
          arg_index++;
          break;

        case TAC_VEC:
          fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                  "\tcltq\n"
                  "\tmovl _%s(,%%rax, 4), %%eax\n"
                  "\tmovl %%eax, _%s(%%rip)\n", tac->op2->text, tac->op1->text, tac->res->text);
          break;

        case TAC_VECATTR:
          fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                  "\tmovl _%s(%%rip), %%edx\n"
                  "\tcltq\n"
                  "\tmovl %%edx, _%s(,%%rax, 4)\n", tac->op1->text, tac->op2->text, tac->res->text);
          break;

		    case TAC_ENDFUN:
                fprintf(out, "\tpopq	%%rbp\n"
					         "\tret\n");
                break;

            case TAC_CALL:
              if(function_name != NULL) free(function_name);
              function_name = (char*) calloc(1, sizeof(tac->op1->text));
              strcpy(function_name, tac->op1->text);
              function_argument * arg = getNode(function_name)->first_argument;
              for(int i = arg_index - 1; i >= 0 && arg != NULL; i--, arg = arg->next){
              fprintf(out, "\tmovl _%s(%%rip), %%eax\n"
                        "\tmovl %%eax, _%s(%%rip)\n", argumentBuffer[i], arg->name);
              }
              fprintf(out, "\tcall	%s\n"
				             "\tmovl	%%eax, _%s(%%rip)\n" , tac->op1->text, tac->res->text);
              arg_index = 0;
              break;
        case TAC_READ: fprintf(out, "\tmovl	$_%s, %%esi\n"
                                "\tmovl	$.LC0, %%edi\n"
                                "\tcall	__isoc99_scanf\n", tac->res->text);
            break;

        case TAC_RET:
                fprintf(out, "\tmovl	_%s(%%rip), %%eax\n" , tac->res->text);
                break;

            default:
                break;
        }
    }

    fclose(out);
}
