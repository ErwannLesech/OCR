#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL2/SDL_image.h>

const int WIN_WIDTH = 640;
const int WIN_HEIGHT = 480;
void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
     SDL_RenderCopyEx(renderer, NULL, NULL, texture,180,  NULL, SDL_FLIP_NONE);
     SDL_RenderPresent(renderer);
}

void event_loop(SDL_Renderer* renderer, SDL_Texture* normal, SDL_Texture* turn)
{
	SDL_Event event;
	SDL_Texture* t = normal;

	while(1)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				return;
		
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					draw(renderer, normal);
				}
				break;
			case SDL_KEYDOWN:
				if(t == normal)
				{
					draw(renderer, turn);
					t = turn;
				}
				else
				{
					draw(renderer, normal);
					t = normal;
				}
				break;
		}
	}	
}


int main(int argc, char** argv)
{
	if (argc != 3)
        	errx(EXIT_FAILURE, "Erreur");
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	/*
	SDL_Window *win = SDL_CreateWindow("Rendering to a texture!", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	//Put your own bmp image here
	SDL_Surface *bmpSurf = SDL_LoadBMP(argv[1]);
	SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(renderer, bmpSurf);
	SDL_FreeSurface(bmpSurf);

	//Make a target texture to render too
	SDL_Surface* surfaceturn =rotozoomSurface(bmpSurf,(-180), 1,1);
	SDL_Texture *texTarget = SDL_CreateTextureFromSurface(renderer, surfaceturn);

	
	//Now render to the texture
	SDL_SetRenderTarget(renderer, texTarget);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bmpTex, NULL, NULL);
	//Detach the texture
	SDL_SetRenderTarget(renderer, NULL);

	//Now render the texture target to our screen, but upside down
	SDL_RenderClear(renderer);
	SDL_RenderCopyEx(renderer, bmpTex, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);

	SDL_Delay(5000);
	SDL_DestroyTexture(texTarget);
	SDL_DestroyTexture(bmpTex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;*/
	
	SDL_Window* window = SDL_CreateWindow("Window", 0, 0,
			800, 800,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	SDL_Surface* surface= SDL_LoadBMP(argv[1]);
	SDL_Texture* normal = IMG_LoadTexture(renderer,argv[1]);

	
	//int angler = (int)(argv[2]) * M_PI / 180.0;
	
	SDL_Surface* surfaceturn =rotozoomSurface(surface,(-180), 1,1);
	int turn = SDL_SaveBMP(surfaceturn, "test.bmp");
	SDL_Renderer* renderer2 = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* normal2= IMG_LoadTexture(renderer2, "test.bmp");

	
	
	//SDL_Texture *turn = SDL_CreateTextureFromSurface(renderer, surfaceturn);
	
	SDL_FreeSurface(surface);
	event_loop(renderer,normal,normal2);

	SDL_DestroyTexture(normal);
	printf("a");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS; 
	
}
/*
void corrected_rotation_matrix(double angle, double x, double y,
    double center_x, double center_y, double *rx, double *ry)
{
    *rx = (x - center_x) * cos(angle) - (y - center_y) * sin(angle) + center_x;
    *ry = (x - center_x) * sin(angle) + (y - center_y) * cos(angle) + center_y;
}


 * @brief Rotates image counterclockwise by an angle
 *
 * @param image image to rotate
 * @param angle angle of the rotation in degrees
 
Image rotate_image(Image *image, double angle)
{
    Image rotated_image = clone_image(image);
    printf("   🔃 Rotating image by %.0f° (%.5f rad)\n", angle,
        degrees_to_rad(angle));

    angle = degrees_to_rad(angle);

    int w = image->width;
    int h = image->height;
    double center_x = (w / (double)2);
    double center_y = (h / (double)2);

    Pixel black = {0, 0, 0};

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            double rx, ry;
            corrected_rotation_matrix(
                angle, (double)x, (double)y, center_x, center_y, &rx, &ry);

            if (0 <= rx && rx < w && 0 <= ry && ry < h)
            {
                Pixel org = image->pixels[(int)rx][(int)ry];
                Pixel dest = {org.r, org.g, org.b};
                rotated_image.pixels[x][y] = dest;
            }
            else
            {
                rotated_image.pixels[x][y] = black;
            }
        }
    }

    return rotated_image;
}*/

/*
my $screen  = SDL::Video::set_video_mode(800, 600, 32, SDL_SWSURFACE);
my $picture = SDL::Video::load_BMP('test.bmp');
 
my $rotated = SDL::GFX::Rotozoom::surface( $picture, 45, 0.8, SMOOTHING_ON );
 
SDL::Video::blit_surface( $rotated, SDL::Rect->new(0, 0, $rotated->w, $rotated->h), 
                          $screen,  SDL::Rect->new(0, 0, 0, 0) );
 
SDL::Video::update_rect( $screen, 0, 0, 0, 0 );*/
