#include "gameplay.h"


extern niveau NiveauActuelle;

extern int ** inputsJoueurs;


float xHitboxPos(entite* e)
{
  return e->x+e->xHitboxOffset;
}

float yHitboxPos(entite* e)
{
  return e->y+e->yHitboxOffset;
}

float yHitboxPos(entite* e);

int blockIsSolid(int id)
{
  return id == Block_Solid;
}

int blockIsSemiSolid(int id)
{
  return id == Block_Semisolid;
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

  int xMinTile = floorf(xHitboxPos(e) + Hitbox_Precision);
  int xMaxTile = ceilf(xHitboxPos(e)+e->xHitbox - Hitbox_Precision);

  int yNewTile;
  e->y += y;

  if(y > 0)
  {
    yNewTile = floorf(yHitboxPos(e)+e->yHitbox);
    
    for(int i = xMinTile; i < xMaxTile;i++)
    {
      int id = getBlockId(i, yNewTile);
      if(blockIsSolid(id) || blockIsSemiSolid(id))
      {
        e->y = (yNewTile-e->yHitbox-e->yHitboxOffset);
        // printf("SNAP %f\n", e->y);
        return 0;
      }
    }
    return 1;
  }
  
  yNewTile = floorf(yHitboxPos(e));
  for(int i = xMinTile; i < xMaxTile;i++)
  {
    if(blockIsSolid(getBlockId(i, yNewTile)))
    {
      e->y = (yNewTile+1-e->yHitboxOffset);
      return 0;
    }
  }
  return 1;
}

int moveEntityX(entite* e, float x)
{
  if(x == 0){return 1;}

  int yMinTile = floorf(yHitboxPos(e)-Hitbox_Precision)+1;
  int yMaxTile = floorf(yHitboxPos(e)+e->yHitbox+Hitbox_Precision);

  int xNewTile;
  e->x += x;

  if(x > 0)
  {
    xNewTile = floorf(xHitboxPos(e)+e->xHitbox);
    
    for(int i = yMinTile; i < yMaxTile;i++)
    {
      if(blockIsSolid(getBlockId(xNewTile, i)))
      {
        e->x = (xNewTile-e->xHitbox-e->xHitboxOffset);
        return 0;
      }
    }
    return 1;
  }
  
  xNewTile = floorf(xHitboxPos(e));
  for(int i = yMinTile; i < yMaxTile;i++)
  {
    if(blockIsSolid(getBlockId(xNewTile, i)))
    {
      e->x = (xNewTile+1-e->xHitboxOffset);
      return 0;
    }
  }
  return 1;
}



