CC=gcc

CPPFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2`

CFLAGS = -Wall -Wextra -std=c99 -O3 -lm

LDLIBS= -lasan `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl2` -lSDL2_image -lm -lpthread

LDFLAGS= -fsanitize=address 


SRC= main.c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

all: main


clean: 
	rm -rf $(OBJ)
	rm -rf main
	rm -rf saved.png

