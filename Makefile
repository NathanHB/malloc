
# Setting the compiler for the program
CC = gcc
# Options for preprocessor
CPPFLAGS = -MMD
# Option for compilation
CFLAGS = -Wall -Wextra -std=c99 -g
# Linker options
LDFLAGS  =
# Info for linker
LDLIBS =

SRC = malloc.c tests.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: tests

libmalloc.so: malloc.o
	${CC} -shared -o libmalloc.so malloc.o

malloc: ${OBJ}

main: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} tests
	${RM} libmalloc.so

-include ${DEP}
