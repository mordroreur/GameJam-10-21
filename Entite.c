#include "Entite.h"

entite* entityNew(int type)
{
  entite * e = malloc(sizeof(entite));
  e->type = type;
  return e;
}

void entityInit(entite* e, float x, float y, float sizeX, float sizeY, float xHitbox, float yHitbox, float xHitboxOffsetPourcentage, float yHitboxOffsetPourcentage) 
{
  e->x=x;
  e->y=y;
  e->xSpeed=0;
  e->ySpeed=0;
  e->sizeX=sizeX;
  e->sizeY=sizeY;
  e->xHitbox=xHitbox;
  e->yHitbox=yHitbox;
  e->heldPowerup=-1;
  e->xHitboxOffset= (sizeX-xHitbox)*xHitboxOffsetPourcentage;
  e->yHitboxOffset= (sizeY-yHitbox)*yHitboxOffsetPourcentage;
}