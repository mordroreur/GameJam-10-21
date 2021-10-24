#ifndef ENTITE_HEADER_
#define ENTITE_HEADER_

#include <stdlib.h>
#include <stdio.h>

#define ENTITY_PLAYER 0
#define ENTITY_POWERUP_CRISTAL_RESET 1
#define ENTITY_POWERUP_COINY 2
#define ENTITY_POWERUP_JETPACK 2

typedef struct Entite{

  float x;
  float y;

  float xSpeed;
  float ySpeed;

  float sizeX; //Animation
  float sizeY;

  float xHitbox; // taille de la hitbox
  float yHitbox;

  float xHitboxOffset; // offset entre x et le coin de la hitbox
  float yHitboxOffset;

  int heldPowerup;
  int durabiliteJetpack;
  int type;
  int equipe; 
  int direction;
}entite;

entite* entityNew(int type);
void entityInit(entite* e, float x, float y, float sizeX, float sizeY, float xHitbox, float yHitbox, float xHitboxOffsetPourcentage, float yHitboxOffsetPourcentage);



#endif /* ENTITE_HEADER_ */
