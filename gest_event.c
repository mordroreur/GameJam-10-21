#include "gest_event.h"

extern int EtapeActuelleDuJeu; /* 0 = fin; 1 = Loading Screen... */
extern int TailleEcranLong; /* Taille de l'ecran en nombre de pixel de gauche a droite */
extern int TailleEcranHaut; /* Taille de l'ecran en nombre de pixel de haut en bas */

extern SDL_Event event;

int ** inputsJoueurs;

extern niveau NiveauActuelle;

void keyUp(SDL_KeyboardEvent *key){
  // printf("%d\n", key->keysym.sym);
  switch(key->keysym.sym){
  case SDLK_ESCAPE:EtapeActuelleDuJeu = 0;break;
  case SDLK_UP:inputsJoueurs[0][INPUT_JUMP] = 0;break;
  case SDLK_RIGHT:inputsJoueurs[0][INPUT_RIGHT] = 0;break;
  case SDLK_LEFT:inputsJoueurs[0][INPUT_LEFT] = 0;break;
  case SDLK_DOWN:inputsJoueurs[0][INPUT_ITEM] = 0;break;
  default:break;
  }
}

void keyDown(SDL_KeyboardEvent *key){
  // printf("%d\n", key->keysym.sym);
  switch(key->keysym.sym){
  case SDLK_UP:inputsJoueurs[0][INPUT_JUMP] = 1;break;
  case SDLK_RIGHT:inputsJoueurs[0][INPUT_RIGHT] = 1;break;
  case SDLK_LEFT:inputsJoueurs[0][INPUT_LEFT] = 1;break;
  case SDLK_DOWN:inputsJoueurs[0][INPUT_ITEM] = 1;break;
  default:break;
  }
}

void initGestion() {
  inputsJoueurs = (int **) malloc(NiveauActuelle.nbPlayer * sizeof(int *));
  for(int i = 0; i < NiveauActuelle.nbPlayer; i++){ 
    inputsJoueurs[i] = (int*) calloc(NB_INPUTS, sizeof(int));
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
