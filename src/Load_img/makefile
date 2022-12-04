CC = gcc
CPPFLAGS=  `pkg-config --cflags --libs sdl2 SDL2_image`
CFLAGS= -Wall -Wextra -O3 `pkg-config --cflags --libs sdl2 SDL2_image` 
LDFLAGS= $(sdl2-config --cflags --libs) 
LDLIBS=  -lSDL2_image -lm

SRC= main_image.c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

separate: ${OBJ}
all: main
clean:
	rm -rf main
