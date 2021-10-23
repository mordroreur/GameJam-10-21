#include "Terrain.h"

#define NombreDeSalleConnu 1


niveau AleaCreaTion(int seed, int playerNb){
  srand(seed);
  niveau res;
  
  res.nbSalle = rand()%10 + 30;
  res.nbPlayer = playerNb;
  res.player = (entite *)malloc(sizeof(entite)*playerNb);
  
  for(int i = 0; i < playerNb; i++){
    res.player[i].sizeX = 2;
    res.player[i].sizeY = 2;
    res.player[i].xSpeed = 0;
    res.player[i].ySpeed = 0;
    res.player[i].x = 5;
    res.player[i].y = 5;
    res.player[i].direction = 1;

  }


  res.salle = (salle *)malloc(sizeof(salle)*res.nbSalle);

  res.salle[0] = getFirstSalle(rand());
  
  for(int i = 1; i < res.nbSalle; i++){
    res.salle[i].lE = creerListe();

    if(rand()%3 < 3){
      res.salle[i] = getKnownSalle(rand());
    }else {
      for(int j = 0; j < TAILLE_X_SALLE; j++){
	for(int k = 0; k < TAILLE_Y_SALLE; k++){
	  res.salle[i].terrain[j][k] = (rand()%2 == 1)?0:1;
	}
      }
    }
    
    
    
  }

 
  
  return res;
}

salle getFirstSalle(int n){
  salle s;
  for(int i = 0; i < TAILLE_X_SALLE/5; i++){
    for(int j = 0; j < TAILLE_Y_SALLE; j++){
      if(j < 15 && i != 0 ){
	s.terrain[i][j] = 0;
      }else {
	s.terrain[i][j] = 1;
      }
    }
  }

  for(int i = TAILLE_X_SALLE/5; i < TAILLE_X_SALLE; i++){
    for(int j = 0; j < TAILLE_Y_SALLE; j++){
      int x = s.terrain[i-1][j];
      if(j < TAILLE_Y_SALLE-1){
	x = s.terrain[i-1][j+1];
      }
      if(j > 0){
	x = s.terrain[i-1][j-1];
      }
      
      if(x == 3){
	s.terrain[i][j] = 1;
      }else if(x == 0){
	s.terrain[i][j] = 0;
      }else if((x == 2 && rand()%100 < 75) || (x == 1 && rand()%100 < 25)){
	s.terrain[i][j] = 1;
      }else {
	s.terrain[i][j] = 0;
      }
    }
  }

  s.terrain[8][15] = 0;
  s.terrain[9][15] = 0;
  s.terrain[8][16] = 0;
  s.terrain[9][16] = 0;
  s.terrain[8][17] = 0;
  s.terrain[9][17] = 0;

  s.terrain[1][5] = 1;
  s.terrain[2][6] = 1;

  s.terrain[2][10] = 1;
  s.terrain[3][10] = 1;
  return s;
}


salle getKnownSalle(int n){
  salle s;
  switch (n % NombreDeSalleConnu) {
  case 0 :
    for(int i = 0; i < TAILLE_X_SALLE; i++){
      for(int j = 0; j < TAILLE_Y_SALLE; j++){
	if(j != 15){
	  s.terrain[i][j] = 0;
	}else {
	  s.terrain[i][j] = 1;
	}
      }
    }break;
  default:
    for(int i = 0; i < TAILLE_X_SALLE; i++){
      for(int j = 0; j < TAILLE_Y_SALLE; j++){
	s.terrain[i][j] = 0;
      }
    }
  }

  return s;
}
