#include "render.h"
#define TAILLE_X 100
#define TAILLE_Y 50

extern int EtapeActuelleDuJeu; /* 0 = fin; 1 = Loading Screen... */
extern int TailleEcranLong; /* Taille de l'ecran en nombre de pixel de gauche a droite */
extern int TailleEcranHaut; /* Taille de l'ecran en nombre de pixel de haut en bas */

extern SDL_Window *window; /* Adresse de la fenêtre que l'on va créer. */
extern SDL_Renderer *renderer; /* Adresse de l'endroit du dessin de la fenetre. */

extern int DEBUG; /* 1 : affiche le debug */

TTF_Font *RobotoFont;

SDL_Surface *image = NULL;
SDL_Texture  *avatar;

SDL_Event event;



int tickCount = 0;






int BouclePrincipaleDuJeu(){

  long int LastFrame;
  long int TimeCount;
  long int NowTime;
  long int timeForNewFrame = 1000000 / FPS_TO_GET;

  //Debogage
  int fpsCount = 0;
  int LastFpsCount = 0;
  int LastTickCount = 0;

  int i;
  int j;



  create_Win();



  /************Initialisation des variables de temps**************/
  LastFrame = getTime();
  TimeCount = getTime();
  NowTime = getTime();


  /************Début de la boucle des ticks***********************/
    pthread_t threadBoucleDesTicks;
    int RetourDuThreadDesTicks = pthread_create(&threadBoucleDesTicks, NULL, BouclePrincipaleDesTicks,  NULL);
    if(RetourDuThreadDesTicks){
      return 1;
    }
    
  
  /************Début de la boucle frames**************************/
  while (EtapeActuelleDuJeu) {
    NowTime = getTime();

    /* Gestion de l'affichage écran */
    if (NowTime - LastFrame > timeForNewFrame) {

      SDL_Rect Fond;
      Fond.x = 0;
      Fond.y = 0;
      Fond.h = TailleEcranHaut;
      Fond.w = TailleEcranLong;
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &Fond);

      SDL_Rect Player1_Screen;
      Player1_Screen.x = 0;
      Player1_Screen.y = 0;
      Player1_Screen.h = TailleEcranHaut;
      Player1_Screen.w = TailleEcranLong/2;
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_RenderFillRect(renderer, &Player1_Screen);

      SDL_Rect Player2_Screen;
      Player2_Screen.x = TailleEcranLong/2;
      Player2_Screen.y = 0;
      Player2_Screen.h = TailleEcranHaut;
      Player2_Screen.w = TailleEcranLong/2;
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      SDL_RenderFillRect(renderer, &Player2_Screen);

      SDL_Rect case_screen;

      for(i=0; i<TAILLE_X_SALLE; i++){
        for(j=0; j<TAILLE_Y_SALLE; j++){
          case_screen.x = i * TailleEcranLong/(2*TAILLE_X_SALLE);
          case_screen.y = j * TailleEcranHaut*TAILLE_Y_SALLE;
          case_screen.h = TailleEcranHaut/TAILLE_Y_SALLE;
          case_screen.w = TailleEcranLong/(2*TAILLE_X_SALLE);

          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          if (i + j % 2){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          }

          SDL_RenderFillRect(renderer, &case_screen);
        }
      }

      if(DEBUG){
      char affichageFrameDebug[5];
      sprintf(affichageFrameDebug, "%d", LastFpsCount);
      DrawString(affichageFrameDebug, 0, 0, 6, 'n', 0, 0, 0);
      sprintf(affichageFrameDebug, "%d", LastTickCount);
      DrawString(affichageFrameDebug, 100, 0, 6, 'e', 0, 0, 0);
      }
      
      SDL_RenderPresent(renderer);
      SDL_RenderClear(renderer);

      LastFrame += timeForNewFrame;
      fpsCount++;
    }else{

      /* Endors le cpu pour garder de la ressource */
      NowTime = getTime();
      
      long SleepForCPU = 0;
      SleepForCPU = (long)(timeForNewFrame - (NowTime - LastFrame)) / 300;
      SDL_Delay(SleepForCPU);
    }
    

    /* Gestion du debugage */
    if (NowTime > TimeCount)
    {
      TimeCount += 1000000;
      LastFpsCount = fpsCount;
      LastTickCount = tickCount;
      //printf("%d images cette seconde et %d ticks\n", fpsCount, tickCount);
      fpsCount = 0;
      tickCount = 0;
    }
  }

  
  /* on referme proprement */
  end_sdl(1, "Normal ending");

  return 0;
}




