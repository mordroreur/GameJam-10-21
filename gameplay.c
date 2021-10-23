#include "gameplay.h"

extern niveau NiveauActuelle;

extern int ** inputsJoueurs;

int getSalleEntite(entite ent) {
    return (ent.x / TAILLE_X_SALLE);
}

void gestionPhysiquesJoueur(int idJoueur) {
    entite * joueur = &NiveauActuelle.player[idJoueur];
    float x = joueur->x, y = joueur->y;
    int salleJoueur = getSalleEntite(*joueur);
    int isJumping = 0;
    int grounded = 0;

    if(NiveauActuelle.salle[salleJoueur].terrain[(int)x][(int)(y+joueur->sizeY)] != 1) {
        grounded = 0;
        if(joueur->ySpeed > 0) joueur->ySpeed *= GRAVITY_MULTIPLIER;
        else if(joueur->ySpeed == 0) joueur->ySpeed = 0.05;
        else joueur->ySpeed *= (1 - GRAVITY_MULTIPLIER);
    } else {
        grounded = 1;
        joueur->ySpeed = 0;
    }

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

    // if(NiveauActuelle.salle[salleJoueur].terrain[(int)x][(int)(y+joueur->sizeY+joueur->ySpeed)] != 1) {
    joueur->y += joueur->ySpeed;
    // } 
    joueur->x += joueur->xSpeed;
}