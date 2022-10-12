CC = gcc
CPPFLAGS=  `pkg-config --cflags sdl2 SDL2_image` -lSDL_gfx 
CFLAGS=  -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS= 
LDLIBS=  `pkg-config --libs sdl2 SDL2_image`

SRC= main.c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

all: main
clean:
	rm -rf $(OBJ)
	rm -rf main
