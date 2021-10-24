#ifndef RENDERUTILLITIES_HEADER_
#define RENDERUTILLITIES_HEADER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <time.h>

#include "Terrain.h"

void DrawString(char *s, int x, int y, int size, char center, int R, int G, int B);


long int getTime();


void DrawMenu();


void ClickOnMenu();


void ClickOnParam();


void GetManetteInput();


void ManetteInit();



#endif /* RENDERUTILLITIES_HEADER_ */
