#include "helper.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_surface.h"

SDL_Surface** separate(SDL_Surface* grid);
void save_image(SDL_Surface** surfaces);
