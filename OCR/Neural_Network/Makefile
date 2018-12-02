# Makefile

CC=gcc -fsanitize=address
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS=

SRC= parser.c xor.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

all: main

-include ${DEP}

main: ${OBJ}

all: ${PRG}

clean:
	rm -f ${OBJ} ${DEP} main

# END
