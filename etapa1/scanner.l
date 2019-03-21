
%{
	#include "tokens.h"

	int Running = 1;
	int LineNumber = 1;
%}

%x COMMENT

%%

byte			            {return KW_BYTE;      }
int                         {return KW_INT;       }
float                       {return KW_FLOAT;     }
if                          {return KW_IF;        }
then                        {return KW_THEN;      }
else                        {return KW_ELSE;      }
loop                        {return KW_LOOP;      }
leap                        {return KW_LEAP;      }
read                        {return KW_READ;      }
print                       {return KW_PRINT;     }
return                      {return KW_RETURN;    }
[-,;:()\[\]{}+*/<>=&$#]     {return yytext[0];    }
or                          {return OPERATOR_OR;  }
and                         {return OPERATOR_AND; }
not                         {return OPERATOR_NOT; }
">="                        {return OPERATOR_GE;  }
"<="                        {return OPERATOR_LE;  }
"=="                        {return OPERATOR_EQ;  }
"!="                        {return OPERATOR_DIF; }
[0-9a-z_]+                  {return TK_IDENTIFIER;}
[A-IO]+				        {return LIT_INTEGER;  }
[A-IO]+\.[A-IO]+            {return LIT_FLOAT;    }
\n                          {LineNumber++;        }
[ \t]
ZZ.*
XXX                         {BEGIN(COMMENT);}
'.'                         {return LIT_CHAR;     }
\"(\\.|[^"])*\"             {return LIT_STRING;   }
.                           {return TOKEN_ERROR;  }

<COMMENT>XXX                {BEGIN(INITIAL);}
<COMMENT>.
<COMMENT>\n                 {++LineNumber;}

%%

int yywrap(){
    Running = 0;
    return 1;
}



