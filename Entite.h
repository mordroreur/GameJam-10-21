#ifndef ENTITE_HEADER_
#define ENTITE_HEADER_

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

  int type;
  int equipe; 
  int direction;
}entite;




#endif /* ENTITE_HEADER_ */
