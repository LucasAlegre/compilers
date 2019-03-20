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
			case KW_INT:
				printf("KW_INT\n");
				break;
			default:
				printf("DEFAULT\n");
				break;
		}
	}

	return 0;
}