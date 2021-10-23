#include "Terrain.h"



niveau AleaCreaTion(int seed, int playerNb){
  srand(seed);
  niveau res;
  
  res.nbSalle = rand()%10 + 30;
  res.nbPlayer = playerNb;
  res.player = (entite *)malloc(sizeof(entite)*playerNb);
  
  for(int i = 0; i < playerNb; i++){
    res.player[i].sizeX = 1;
    res.player[i].sizeY = 2;
    res.player[i].x = 0;
    res.player[i].y = 0;
  }


  res.salle = (salle *)malloc(sizeof(salle)*res.nbSalle);
  for(int i = 0; i < res.nbSalle; i++){
    res.salle[i].lE = creerListe();

    for(int j = 0; j < TAILLE_X_SALLE; j++){
      for(int k = 0; k < TAILLE_Y_SALLE; k++){
	res.salle[i].terrain[j][k] = (rand()%2 == 1)?0:1;
      }
    }
    

    
  }

 
  
  return res;
}
