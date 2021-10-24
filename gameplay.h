#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Entite.h"
#include "Terrain.h"
#include "listeEntite.h"

#define GRAVITY 1/128.0
#define JUMP_HEIGHT -15/64.0
#define HELD_JUMP_BOOST 1/256.0

#define AIR_FRICTION 0.0015
//0.0003
#define GROUND_FRICTION 0.01

#define X_ACCEL 0.01
#define X_ACCEL_AERIAL 0.0025
#define X_TERM_VELOCITY_AERIAL 0.175
//0.2
#define X_TERM_VELOCITY 0.2

#define NB_INPUTS 4
#define INPUT_JUMP 0
#define INPUT_LEFT 1
#define INPUT_RIGHT 2
#define INPUT_ITEM 3

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define Hitbox_Precision (2/16.0)

#define Block_Semisolid 2
#define Block_Solid 1
#define Block_Air 0

int getBlockIdRelative(salle* s, int x, int y);
int getBlockId(int x, int y);
int getSalleEntite(entite ent);
void gestionPhysiquesJoueur(int idJoueur);

void checkEntityCollisions(int idJoueur);
int checkCollision(entite * joueur, entite * entity);
void processCollision(int idJoueur, entite * entity);

int blockIsSolid(int id); 
int blockIsSemiSolid(int id); 

float xHitboxPos(entite* e);
float yHitboxPos(entite* e);

// 0 = pas reussi
// 1 = reuss à te déplacer
int moveEntityX(entite* e, float x);
int moveEntityY(entite* e, float y);