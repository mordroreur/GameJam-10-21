#include "RenderUtilities.h"
#include "gameplay.h"
#include "gest_event.h"
#include <SDL2/SDL_joystick.h>

extern int EtapeActuelleDuJeu; /* 0 = fin; 1 = Loading Screen... */

extern int TailleEcranLong; /* Taille de l'ecran en nombre de pixel de gauche a droite */
extern int TailleEcranHaut; /* Taille de l'ecran en nombre de pixel de haut en bas */

extern SDL_Window *window; /* Adresse de la fenêtre que l'on va créer. */
extern SDL_Renderer *renderer; /* Adresse de l'endroit du dessin de la fenetre. */

extern int DEBUG; /* 1 : affiche le debug */

extern TTF_Font *RobotoFont;

extern SDL_Surface *background_image;

extern SDL_Surface *sprite_image_Star[3];
extern SDL_Surface *sprite_image_Fusee[2];


extern int ** inputsJoueurs;

extern niveau NiveauActuelle;

extern SDL_Event event;


long int getTime(){
  struct timespec tms;
  if (clock_gettime(CLOCK_REALTIME,&tms)) {
        return -1;
    }
  return ((tms.tv_sec*1000000) + (tms.tv_nsec/1000));
}


void DrawString(char *s, int x, int y, int size, char center, int R, int G, int B){
  int n = 0;
  while(s[n] != '\0'){
    n++;
  }

  SDL_Color Color = {R, G, B};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(RobotoFont, s, Color); 
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_Rect Message_rect;
  switch (center) {
  case 'n':
    Message_rect.x = (int)((float)(TailleEcranLong)/100 * x); 
    Message_rect.y = (int)((float)(TailleEcranHaut)/100 * y);
    Message_rect.w = (int)((float)(TailleEcranLong)/400 * size * n);
    Message_rect.h = (int)((float)(TailleEcranHaut)/100 * size);
    break;
  case 'e':
    Message_rect.x = (int)((float)(TailleEcranLong)/100 * x - (float)(TailleEcranLong)/400 * size * n); 
    Message_rect.y = (int)((float)(TailleEcranHaut)/100 * y);
    Message_rect.w = (int)((float)(TailleEcranLong)/400 * size * n);
    Message_rect.h = (int)((float)(TailleEcranHaut)/100 * size);
    break;
    case 'c':
      Message_rect.x = (int)((float)(TailleEcranLong)/100 * x - ((float)(TailleEcranLong)/400 * size * n)/2); 
    Message_rect.y = (int)((float)(TailleEcranHaut)/100 * y - ((float)(TailleEcranHaut)/100 * size)/2);
    Message_rect.w = (int)((float)(TailleEcranLong)/400 * size * n);
    Message_rect.h = (int)((float)(TailleEcranHaut)/100 * size);
    break;
  default:
    Message_rect.x = (int)((float)(TailleEcranLong)/100 * x); 
    Message_rect.y = (int)((float)(TailleEcranHaut)/100 * y);
    Message_rect.w = (int)((float)(TailleEcranLong)/400 * size * n);
    Message_rect.h = (int)((float)(TailleEcranHaut)/100 * size);
    break;
  }

  SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);


  
}
int nombreOpen = 0;
int LastOpen = 0;

void DrawMenu(){

  SDL_Texture *Text;
  int posMX;
  int posMY;
  SDL_GetMouseState(&posMX, &posMY);

  SDL_Rect Rect;
  Rect.x = 0;
  Rect.y = 0;
  Rect.h = TailleEcranHaut;
  Rect.w = TailleEcranLong;
  
  Text = SDL_CreateTextureFromSurface(renderer, background_image);
  SDL_RenderCopy(renderer, Text, NULL, &Rect);
  SDL_DestroyTexture(Text);


  Rect.x = TailleEcranHaut/6;
  Rect.y = TailleEcranLong/13;
  Rect.h = TailleEcranHaut/2;
  Rect.w = TailleEcranLong/4;
  int isSouris = (posMX > TailleEcranLong/8 && posMX < TailleEcranLong/8 + TailleEcranLong/6 && posMY > TailleEcranHaut/6 && posMY < TailleEcranHaut/6 + TailleEcranHaut/2)?1:0;

  if(LastOpen != isSouris){
    LastOpen = isSouris;
    nombreOpen++;
  }
  if(nombreOpen < 200){
  Text = SDL_CreateTextureFromSurface(renderer, sprite_image_Fusee[isSouris]);
  }else {
  Text = SDL_CreateTextureFromSurface(renderer, sprite_image_Fusee[2]);  
  }
  SDL_RenderCopy(renderer, Text, NULL, &Rect);
  SDL_DestroyTexture(Text);

  DrawString("Play", 22, 68, 8, 'c', 255*isSouris, 255*isSouris, 255*isSouris);

  

  
  //TODO
  
}




