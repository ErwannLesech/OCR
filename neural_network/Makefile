CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -O1
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

test: $(OBJ)
 	$(CC) -o $@ $^

clean:
	rm -rf $(OBJ)
	rm -rf test
