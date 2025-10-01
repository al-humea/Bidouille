%{
    #include <stdio.h>
    extern int yylex();
    void yyerror (const char *msg);
%}

%token NUM
%start E

%%

E: %empty {$$ = 0;}
    | E '+' E {$$ = $1 + $3;}
    | NUM {$$ = $1;}
;/*';' important à chaque fin de bloc*/
%%

void yyerror(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
}