#include "gest_event.h"

extern int EtapeActuelleDuJeu; /* 0 = fin; 1 = Loading Screen... */
extern int TailleEcranLong; /* Taille de l'ecran en nombre de pixel de gauche a droite */
extern int TailleEcranHaut; /* Taille de l'ecran en nombre de pixel de haut en bas */

extern SDL_Event event;

extern niveau NiveauActuelle;

void keyUp(SDL_KeyboardEvent *key){
  // printf("%d\n", key->keysym.sym);
  switch(key->keysym.sym){
  case SDLK_ESCAPE:EtapeActuelleDuJeu = 0;break;
  default:break;
  }
}

void keyDown(SDL_KeyboardEvent *key){
  // printf("%d\n", key->keysym.sym);
  switch(key->keysym.sym){
  case SDLK_q:EtapeActuelleDuJeu = 0;break;
  default:break;
  }
}

void gestionInputs() {
/* Gestion des inputs clavier */
    
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_KEYDOWN:
        keyDown(&event.key);
        break;
      case SDL_KEYUP:
        keyUp(&event.key);
        break;
      case SDL_MOUSEWHEEL:
        // if (event.wheel.y > 0) {
	// } else if (event.wheel.y < 0) {
	// }
        break;
      case SDL_MOUSEBUTTONDOWN:
        // if (event.button.button == SDL_BUTTON_LEFT) {
        // } else if (event.button.button == SDL_BUTTON_RIGHT) {
	// }
        break;
      case SDL_QUIT:
        EtapeActuelleDuJeu = 0;
        break;
      case SDL_WINDOWEVENT:
	if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
	  TailleEcranHaut = event.window.data2;
	  TailleEcranLong = event.window.data1;
	}
	break;
      default:
        break;
      }
    }
    for(int i = 0; i < NiveauActuelle.nbPlayer; i++) {
      gestionPhysiquesJoueur(i);
    }
}
