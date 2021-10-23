#ifndef RENDERUTILLITIES_HEADER_
#define RENDERUTILLITIES_HEADER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <time.h>


void DrawString(char *s, int x, int y, int size, char center, int R, int G, int B);


long int getTime();


void DrawMenu();



#endif /* RENDERUTILLITIES_HEADER_ */
