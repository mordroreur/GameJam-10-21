#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Entite.h"
#include "Terrain.h"

#define GRAVITY_MULTIPLIER 1.1
#define AIR_FRICTION 0.0003
#define GROUND_FRICTION 0.01

#define X_ACCEL 0.01
#define X_ACCEL_AERIAL 0.0025
#define X_TERM_VELOCITY 0.2

#define NB_INPUTS 4
#define INPUT_JUMP 0
#define INPUT_LEFT 1
#define INPUT_RIGHT 2
#define INPUT_ITEM 3

int getBlockIdRelative(salle* s, int x, int y);
int getBlockId(int x, int y);
int getSalleEntite(entite ent);
void gestionPhysiquesJoueur(int idJoueur);

int blockIsSolid(int id); 

// 0 = pas reussi
// 1 = reuss à te déplacer
int moveEntityX(entite* e, float x);
int moveEntityY(entite* e, float y);