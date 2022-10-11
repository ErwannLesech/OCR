CC = gcc
FLAGS = -Wall -Wextra
LDFLAGS=-lSDL -lSDL_gfx
DEP = -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: main

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEP) -o $@ -c $<

main: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEP) -o $@ $^

clean:
	rm -rf $(OBJ)
	rm -rf main