void end_sdl(char ok, char const * msg) {
  char msg_formated[255];
  int l;

  if (!ok){
    strncpy(msg_formated, msg, 250);
    l = strlen(msg_formated);
    strcpy(msg_formated+l, " : %s\n");

    SDL_Log(msg_formated, SDL_GetError());
  }

  if(renderer != NULL){
    SDL_DestroyRenderer(renderer);
  }
  if(window != NULL){
    SDL_DestroyWindow(window);
  }
  SDL_Quit();

  if (!ok) {exit(EXIT_FAILURE);}
}


void create_Win() {
  SDL_DisplayMode screen_dimension;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    end_sdl(0, "ERROR SDL INIT");

  //récupère la taille de l'écran
  SDL_GetCurrentDisplayMode(0, &screen_dimension);
  //      printf("Taille de l'écran\n\tw : %d\n\th : %d\n", screen_dimension.w,
  //      screen_dimension.h);


  /* Création de la fenêtre, cas avec erreur */
  window = SDL_CreateWindow("THIS IS A F****** WINDOW!!!", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen_dimension.w/2,
                            screen_dimension.h/2, SDL_WINDOW_RESIZABLE);
  if (window == NULL)
    end_sdl(0, "ERROR WINDOW CREATION");

  /* Création du renderer (le truc dans la windows) */
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  if (renderer == NULL)
    end_sdl(0, "ERROR RENDERER CREATION");


  // écrire (lettre chiffre) dans le render, grace à la bibliothèque TTF
  if (TTF_Init() == -1)
  {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }

  /* Taille de écran fournit par SDL */
  SDL_GetWindowSize(window, &TailleEcranLong, &TailleEcranHaut);

  
  RobotoFont = TTF_OpenFont("Res/Roboto-Black.ttf", 50);
  
}





/*Peut etre utile :



  
  



  // créer l'image de la moitié de la taille de l'écran
  *Graph = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA8888,
                             SDL_TEXTUREACCESS_TARGET, *SX / 2, *SY / 2);


  char s[1000];
  SDL_Color Green = {0, 255, 0};
  strcpy(s, "Newtone : ");
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, s, Green); 
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_Rect Message_rect;
  Message_rect.x = SX/100; 
  Message_rect.y = (7*SY + (SY/100))/8; 
  Message_rect.w = (SX/9) * ((newt->maxDeg < 6)?newt->maxDeg+1 : 8);
  Message_rect.h = SY/25; 
  SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);




*/





void *BouclePrincipaleDesTicks(void *CeciEstUneVaribleNull){
  
  long int LastTick;
  long int timeForNewTick = 1000000 / TICK_TO_GET;
  long int NowTime;
  NowTime = getTime();
  LastTick = getTime();

  
  while(EtapeActuelleDuJeu){

    NowTime = getTime();
    
    /* Gestion des verif gameplay */
    if (NowTime - LastTick > timeForNewTick) {
      

      gestionInputs();
      
      LastTick += timeForNewTick;
      tickCount++;
    }else{

      /* Endors le cpu pour garder de la ressource */
      NowTime = getTime();
      
      long SleepForCPU = 0;
      SleepForCPU = (long)(timeForNewTick - (NowTime - LastTick)) / 300;
      SDL_Delay(SleepForCPU);
    } 
  }
  return NULL;
}


