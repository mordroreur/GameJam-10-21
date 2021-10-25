#include "Terrain.h"

#define NombreDeSalleConnu 2



int indexValid(int x, int y)
{
  return x >= 0 && x < TAILLE_X_SALLE && y >= 0 && y<TAILLE_Y_SALLE; 
}


void set(salle* s, int x, int y, int id)
{
  if(indexValid(x,y))
  {
    s->terrain[x][y] = id;
  } 
}


void fill(salle* s, int xBegin, int xLength, int yBegin, int yLength, int id)
{
  if(xLength < 0)
  {
    fill(s, xBegin+xLength, -xLength, yBegin, yLength, id);
    return;
  } 
  if(yLength < 0)
  {
    fill(s, xBegin, xLength, yBegin+yLength, -yLength, id);
    return;
  } 

  for(int x = xBegin; x<=xBegin+xLength; x++)
  {
    for(int y = yBegin; y <= yBegin+yLength;y++)
    {
      set(s, x, y, id);
    } 
  } 
}

void addRandomPowerUp(salle* s, int x, int y)
{
  entite* jetpack = entityNew(rand()%3+1);
  entityInit(jetpack, x, y, 1, 1, 1, 1, 0.5, 0.5);
  ajouteDebut(&(s->lE), *jetpack);
}


void placePlatform(salle* s, int x, int y, int size, int nbTime)
{
  if(nbTime < 0)
  {return;}

  fill(s, x, size, y, 0, 2);
  placePlatform(s, x+rand()%10, y+rand()%9-7, 2+rand()%7, nbTime-1);

  if(nbTime == 0){
    addRandomPowerUp(s, x+rand()%5,y-1);
  }
}


//y : y enter & y leave
salle GetRandomRoom(int i, int* y)
{
  salle s;
  s.lE = creerListe();

  fill(&s, 0, TAILLE_X_SALLE, 0, TAILLE_Y_SALLE, 0);

  for(int x = 0; x < TAILLE_X_SALLE;x++)
  {
    for(int y = 0; y < TAILLE_X_SALLE;y++)
    {
        set(&s, x, y, rand()%(17+9)==1 ? 3 : 0);
    } 
  } 

  if(i==0)
  {
    fill(&s, 0, 0, 0, TAILLE_Y_SALLE, 1);
  }

/*
  entite* jetpack = entityNew(ENTITY_POWERUP_JETPACK);
  entityInit(jetpack, 1, *y-2, 1, 1, 1, 1, 0.5, 0.5);
  ajouteDebut(&(s.lE), *jetpack);*/

  // int yEnter = *y;
  int x  = 0;
  while(x<TAILLE_X_SALLE)
  {
    int length = rand()%20+1;
    int height = rand()%11-5;

    if((*y > TAILLE_Y_SALLE-10 && height > 0)|| (*y < 10 && height < 0))
    {
        height = -height;
    }

    fill(&s, x, length, *y, TAILLE_Y_SALLE-*y, 1);

    if(rand()%3==0)
    {
      int z = *y;
      placePlatform(&s, x, z-3-rand()%6, 3+rand()%10, rand()%3);
    } 


    x+=length;//+(rand()*rand()%7);
    *y+=height;
    //printf("x = %i, y = %i\n", x, )
  }

  int yEnd = *y;
  /*
  x = 0;
  int z = yEnter;
  while(x<TAILLE_X_SALLE)
  {
    if(rand()%3==0)
    {
      int l = 2+rand()%13;
      fill(&s, x, l, z, 1, 2);
      x+=l;
    } 
    else
    {
      x += 10+rand()%10*3;
    } 
  }*/


  *y = yEnd;

  return s;
}


