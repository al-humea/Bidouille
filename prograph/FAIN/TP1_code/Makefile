
# Vendredi 10 Septembre 1999
# Arash Habibi
# Le Makefile de Interface


CC=gcc

CFLAGS=-Wall
LFLAGS=-lGL -lGLU -lglut

SOURCES=$(wildcard *.c)
EXECUTABLES=$(SOURCES:%.c=%)

# Compiler le programme
all : $(EXECUTABLES)

% :  %.c
	${CC} ${CFLAGS} -o $@ $^ $(LFLAGS)

clean :
	rm *.o $(EXECUTABLES)

