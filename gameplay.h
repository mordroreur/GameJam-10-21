#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Entite.h"
#include "Terrain.h"

#define GRAVITY_MULTIPLIER 0.9
#define AIR_FRICTION 0.8

int getSalleEntite(entite ent);
void gestionPhysiquesJoueur(int idJoueur);