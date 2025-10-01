D'abord `bison -d exemple.y` génère exemple tab h puis
puis `gcc -c exemple.tab.c` ensuite `flex exemple.lex`
puis `gcc -c lex.yy.c` et `gcc -c main.c`
Enfin : `gcc exemple.tab.o lex.yy.o main.o -o main -lfl`

revoir cours LR LRAD

finir calculatrice

commencer TP3
