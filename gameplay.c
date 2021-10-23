#include "gameplay.h"


extern niveau NiveauActuelle;

extern int ** inputsJoueurs;
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))


int getSalleEntite(entite ent) {
    return (ent.x / TAILLE_X_SALLE);
}

int moveEntityY(entite* e, float y)
{
  if(y == 0){return 1;}

  int xMinTile = MAX(0,floorf(e->x));
  int xMaxTile = MIN(TAILLE_X_SALLE-1, floorf(e->x+e->sizeX));
  int numSalle = getSalleEntite(*e);

  float yOld, yNew;
  int yOldTile, yNewTile;

  if(y > 0)
  {
    yOld = e->y+e->sizeY;
    yNew = yOld+y;

    yOldTile = floorf(yOld);
    yNewTile = floorf(yNew);
    
    if(yOldTile != yNewTile && (yNewTile < TAILLE_Y_SALLE && yNewTile >= 0))
    {
      for(int i = xMinTile; i<= xMaxTile;i++)
      {
        if(NiveauActuelle.salle[numSalle].terrain[i][yNewTile] == 1)
        {
          e->y = yNewTile-e->sizeY-0.00001;
          return 0;
        }
      } 
    } 
    e->y += y;
    return 1;
  }
  return 1;
    yOld = e->y+e->sizeY;
    yNew = yOld+y;

    yOldTile = floorf(yOld);
    yNewTile = floorf(yNew);
    
    if(yOldTile != yNewTile && (yNewTile < TAILLE_Y_SALLE && yNewTile >= 0))
    {
      for(int i = xMinTile; i<= xMaxTile;i++)
      {
        if(NiveauActuelle.salle[numSalle].terrain[i][yNewTile] == 1)
        {
          e->y = yNewTile-e->sizeY-0.00001;
          return 0;
        }
      } 
    } 
    e->y += y;
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
    joueur->ySpeed = MIN(16.0/64, joueur->ySpeed+1/64.0);

    if(moveEntityY(joueur, joueur->ySpeed) == 0)
    {
      joueur->ySpeed = 0;
      grounded = 1;
      printf("1\n");
    }else
    {
      printf("0\n");

    }
      //joueur->ySpeed = 0;

      //grounded=1;


    if(inputsJoueurs[idJoueur][INPUT_RIGHT]) {
      joueur->xSpeed = ((joueur->xSpeed + X_ACCEL < X_TERM_VELOCITY) ? joueur->xSpeed + X_ACCEL : X_TERM_VELOCITY);
    } else if(inputsJoueurs[idJoueur][INPUT_LEFT]) {
      joueur->xSpeed = ((joueur->xSpeed - X_ACCEL > -X_TERM_VELOCITY) ? joueur->xSpeed - X_ACCEL : -X_TERM_VELOCITY);
    } else {
      joueur->xSpeed = 0;
    }

    // Jetpack
    // if(inputsJoueurs[idJoueur][INPUT_JUMP] && joueur->ySpeed < 2) {
    //   joueur->ySpeed -= 0.05;
    // }

    if(inputsJoueurs[idJoueur][INPUT_JUMP] && grounded) {
      joueur->ySpeed -= 3;
      isJumping = 1;
      inputsJoueurs[idJoueur][INPUT_JUMP] = 0;
    }

/*
    if(NiveauActuelle.salle[salleJoueur].terrain[(int)x][(int)(y+joueur->sizeY+joueur->ySpeed)] != 1) {
      joueur->y += joueur->ySpeed;
    }
    */
    joueur->x += joueur->xSpeed;
}