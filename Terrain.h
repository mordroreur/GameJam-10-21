#ifndef TERRAIN_HEADER_
#define TERRAIN_HEADER_

#include "listeEntite.h"
#include "Entite.h"

#include <stdlib.h>

#define TAILLE_X_SALLE 100
#define TAILLE_Y_SALLE 50

#define ENTITY_PLAYER 0
#define ENTITY_POWERUP_CRISTAL_RESET 1

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
salle getKnownSalle(int n, int *Begin);
salle getFirstSalle(int n, int *Begin);

#endif /* TERRAIN_HEADER_ */
