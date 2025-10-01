%{
#include "exemple.tab.h"
%}

%option nounput
%option noyywrap

%%
[()] return yytext[0];
[0-9]+ {yylval = atoi(yytext); return NUM ;}

[[:space:]] ;

. fprintf(stderr, "caractère illégal (%d) ignoré\n", yytext[0]);
%%