CC = gcc
CPPFLAGS = -MMD
CFLAGS = #-Wall -Wextra
LDFLAGS = $(sdl2-config --cflags --libs)
LDLIBS = -lSDL2_image 

SRC = load_img.c array_utils.c canny_filter.c main.c turn_img.c display_img.c 
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

mainu: ${OBJ}

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

# END

#test: load_img.c load_img.h main.c array_utils.c array_utils.h display_img.c display_img.h 
#	gcc -o test main.c load_img.c array_utils.c  