
%{
	#include "tokens.h"
%}



%%

[1-9]+				{return KW_INT;}
.+					{return -1;}

%%

int yywrap()
{
	return 1;
}



