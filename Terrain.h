#ifndef TERRAIN_HEADER_
#define TERRAIN_HEADER_

#include "listeEntite.h"

#include <stdlib.h>

#define TAILLE_X_SALLE 100
#define TAILLE_Y_SALLE 50

typedef struct Salle{

  int terrain[TAILLE_X_SALLE][TAILLE_Y_SALLE];
  ListeEntite lE;
  
}salle;


typedef struct Niveau{

  entite *player;
  salle *salle;
  int nbPlayer;
  int nbSalle;
  
}niveau;

niveau AleaCreaTion(int seed, int playerNb);
salle getKnownSalle(int n);
salle getFirstSalle(int n);


entite* entityNew();
void entityInit(entite* e, float x, float y, float sizeX, float sizeY, float xHitbox, float yHitbox, float xHitboxOffsetPourcentage, float yHitboxOffsetPourcentage);

#endif /* TERRAIN_HEADER_ */
