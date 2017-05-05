/*Imports*/
%{
	#include "anasin.tab.h"

%}

%option noinput
%option nounput

/*Tokens*/
%%
"!" return LAMBDA;

"." return PONTO;

"(" return PARE;

")" return PARD;

[a-z] {
	yylval.letter = strdup(yytext); /*coloca o valor na stack*/

	return LETTER;	
}
[ \n\t] ;

%%

int yywrap() {
  return 1;
}