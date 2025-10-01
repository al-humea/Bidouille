%{
    #include <stdio.h>
    extern int yylex();
    void yyerror (const char *msg);/**/
%}

%token OPAR CPAR
%token DOT

%start phrase

%%

phrase: %empty
    | phrase OPAR phrase CPAR
    | phrase OPAR phrase DOT phrase CPAR
;/*';' important à chaque fin de bloc*/

%%

void yyerror(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
}