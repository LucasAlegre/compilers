%{
/* 
	ETAPA 1 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
	Alunos:
		Guilherme Haetinger e Lucas Alegre 
*/
	#include <stdio.h>
	#include "y.tab.h"
	#include "hash.h"
	
	int yyparse(); 
    
	int LineNumber = 1;
    int Running = 1;  
   	
%}

%x COMMENT

%%

byte						{return KW_BYTE;      }
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
[0-9a-z_]+                  {hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER;}
[A-IO]+						{hashInsert(LIT_INTEGER, yytext); return LIT_INTEGER;  }
[A-IO]+\.[A-IO]+            {hashInsert(LIT_FLOAT, yytext); return LIT_FLOAT;    }
\n                          {LineNumber++;        }
[ \t]
ZZ.*
XXX                         {BEGIN(COMMENT);}
'.'                         {hashInsert(LIT_CHAR, yytext); return LIT_CHAR;     }
\"(\\.|[^"])*\"             {hashInsert(LIT_STRING, yytext); return LIT_STRING;   }
.                           {return TOKEN_ERROR;  }

<COMMENT>XXX                {BEGIN(INITIAL);}
<COMMENT>.
<COMMENT>\n                 {++LineNumber;}

%%

void initMe(void){
	hashInit();
}

int getLineNumber(void){
	return LineNumber;
}

int isRunning(void){
	return Running;
}

int yywrap(){
    Running = 0;
    return 1;
}



