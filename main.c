#include "main.h"

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////       Declaration des variables globale     ///////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////


int EtapeActuelleDuJeu; /* 0 = fin; 1 = Loading Screen... */

int TailleEcranLong; /* Taille de l'ecran en nombre de pixel de gauche a droite */
int TailleEcranHaut; /* Taille de l'ecran en nombre de pixel de haut en bas */

SDL_Window *window = NULL; /* Adresse de la fenêtre que l'on va créer. */
SDL_Renderer *renderer = NULL; /* Adresse de l'endroit du dessin de la fenetre. */


int DEBUG = 0; /* 1 : affiche le debug*/


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

int main()
{
  //  srand(time(NULL)); // in case we need random

  EtapeActuelleDuJeu = 2;

  BouclePrincipaleDuJeu();

  
  
}
