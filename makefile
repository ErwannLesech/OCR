main: main.c
gcc -o main main.c `$(sdl2-config --cflags --libs)` -lSDL2_image 

