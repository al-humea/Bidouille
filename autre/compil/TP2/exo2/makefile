NAME=exo2

main: $(NAME).tab.o lex.yy.o main.o

$(NAME).tab.c: $(NAME).y
	bison -d $<

lex.yy.c: $(NAME).lex $(NAME).tab.c
	flex -s $<

clean:
	rm -f \
		$(NAME).tab.o $(NAME).tab.c $(NAME).tab.h $(NAME).output \
		lex.yy.o lex.yy.c \
		main.o main

re : clean main