#pragma once
#include <SDL2/SDL.h>
#include "gameplay.h"

#include "RenderUtilities.h"

void keyUp(SDL_KeyboardEvent *key);
void keyDown(SDL_KeyboardEvent *key);
void initGestion();
void gestionInputs();
