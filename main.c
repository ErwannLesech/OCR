#include <SDL2/SDL_image.h>

int main(){
    SDL_Surface *sdl_surface = IMG_Load("image_01.jpeg");
    sdl_surface->pixels;
}