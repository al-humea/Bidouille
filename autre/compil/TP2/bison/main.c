#include <stdio.h>
extern int yyparse();

int main()
{
    int r = yyparse();//appelle yylex
    printf("->%d\n", r);
    return r;
}