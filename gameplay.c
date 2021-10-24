#include "gameplay.h"


extern niveau NiveauActuelle;

extern int ** inputsJoueurs;
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define Block_Solid 1
#define Block_Air 0

int blockIsSolid(int id)
{
  return id == 1;
}


int getBlockId(int x, int y)
{
  int salleNb = x/TAILLE_X_SALLE;

  if(salleNb<0 || salleNb >= NiveauActuelle.nbSalle)
  {
    return Block_Air;
  }
  return getBlockIdRelative(&(NiveauActuelle.salle[salleNb]), x, y);
}


int getBlockIdRelative(salle* s, int x, int y)
{
  x %= TAILLE_X_SALLE;
  return x >= 0 && x <TAILLE_X_SALLE && y >= 0 && y <TAILLE_Y_SALLE ?
    s->terrain[x][y] : Block_Air;
}

int getSalleEntite(entite ent) {
    return (ent.x / TAILLE_X_SALLE);
}

int moveEntityY(entite* e, float y)
{
  if(y == 0){return 1;}

  int xMinTile = floorf(e->x+0.2);
  int xMaxTile = ceilf(e->x+e->sizeX - 0.2);

  int yNewTile;
  e->y += y;

  if(y > 0)
  {
    yNewTile = floorf(e->y+e->sizeY);
    
    for(int i = xMinTile; i < xMaxTile;i++)
    {
      if(blockIsSolid(getBlockId(i, yNewTile)))
      {
        e->y = (yNewTile-e->sizeY);
        // printf("SNAP %f\n", e->y);
        return 0;
      }
    }
    return 1;
  }
  
  yNewTile = floorf(e->y);
  for(int i = xMinTile; i < xMaxTile;i++)
  {
    if(blockIsSolid(getBlockId(i, yNewTile)))
    {
      e->y = (yNewTile+1);
      return 0;
    }
  }
  return 1;
}

int moveEntityX(entite* e, float x)
{
  if(x == 0){return 1;}

  int yMinTile = floorf(e->y)+1;
  int yMaxTile = floorf(e->y+e->sizeY);
  salle* s = &(NiveauActuelle.salle[getSalleEntite(*e)]);

  int xNewTile;
  e->x += x;

  if(x > 0)
  {
    xNewTile = floorf(e->x+e->sizeX);
    
    for(int i = yMinTile; i < yMaxTile;i++)
    {
      if(blockIsSolid(getBlockId(xNewTile, i)))
      {
        e->x = (xNewTile-e->sizeX);
        return 0;
      }
    }
    return 1;
  }
  
  xNewTile = floorf(e->x);
  for(int i = yMinTile; i < yMaxTile;i++)
  {
    if(blockIsSolid(getBlockId(xNewTile, i)))
    {
      e->x = (xNewTile+1);
      return 0;
    }
  }
  return 1;
}



void gestionPhysiquesJoueur(int idJoueur) {
    entite * joueur = &NiveauActuelle.player[idJoueur];
    float x = joueur->x, y = joueur->y;
    int salleJoueur = getSalleEntite(*joueur);
    int isJumping = 0;
    int grounded = 0;


/*
    if(NiveauActuelle.salle[salleJoueur].terrain[(int)x][(int)(y+joueur->sizeY)] != 1) {
        grounded = 0;
        if(joueur->ySpeed > 0) joueur->ySpeed *= GRAVITY_MULTIPLIER;
        else if(joueur->ySpeed == 0) joueur->ySpeed = 0.05;
        else joueur->ySpeed *= (1 - GRAVITY_MULTIPLIER);
    } else {
        grounded = 1;
        joueur->ySpeed = 0;
    }
    */
    
    joueur->ySpeed = MIN(16.0/64, joueur->ySpeed+1/128.0);

    
    if(moveEntityY(joueur, joueur->ySpeed) == 0)
    {
      joueur->ySpeed = 0;
      grounded = 1;
      // printf("A1\n");
    }else
    {

      // printf("A0\n");

    }
      //joueur->ySpeed = 0;

      //grounded=1;
    //printf("x:%f, y:%f\n", joueur->x, joueur->y);


    if(inputsJoueurs[idJoueur][INPUT_RIGHT] && grounded) {
      joueur->xSpeed = MIN(joueur->xSpeed + X_ACCEL, X_TERM_VELOCITY);
    } else if(inputsJoueurs[idJoueur][INPUT_LEFT] && grounded) {
      joueur->xSpeed = MAX(joueur->xSpeed - X_ACCEL, -X_TERM_VELOCITY);
    } else if (grounded && joueur->xSpeed > 0){
      joueur->xSpeed = MAX(0, joueur->xSpeed-GROUND_FRICTION);
    } else if (grounded && joueur->xSpeed < 0){
      joueur->xSpeed = MIN(0, joueur->xSpeed+GROUND_FRICTION);
    }

    if(inputsJoueurs[idJoueur][INPUT_RIGHT] && !grounded) {
      joueur->xSpeed = MIN(joueur->xSpeed + X_ACCEL_AERIAL, X_TERM_VELOCITY);
    } else if(inputsJoueurs[idJoueur][INPUT_LEFT] && !grounded) {
      joueur->xSpeed = MAX(joueur->xSpeed - X_ACCEL_AERIAL, -X_TERM_VELOCITY);
    } else if (!grounded && joueur->xSpeed > 0){
      joueur->xSpeed = MAX(0, joueur->xSpeed-AIR_FRICTION);
    } else if (!grounded && joueur->xSpeed < 0){
      joueur->xSpeed = MIN(0, joueur->xSpeed+AIR_FRICTION);
    }


    // Jetpack
    // if(inputsJoueurs[idJoueur][INPUT_JUMP] && joueur->ySpeed < 2) {
    //   joueur->ySpeed -= 0.05;
    // }

    if(inputsJoueurs[idJoueur][INPUT_JUMP] && grounded) {
      joueur->ySpeed = -20/64.0;
      isJumping = 1;
      inputsJoueurs[idJoueur][INPUT_JUMP] = 0;
    }

/*
    if(NiveauActuelle.salle[salleJoueur].terrain[(int)x][(int)(y+joueur->sizeY+joueur->ySpeed)] != 1) {
      joueur->y += joueur->ySpeed;
    }
    */

    if(moveEntityX(joueur, joueur->xSpeed) == 0)
    {
      joueur->xSpeed = 0;
    }
}
