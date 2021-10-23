#include "listeEntite.h"
#include "Entite.h"

ListeEntite creerListe(){
  ListeEntite l;
  l.first = NULL;
  return l;
}

void detruireListe(ListeEntite l){
  Maillon *old;
  Maillon *new;
  
  new = l.first;
  while (new != NULL) {
    old = new;
    new = new->suiv;
    free(old);
  }
}

void ajouteDebut(ListeEntite *l, entite n){
  Maillon *M = (Maillon *)malloc(sizeof(Maillon));
  
  M->val.type = n.type;

  
  M->suiv = l->first;
  l->first = M;
}

void ajouteFin(ListeEntite *l, entite n){
  Maillon *M = (Maillon *)malloc(sizeof(Maillon));
  Maillon *new;

  M->val.type = n.type;
  
  M->suiv = NULL;
  if(l->first == NULL){
    l->first = M;
  }else{
    new = l->first;
    while (new->suiv != NULL) {
      new = new->suiv;
    }
    new->suiv = M;
  }
}

void afficheListe(ListeEntite l){
  Maillon *new;
  
  new = l.first;
  if(new == NULL){
    printf("La suite est vide.\n");
  }else{
    printf("La suite vaut : %d", new->val.type);
    new = new->suiv;
    while(new != NULL) {
      printf(", %d", new->val.type);
      new = new->suiv;
    }
    printf("\n");
  }
}

int ListLenght(ListeEntite l){
  Maillon *new;
  int result = 0;
  

  if(l.first != NULL){
    new = l.first;
    while (new != NULL) {
      new = new->suiv;
      result++;
    }
  }
  return result;
}


void supprDebut(ListeEntite *l){
  Maillon *new;
  if(l->first != NULL){
    new = l->first;
    l->first = new->suiv;
    free(new);
  }
}

void supprFin(ListeEntite *l){
  Maillon *new;
  if(l->first != NULL){
    new = l->first;
    while (new->suiv != NULL) {
      new = new->suiv;
    }
    free(new->suiv);
    new->suiv = NULL;
  }
}

void supprValeur(ListeEntite *l, entite val){
  Maillon *new;
  Maillon *old;
  if(l->first != NULL){
    if(l->first->val.type == val.type){
      supprDebut(l);
    }else{
      new = l->first;
      while ((new->suiv != NULL) && (new->suiv->val.type != val.type)) {
	new = new->suiv;
      }
      if(new->suiv != NULL){
	old = new->suiv->suiv;
	free(new->suiv);
	new->suiv = old;
      }
    }
  }
}

void supprMaillon(ListeEntite *l, int nbMaillon){
  Maillon *new;
  Maillon *old;

  if(nbMaillon == 0){
    supprDebut(l);
  }else{
    new = l->first;
    for(int i = 0; i < nbMaillon-1; i++){
      new = new->suiv;
      if(new == NULL){
	break;
      }
    }
    if(new != NULL){
      old = new->suiv->suiv;
      free(new->suiv);
      new->suiv = old;
    }
  }
}
