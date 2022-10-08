# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra `pkg-config --cflags gtk+-3.0` 
LIBS = `pkg-config --libs gtk+-3.0`

all: main

SRC = main.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

main: main.o

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END
