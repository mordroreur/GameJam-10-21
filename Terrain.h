#ifndef TERRAIN_HEADER_
#define TERRAIN_HEADER_

#include "listeEntite.h"

typedef struct Salle{

  int terrain[100][50];
  ListeEntite lE;
  
}salle;


typedef struct Niveau{

  int *player;
  int *salle;
  int nbPlayer;
  int nbSalle;
  
}niveau;



#endif /* TERRAIN_HEADER_ */
