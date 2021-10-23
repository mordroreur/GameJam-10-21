#include "gameplay.h"

extern niveau NiveauActuelle;

int getSalleEntite(entite ent) {
    return (ent.x / TAILLE_X_SALLE);
}

void gestionPhysiquesJoueur(int idJoueur) {
    entite * joueur = &NiveauActuelle.player[idJoueur];
    float x = joueur->x, y = joueur->y;
    printf("%f %f\n", x, y);
    int salleJoueur = getSalleEntite(*joueur);
    if(NiveauActuelle.salle[salleJoueur].terrain[(int)x][(int)y] != 1) {
        joueur->y += 0.1;
    }
}