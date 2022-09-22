CC = gcc
CFLAGS = -Wall -Wextra
DEP = -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: main

%.o: %.c
	$(CC) $(CFLAGS) $(DEP) -o $@ -c $<

main: $(OBJ)
	$(CC) $(CFLAGS) $(DEP) -o $@ $^

clean: 
	rm -rf $(OBJ)
	rm -rf main