void ClickOnMenu(){
  int posMX;
  int posMY;
while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_KEYUP:
	switch(event.key.keysym.sym){
	case SDLK_ESCAPE:EtapeActuelleDuJeu = 0;break;
	default:break;
	}
	break;
      case SDL_MOUSEWHEEL:
        // if (event.wheel.y > 0) {
	// } else if (event.wheel.y < 0) {
	// }
        break;
      case SDL_MOUSEBUTTONDOWN:
         if (event.button.button == SDL_BUTTON_LEFT) {
	   SDL_GetMouseState(&posMX, &posMY);
	   if((posMX > TailleEcranLong/8 && posMX < TailleEcranLong/8 + TailleEcranLong/6 && posMY > TailleEcranHaut/6 && posMY < TailleEcranHaut/6 + TailleEcranHaut/2)){
	       NiveauActuelle = AleaCreaTion(time(NULL), 2);
	       initGestion();
	       EtapeActuelleDuJeu = 42;
	       }
        // } else if (event.button.button == SDL_BUTTON_RIGHT) {
	 }
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
}


void ClickOnParam(){
  while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
	case SDL_KEYUP:
	switch(event.key.keysym.sym){
	case SDLK_ESCAPE:EtapeActuelleDuJeu = 0;break;
	default:break;
	}
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
}

SDL_Joystick **joystick;
int tempo = 0;



void GetManetteInput(){

  tempo++;
  SDL_JoystickUpdate();

if ( event.type == SDL_JOYAXISMOTION )
{

  //  for (int i = 0 ; i < SDL_JoystickNumAxes(joystick[0]) ; i++ )
  //    {
      //printf("Axe %d à la valeur %d\n",i,SDL_JoystickGetAxis(joystick[0],i));
  //    }
  for(int i = 0; i < SDL_NumJoysticks(); i++){
    if(SDL_JoystickGetAxis(joystick[i],0) < -25000){
      inputsJoueurs[i][INPUT_LEFT] = 1;NiveauActuelle.player[i].direction = 0;
      inputsJoueurs[i][INPUT_RIGHT] = 0;
    }else if(SDL_JoystickGetAxis(joystick[i],0) > 25000){
      inputsJoueurs[i][INPUT_RIGHT] = 1;NiveauActuelle.player[i].direction = 1;
      inputsJoueurs[i][INPUT_LEFT] = 0;
    }else{
      inputsJoueurs[i][INPUT_LEFT] = 0;
      inputsJoueurs[i][INPUT_RIGHT] = 0;
    }
    
  }
 }

 
}



void ManetteInit(){

  

  int numJoystick = SDL_NumJoysticks();
  //printf("nb de manette :%d\n", numJoystick);

  joystick = (SDL_Joystick **)malloc(numJoystick*sizeof(SDL_Joystick*));

  
  for(int i = 0; i < numJoystick; i++){
      joystick[i] = SDL_JoystickOpen(i);
      if ( joystick[i] == NULL ){
        printf("Erreur pour ouvrir le joystick\n");
    }
    /*
    printf("Informations du joystick\n");
    printf("Nom : %s\n",SDL_JoystickName(0));
    printf("Nombre d'axes : %d\n",SDL_JoystickNumAxes(joystick[i]));
    printf("Nombre de chapeaux : %d\n",SDL_JoystickNumHats(joystick[i]));
    printf("Nombre de trackballs : %d\n",SDL_JoystickNumBalls(joystick[i]));
    printf("Nombre de boutons : %d\n",SDL_JoystickNumButtons(joystick[i]));
    */
  }

    SDL_JoystickEventState(SDL_ENABLE);
  
}

