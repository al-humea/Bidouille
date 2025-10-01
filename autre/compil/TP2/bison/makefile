main: exemple.tab.o lex.yy.o main.o

exemple.tab.c: exemple.y
	bison -d $<

lex.yy.c: exemple.lex exemple.tab.c
	flex -s $<

clean:
	rm -f \
		exemple.tab.o exemple.tab.c exemple.tab.h exemple.output \
		lex.yy.o lex.yy.c \
		main.o main

re : clean main