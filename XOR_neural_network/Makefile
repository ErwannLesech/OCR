CC = gcc
CFLAGS = -Wall -Wextra
DEP = -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: main

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(DEP)

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(DEP)

clean: 
	rm -rf $(OBJ)
	rm -rf main
	rm -rf test.txt
