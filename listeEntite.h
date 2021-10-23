#ifndef LISTEENTITE_HEADER_
#define LISTEENTITE_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include "Entite.h"

typedef struct Maillon{
  struct Maillon *suiv;
  entite val;
}Maillon;


typedef struct Liste{
  struct Maillon *first;
}ListeEntite;


ListeEntite creerListe();
void detruireListe(ListeEntite l);
void ajouteDebut(ListeEntite *l, entite n);
void ajouteFin(ListeEntite *l, entite n);
void afficheListe(ListeEntite l);
int ListLenght(ListeEntite l);
void supprDebut(ListeEntite *l);
void supprFin(ListeEntite *l);
void supprValeur(ListeEntite *l, entite val);
void supprMaillon(ListeEntite *l, int nbMaillon);


#endif /* LISTEENTITE_HEADER_ */