niveau AleaCreaTion(int seed, int playerNb){
  srand(seed);
  niveau res;
  
  res.nbSalle = rand()%5 + 5 + 1;
  res.nbPlayer = playerNb;
  res.player = (entite *)malloc(sizeof(entite)*playerNb);
  
  for(int i = 0; i < playerNb; i++){

    entite* p = &(res.player[i]);
    p->direction = 1;
    p->type = ENTITY_PLAYER;
    p->equipe = i;

    entityInit(p, 
    1, 10,
    2,2,
    14/16.0, 22/16.0,
    0.7, 1
    );

  }

  
  res.salle = (salle *)malloc(sizeof(salle)*res.nbSalle);

  //res.salle[0] = getKnownSalle(0, &begin);
  //res.salle[0] = getFirstSalle(rand(), &begin);

  //printf("%d\n", begin);
  
  int yEnter = TAILLE_Y_SALLE-8;
  for(int i = 0; i < res.nbSalle-1; i++)
  {
    salle s =GetRandomRoom(i, &yEnter);
    res.salle[i] = s;
    
    /*
    res.salle[i].lE = creerListe();

    if(rand()%3 <= 1){
      res.salle[i] = getKnownSalle(rand(), &begin);
    }else {
      for(int j = 0; j < TAILLE_X_SALLE; j++){
        for(int k = 0; k < TAILLE_Y_SALLE; k++){
          res.salle[i].terrain[j][k] = (rand()%2 == 1)?0:1;
        }
      }
    }*/
    
    
    
    
  }
  for(int i = 0; i < TAILLE_X_SALLE; i++){
    for(int j = 0; j < TAILLE_Y_SALLE; j++){
      res.salle[res.nbSalle-1].terrain[i][j] = 3;
    }  
  }

 
  
  return res;
}




salle getFirstSalle(int n, int *Begin){
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
	x += s.terrain[i-1][j+1];
      }
      if(j > 0){
	x += s.terrain[i-1][j-1];
      }
      
      if(x == 3){
	s.terrain[i][j] = 1;
      }else if(x == 0){
	s.terrain[i][j] = 0;
      }else if((x == 2 && rand()%100 < 75) || (x == 1 && rand()%100 < 25)){
	s.terrain[i][j] = 1;
	if(i  == TAILLE_X_SALLE-1){
	  *Begin = j;
	}
      }else {
	s.terrain[i][j] = 0;
      }
    }
  }

  s.terrain[8][12] = 2;
  s.terrain[9][12] = 2;

  s.terrain[8][9] = 2;
  s.terrain[9][9] = 2;

  s.terrain[8][7] = 2;
  s.terrain[9][7] = 2;
  
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


salle getKnownSalle(int n, int *Begin){
  salle s;
  int tmpm5 = rand()%5 +1;
  switch (n % NombreDeSalleConnu) {
  case 0 :
    for(int i = 0; i < (int)(TAILLE_X_SALLE/(tmpm5)); i++){
      for(int j = 0; j < TAILLE_Y_SALLE; j++){
	if(j < (int)(*Begin+i/5)){
	  s.terrain[i][j] = 0;
	}else {
	  s.terrain[i][j] = 1;
	}
      }
    }
    for(int i = (int)(TAILLE_X_SALLE/(tmpm5)); i < TAILLE_X_SALLE; i++){
      for(int j = 0; j < TAILLE_Y_SALLE; j++){
	if(j < *Begin+TAILLE_X_SALLE/(tmpm5)/5 - (i-((int)(TAILLE_X_SALLE/(tmpm5))))/5){
	  s.terrain[i][j] = 0;
	}else {
	  s.terrain[i][j] = 1;
	}
      }
      if(i == TAILLE_X_SALLE-1){
	*Begin = *Begin+TAILLE_X_SALLE/(tmpm5)/5 - (i-((int)(TAILLE_X_SALLE/(tmpm5))))/5;
      }
    }
    /*for(int i = 0; i < TAILLE_X_SALLE){
      
      }*/
    break;
  case 1 :// Marchant salle (sans marchant(une barre))
    for(int i = 0; i < TAILLE_X_SALLE; i++){
      for(int j = 0; j < TAILLE_Y_SALLE; j++){
	if(j < *Begin){
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
