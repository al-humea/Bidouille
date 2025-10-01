%{
    #include <stdio.h>
    extern int yylex();
    void yyerror (const char *msg);/**/
%}

%token NUM
%start phrase

%%
//attributs, tous les symboles par défaut entiers ici
//le code permet de compter la profondeur de parenthésage
phrase: %empty {
                    $$ = 0;//initialise à 0 l'attribut de phrase
                    printf("empty = %d\n", $$);
                }
    | phrase '(' phrase ')' {
                                if ($1 > $3)
                                    $$ = $1;
                                else
                                    $$ = $3+1;
                                printf(".(.) = %d\n", $$);
                            }
    | NUM   { $$ = $1; }
;/*';' important à chaque fin de bloc*/
%%

void yyerror(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
}