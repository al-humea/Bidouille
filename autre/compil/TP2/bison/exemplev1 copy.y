%{
    #include <stdio.h>
    extern int yylex();
    void yyerror (const char *msg);/**/
%}

%union {int nombre; char *variable}//liste d'attributs possible
%token <nombre> NUM//token init avec attribut
%token <variable> NAME

%right ’=’
%left ’+’ ’-’
%left ’*’ ’/’
%left UMOINS //détermine la priorité des opération et l'associativité à gauche ou droite(osef)

E -> E + E
    | E * E
    | - E %prec UMOINS // prend la priorité de l'opérateur UMOINS donc le plus important
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