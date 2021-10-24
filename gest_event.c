#include "gest_event.h"
#include "gameplay.h"
#include <SDL2/SDL_keycode.h>

extern int EtapeActuelleDuJeu; /* 0 = fin; 1 = Loading Screen... */
extern int TailleEcranLong; /* Taille de l'ecran en nombre de pixel de gauche a droite */
extern int TailleEcranHaut; /* Taille de l'ecran en nombre de pixel de haut en bas */

extern SDL_Event event;

int **inputsJoueurs;

extern int ToucheAppuiPlayer[2][4];

extern niveau NiveauActuelle;

void keyUp(SDL_KeyboardEvent *key){
  // printf("%d\n", key->keysym.sym);
  /*switch(key->keysym.sym){
  case SDLK_ESCAPE:EtapeActuelleDuJeu = 0;break;
  case SDLK_UP:inputsJoueurs[0][INPUT_JUMP] = 0;break;
  case SDLK_RIGHT:inputsJoueurs[0][INPUT_RIGHT] = 0; break;
  case SDLK_LEFT:inputsJoueurs[0][INPUT_LEFT] = 0; break;
  case SDLK_DOWN:inputsJoueurs[0][INPUT_ITEM] = 0;break;

  case SDLK_z:inputsJoueurs[1][INPUT_JUMP] = 0;break;
  case SDLK_d:inputsJoueurs[1][INPUT_RIGHT] = 0; break;
  case SDLK_q:inputsJoueurs[1][INPUT_LEFT] = 0; break;
  case SDLK_s:inputsJoueurs[1][INPUT_ITEM] = 0;break;
  default:break;
  }*/
  if(key->keysym.sym == SDLK_ESCAPE){
    EtapeActuelleDuJeu = 0;
  }else{
    for(int i = 0; i < NiveauActuelle.nbPlayer; i++){
      for(int j = 0; j < NB_INPUTS; j++){
	if(key->keysym.sym == ToucheAppuiPlayer[i][j]){
	  inputsJoueurs[i][j] = 0;
	}
      }
    }
  }
}

void keyDown(SDL_KeyboardEvent *key){
  // printf("%d\n", key->keysym.sym);
  /*switch(key->keysym.sym){
  case SDLK_UP:inputsJoueurs[0][INPUT_JUMP] = 1;break;
  case SDLK_RIGHT:inputsJoueurs[0][INPUT_RIGHT] = 1; NiveauActuelle.player[0].direction = 1; break;
  case SDLK_LEFT:inputsJoueurs[0][INPUT_LEFT] = 1; NiveauActuelle.player[0].direction = 0; break;
  case SDLK_DOWN:inputsJoueurs[0][INPUT_ITEM] = 1;break;

  case SDLK_z:inputsJoueurs[1][INPUT_JUMP] = 1;break;
  case SDLK_d:inputsJoueurs[1][INPUT_RIGHT] = 1; NiveauActuelle.player[1].direction = 1; break;
  case SDLK_q:inputsJoueurs[1][INPUT_LEFT] = 1;  NiveauActuelle.player[1].direction = 0; break;
  case SDLK_s:inputsJoueurs[1][INPUT_ITEM] = 1;break;
  default:break;
  }*/
  for(int i = 0; i < NiveauActuelle.nbPlayer; i++){
    for(int j = 0; j < NB_INPUTS; j++){
      if(key->keysym.sym == ToucheAppuiPlayer[i][j]){
        if(!key->repeat) {
	        inputsJoueurs[i][j] = 1;
        }
	      if(j == INPUT_RIGHT){
	        NiveauActuelle.player[i].direction = 1;
	      }else if(j == INPUT_LEFT){
	        NiveauActuelle.player[i].direction = 0;
	      }
      }
    }
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
      case SDL_JOYBUTTONDOWN:
	if(event.jbutton.button == 0){
	  inputsJoueurs[event.jbutton.which][INPUT_JUMP] = 1;
	}break;
      case SDL_JOYBUTTONUP:
	if(event.jbutton.button == 0){
	  inputsJoueurs[event.jbutton.which][INPUT_JUMP] = 0;
	}break;
      default:
        break;
      }
    }

    GetManetteInput();

     for(int i = 0; i < NiveauActuelle.nbPlayer; i++) {
       gestionPhysiquesJoueur(i);
     }
    

}