void gestionPhysiquesJoueur(int idJoueur) {
    entite * joueur = &NiveauActuelle.player[idJoueur];
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
    
    joueur->ySpeed = MIN(16.0/64, joueur->ySpeed+GRAVITY);

    
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
    // printf("size x%f\n", joueur->sizeX);
    //printf("size x%f, size y%f\n", joueur->sizeX, joueur->sizeY);
    //printf("x%f, y%f\n", joueur->x, joueur->y);


    if(inputsJoueurs[idJoueur][INPUT_RIGHT] && grounded) {
      joueur->xSpeed = MIN(joueur->xSpeed + X_ACCEL, X_TERM_VELOCITY);
    } else if(inputsJoueurs[idJoueur][INPUT_LEFT] && grounded) {
      joueur->xSpeed = MAX(joueur->xSpeed - X_ACCEL, -X_TERM_VELOCITY);
    } else if (grounded && joueur->xSpeed > 0){
      joueur->xSpeed = MAX(0, joueur->xSpeed - GROUND_FRICTION);
    } else if (grounded && joueur->xSpeed < 0){
      joueur->xSpeed = MIN(0, joueur->xSpeed + GROUND_FRICTION);
    }

    if(inputsJoueurs[idJoueur][INPUT_RIGHT] && !grounded) {
      joueur->xSpeed = MIN(joueur->xSpeed - AIR_FRICTION + X_ACCEL_AERIAL, X_TERM_VELOCITY_AERIAL);
    } else if(inputsJoueurs[idJoueur][INPUT_LEFT] && !grounded) {
      joueur->xSpeed = MAX(joueur->xSpeed - X_ACCEL_AERIAL + AIR_FRICTION, -X_TERM_VELOCITY_AERIAL);
    } else if (!grounded && joueur->xSpeed > 0){
      joueur->xSpeed = MAX(0, joueur->xSpeed - AIR_FRICTION);
    } else if (!grounded && joueur->xSpeed < 0){
      joueur->xSpeed = MIN(0, joueur->xSpeed + AIR_FRICTION);
    }

    // if(idJoueur == 1) printf("Speed : %f\n", joueur->xSpeed);
    // Jetpack
    // if(inputsJoueurs[idJoueur][INPUT_JUMP] && joueur->ySpeed < 2) {
    //   joueur->ySpeed -= 0.05;
    // }

    if(inputsJoueurs[idJoueur][INPUT_JUMP] == 1 && grounded) {
      joueur->ySpeed = JUMP_HEIGHT;
      inputsJoueurs[idJoueur][INPUT_JUMP] = 2;
    }

    if(inputsJoueurs[idJoueur][INPUT_JUMP] == 2 && !grounded) {
      joueur->ySpeed -= HELD_JUMP_BOOST;
      inputsJoueurs[idJoueur][INPUT_JUMP] = 2;
    }

    if(inputsJoueurs[idJoueur][INPUT_ITEM] == 1) {
      usePowerup(idJoueur);
    }

    // printf("J%d : %d\n", idJoueur, inputsJoueurs[idJoueur][INPUT_JUMP]);

/*
    if(NiveauActuelle.salle[salleJoueur].terrain[(int)x][(int)(y+joueur->sizeY+joueur->ySpeed)] != 1) {
      joueur->y += joueur->ySpeed;
    }
    */

    if(moveEntityX(joueur, joueur->xSpeed) == 0)
    {
      joueur->xSpeed = 0;
    }

    checkEntityCollisions(idJoueur);
    // entite ent = (NiveauActuelle.salle[0].lE.first)->val;
    // printf("%f %f\n", ent.x, ent.y);
}

void checkEntityCollisions(int idJoueur) {
  entite * joueur = &NiveauActuelle.player[idJoueur];
  Maillon * courant = NiveauActuelle.salle[getSalleEntite(*joueur)].lE.first;
  while(courant != NULL) {
    if(checkCollision(joueur, &((*courant).val))) {
      processCollision(idJoueur, &((*courant).val));
    }
    courant = ((*courant).suiv);
  }
}

int checkCollision(entite * joueur, entite * entity) {
  float xMinJoueur = joueur->x+joueur->xHitboxOffset;
  float xMaxJoueur = xMinJoueur+joueur->xHitbox;
  float yMinJoueur = joueur->y+joueur->yHitboxOffset;
  float yMaxJoueur = yMinJoueur+joueur->yHitbox;

  float xMinEntity = entity->x+entity->xHitboxOffset;
  float xMaxEntity = xMinEntity+entity->xHitbox;
  float yMinEntity = entity->y+entity->yHitboxOffset;
  float yMaxEntity = yMinEntity+entity->yHitbox;

  int collisionX = (xMinJoueur > xMaxEntity) != (xMaxJoueur > xMinEntity);
  int collisionY = (yMinJoueur > yMaxEntity) != (yMaxJoueur > yMinEntity);

  // printf("xminent %f, xmaxent %f\n", entity->x, entity->y);
  // printf("COLL X %d, COLL Y %d\n", collisionX, collisionY);

  return (collisionX && collisionY);
}

void processCollision(int idJoueur, entite * entity) {
  entite * joueur = &NiveauActuelle.player[idJoueur];
  switch(entity->type) {
    case ENTITY_POWERUP_CRISTAL_RESET:
      joueur->heldPowerup = ENTITY_POWERUP_CRISTAL_RESET;
      supprValeur(&(NiveauActuelle.salle[getSalleEntite(*joueur)].lE), *entity);
      // printf("POWERUP ACTIVE\n");
      break;
  }
}

void usePowerup(int idJoueur) {
  entite * joueur = &NiveauActuelle.player[idJoueur];
  switch(joueur->heldPowerup) {
    case ENTITY_POWERUP_CRISTAL_RESET:
      for (int i = 0; i < NiveauActuelle.nbPlayer; i++) {
              if (i != idJoueur) {
                NiveauActuelle.player[i].xSpeed = 0;
                NiveauActuelle.player[i].ySpeed = 0;
              }
            }
      joueur->heldPowerup = 0;
      break;
  }
}