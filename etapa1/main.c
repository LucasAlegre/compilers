#include <stdio.h>
#include "lex.yy.h"
#include "tokens.h"

int main()
{
	int tok;

	while(1)
	{
		tok = yylex();

		switch(tok)
		{
			case KW_BYTE:
				printf("KW_BYTE\n");
				break;
			case KW_INT:
				printf("KW_INT\n");
				break;
   			case KW_FLOAT:
   				printf("KW_FLOAT\n");
   				break;
   			case KW_IF:
   				printf("KW_IF\n");
   				break;
   			case KW_THEN:
   				printf("KW_THEN\n");
   				break;
   			case KW_ELSE:
   				printf("KW_ELSE\n");
   				break;
   			case KW_LOOP:
   				printf("KW_LOOP\n");
   				break;
   			case KW_LEAP:
   				printf("KW_LEAP\n");
   				break;
   			case KW_READ:
   				printf("KW_READ\n");
   				break;
   			case KW_RETURN:
   				printf("KW_RETURN\n");
   				break;
   			case KW_PRINT:
   				printf("KW_PRINT\n");
   				break;
   			case OPERATOR_LE:
   				printf("OPERATOR_LE\n");
   				break;
   			case OPERATOR_GE:
   				printf("OPERATOR_GE\n");
   				break;
   			case OPERATOR_EQ:
   				printf("OPERATOR_EQ\n");
   				break;
   			case OPERATOR_DIF:
   				printf("OPERATOR_DIF\n");
   				break;
   			case OPERATOR_OR:
   				printf("OPERATOR_OR\n");
   				break;
   			case OPERATOR_AND:
   				printf("OPERATOR_AND\n");
   				break;
   			case OPERATOR_NOT:
   				printf("OPERATOR_NOT\n");
   				break;
   			case TK_IDENTIFIER:
   				printf("TK_IDENTIFIER\n");
   				break;
   			case LIT_INTEGER:
   				printf("LIT_INTEGER\n");
   				break;
   			case LIT_FLOAT:
   				printf("LIT_FLOAT\n");
   				break;
   			case LIT_CHAR:
   				printf("LIT_CHAR\n");
   				break;
   			case LIT_STRING:
   				printf("LIT_STRING\n");
   				break;
   			case TOKEN_ERROR:
   				printf("TOKEN_ERROR\n");
   				break;
			default:
				printf("DEFAULT\n");
				break;
		}
	}

	return 0;
}
