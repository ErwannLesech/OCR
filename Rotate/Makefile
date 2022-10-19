CC = gcc
CPPFLAGS=  `pkg-config --cflags --libs sdl` -lSDL_gfx -lSDL_image
CFLAGS=  -Wall -Wextra -O3 `pkg-config --cflags --libs sdl`
LDFLAGS= 
LDLIBS=  `pkg-config --libs sdl`

SRC= main.c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

all: main
clean:
	rm -rf main
	rm -rf test.bmp

