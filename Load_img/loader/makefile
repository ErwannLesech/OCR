CC = gcc
CPPFLAGS = -MMD
CFLAGS = #-Wall -Wextra
LDFLAGS = $(sdl2-config --cflags --libs)
LDLIBS = -lSDL2_image 

SRC = load_img.c utils.c canny_filter.c main.c turn_img.c display_img.c 
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

main: ${OBJ}

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

# END

#test: load_img.c load_img.h main.c array_utils.c array_utils.h display_img.c display_img.h 
#	gcc -o test auto_rot.c main.c focus_grid.c find_square.c load_img.c utils.c canny_filter.c display_img.c hough_translate.c utils_hough_translate.c $(sdl2-config --cflags --libs) -lSDL2_image -lm