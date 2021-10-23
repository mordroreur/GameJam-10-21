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



#endif /* TERRAIN_HEADER_ */
