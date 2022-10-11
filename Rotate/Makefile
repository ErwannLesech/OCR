CC = gcc
CPPFLAGS= `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2` -lSDL_gfx -D__NO_INLINE__
CFLAGS=  -g -fsanitize=address -Wall -Wextra  -std=c99 -O0
LDFLAGS= -fsanitize=address 
LDLIBS= -lasan `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl2` -lSDL2_image -lm -lpthread

SRC=$(wildcard*.c)
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

all: main
clean:
	rm -rf $(OBJ)
	rm -rf main
