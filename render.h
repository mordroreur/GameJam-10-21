#ifndef RENDER_HEADER_
#define RENDER_HEADER_

#include "RenderUtilities.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <time.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Terrain.h"
#include "gest_event.h"
#include "gameplay.h"

#define FPS_TO_GET 60  /*!< Frames render per second*/
#define TICK_TO_GET 60 /*!< Verification done per second*/


int BouclePrincipaleDuJeu();


void create_Win();


void end_sdl(char ok, char const *msg);


void *BouclePrincipaleDesTicks(void *CeciEstUneVaribleNull);

//Dessine un sprite dans le render 
void DrawCamera(
  float camX, float camY, float nbBlockY, 
  int camPixelX, int camPixelY,
  int camPixelOffsetX, int camPixelOffsetY);

void DrawSprite(float x, float y, 
    float sizeX, float sizeY,
    SDL_Surface* sprite, int flip, SDL_Rect* source);

void DrawBlockAt(int x, int y);
void DrawBlock(int x, int y, SDL_Surface* sprite, SDL_Rect* source);


void DessinPrincipale();

void WinOrange();

void WinVert();



#endif /* RENDER_HEADER_ */
