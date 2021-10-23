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

#define FPS_TO_GET 60  /*!< Frames render per second*/
#define TICK_TO_GET 60 /*!< Verification done per second*/


int BouclePrincipaleDuJeu();


void create_Win();


void end_sdl(char ok, char const *msg);


void *BouclePrincipaleDesTicks(void *CeciEstUneVaribleNull);


void DessinPrincipale();

#endif /* RENDER_HEADER_ */
