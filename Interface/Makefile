CC = gcc
CFLAGS = -Wall -Wextra
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LDFLAGS = $(shell pkg-config --libs gtk+-3.0)
DEP = -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: main

%.o: %.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(DEP) $(GTK_LDFLAGS) -o $@ -c $<

main: $(OBJ)
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(DEP) $(GTK_LDFLAGS) -o $@ $^

clean: 
	rm -rf $(OBJ)
	rm -rf main
