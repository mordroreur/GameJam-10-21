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

    if(NiveauActuelle.salle[salleJoueur].terrain[(int)x][(int)(y+joueur->sizeY)] != 1) {
        if(joueur->ySpeed > 0) joueur->ySpeed *= GRAVITY_MULTIPLIER;
        else if(joueur->ySpeed == 0) joueur->ySpeed = 0.05;
    } else {
        joueur->ySpeed = 0;
    }

    if(inputsJoueurs[idJoueur][INPUT_RIGHT]) {
      joueur->xSpeed = 0.1;
    } else if(inputsJoueurs[idJoueur][INPUT_LEFT]) {
      joueur->xSpeed = -0.1;
    } else {
      joueur->xSpeed = 0;
    }

    joueur->y += joueur->ySpeed;
    joueur->x += joueur->xSpeed;
}