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

void addData(FILE *out){

}

void asmGenerate(tac *firstTac, astree_node* ast){
    FILE* out = fopen("asm.s", "w");

    addTemporaries(out);
    addImmediates(out);
    


    for(tac* tac = firstTac; tac; tac = tac->next){
        switch (tac->type) {
            case TAC_SYMBOL:
                break;
            
            default:
                break;
        }
    }

    fclose(out);
}