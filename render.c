#include "render.h"
#include "Terrain.h"
#include <SDL2/SDL_render.h>
#define TAILLE_X 21
#define TAILLE_Y 18

extern int EtapeActuelleDuJeu; /* 0 = fin; 1 = Loading Screen... */
extern int TailleEcranLong; /* Taille de l'ecran en nombre de pixel de gauche a droite */
extern int TailleEcranHaut; /* Taille de l'ecran en nombre de pixel de haut en bas */

extern SDL_Window *window; /* Adresse de la fenêtre que l'on va créer. */
extern SDL_Renderer *renderer; /* Adresse de l'endroit du dessin de la fenetre. */

extern int DEBUG; /* 1 : affiche le debug */

TTF_Font *RobotoFont;

SDL_Surface *image = NULL;
SDL_Texture  *avatar;

SDL_Surface *background_image = NULL;
SDL_Texture *background_avatar;

SDL_Surface *sprite_image = NULL;

SDL_Surface *sprite_image_orange[9];

SDL_Surface *sprite_image_Star[3];
SDL_Surface *sprite_image_Fusee[2];


SDL_Texture *sprite_avatar;

SDL_Event event;


int tickCount = 0;

niveau NiveauActuelle;

int cycle_animation = 0;


int BouclePrincipaleDuJeu(){

  long int LastFrame;
  long int TimeCount;
  long int NowTime;
  long int timeForNewFrame = 1000000 / FPS_TO_GET;

  //Debogage
  int fpsCount = 0;
  int LastFpsCount = 0;
  int LastTickCount = 0;



  create_Win();

  image=IMG_Load("roche.png");
  if(!image) {
    printf("IMG_Load: %s\n", IMG_GetError());
  }
  background_image = IMG_Load("Res/background/sky.png");
  
  sprite_image_orange[0] = IMG_Load("Res/player/orange/player_walk0.png");
  sprite_image_orange[1] = IMG_Load("Res/player/orange/player_walk1.png");
  sprite_image_orange[2] = IMG_Load("Res/player/orange/player_walk2.png");
  sprite_image_orange[3] = IMG_Load("Res/player/orange/player_walk3.png");

  sprite_image_orange[4] = IMG_Load("Res/player/orange/player_base0.png");
  sprite_image_orange[5] = IMG_Load("Res/player/orange/player_base1.png");

  sprite_image_orange[6] = IMG_Load("Res/player/orange/player_face.png");

  sprite_image_orange[7] = IMG_Load("Res/player/orange/player_fall.png");
  sprite_image_orange[8] = IMG_Load("Res/player/orange/player_jump.png");



  sprite_image_Star[0] = IMG_Load("Res/background/star/star0.png");
  sprite_image_Star[1] = IMG_Load("Res/background/star/star1.png");
  sprite_image_Star[2] = IMG_Load("Res/background/star/star2.png");

  sprite_image_Fusee[0] = IMG_Load("Res/background/rocket/open.png");
  sprite_image_Fusee[1] = IMG_Load("Res/background/rocket/close.png");
  
  /************Initialisation des variables de temps**************/
  LastFrame = getTime();
  TimeCount = getTime();
  NowTime = getTime();

  NiveauActuelle = AleaCreaTion(42, 2);

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

      switch(EtapeActuelleDuJeu){
      case 2:DrawMenu();break;
      case 42:DessinPrincipale();break;
      default:return 0;break;
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
				      
      // Endors le cpu pour garder de la ressource 
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
  initGestion();

  
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

void DessinPrincipale(){

  int i;
  int j;
  int joueur_id;

  SDL_Rect Joueur;

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
      background_avatar = SDL_CreateTextureFromSurface(renderer, background_image);
      SDL_RenderCopy(renderer, background_avatar, NULL, &Player1_Screen);
      SDL_Rect Player2_Screen;
      Player2_Screen.x = TailleEcranLong/2;
      Player2_Screen.y = 0;
      Player2_Screen.h = TailleEcranHaut;
      Player2_Screen.w = TailleEcranLong/2;
      SDL_RenderCopy(renderer, background_avatar, NULL, &Player2_Screen);

      SDL_DestroyTexture(background_avatar);
      
      SDL_Rect case_screen;
      case_screen.x = - (int)((TailleEcranLong/(2*TAILLE_X)+((float)NiveauActuelle.player[0].x - (int)NiveauActuelle.player[0].x )*TailleEcranLong/(2*TAILLE_X)));
      case_screen.y = - TailleEcranHaut/TAILLE_Y + ((float)NiveauActuelle.player[0].y - (int)NiveauActuelle.player[0].y )*TailleEcranHaut/(TAILLE_Y);
      case_screen.w = TailleEcranLong/(2*TAILLE_X);
      case_screen.h = TailleEcranHaut/TAILLE_Y;
      
      for(i=(int)(NiveauActuelle.player[0].x) -11; i< (int)NiveauActuelle.player[0].x + TAILLE_X - 10; i++){

        case_screen.x = case_screen.x + case_screen.w;
        case_screen.y = - TailleEcranHaut/TAILLE_Y;
        for(j=(int)NiveauActuelle.player[0].y - 4; j<TAILLE_Y +1 + (int)NiveauActuelle.player[0].y - 4; j++){

          case_screen.y = case_screen.y + case_screen.h;

          if (j >= 0 && i >= 0 && NiveauActuelle.salle[0].terrain[i][j]){
            avatar = SDL_CreateTextureFromSurface(renderer, image);
            SDL_RenderCopy(renderer, avatar, NULL, &case_screen);
	          SDL_DestroyTexture(avatar);
          }
        }
      }
       
      int angle = 0;
      SDL_RendererFlip flip;



      

      for (joueur_id = 0; joueur_id <2; joueur_id++){
        flip = SDL_FLIP_NONE;

        if(joueur_id == 0){
          Joueur.h = NiveauActuelle.player[joueur_id].sizeY *  TailleEcranHaut/TAILLE_Y;
          Joueur.w = NiveauActuelle.player[joueur_id].sizeX * TailleEcranLong/(2*TAILLE_X);
          Joueur.x = (float)TailleEcranLong/4;
          Joueur.y = (float)TailleEcranHaut/4;
        }
        else {
          Joueur.h = NiveauActuelle.player[joueur_id].sizeY *  TailleEcranHaut/TAILLE_Y;
          Joueur.w = NiveauActuelle.player[joueur_id].sizeX * TailleEcranLong/(2*TAILLE_X);
          Joueur.x = TailleEcranLong/(2) +NiveauActuelle.player[joueur_id].x * TailleEcranLong/(2*TAILLE_X);
          Joueur.y = NiveauActuelle.player[joueur_id].y *  TailleEcranHaut/TAILLE_Y;
        }

        if (NiveauActuelle.player[joueur_id].ySpeed == 0){

          if (NiveauActuelle.player[joueur_id].xSpeed == 0){
            sprite_image = sprite_image_orange[4 + (SDL_GetTicks()/500)%2];
            if (NiveauActuelle.player[joueur_id].direction == 0){
              flip = SDL_FLIP_HORIZONTAL;
            }
          }
          
          if (NiveauActuelle.player[joueur_id].xSpeed > 0){
          sprite_image = sprite_image_orange[(SDL_GetTicks()/110)%4];
          }
          
          if (NiveauActuelle.player[joueur_id].xSpeed < 0){
          sprite_image = sprite_image_orange[(SDL_GetTicks()/110)%4];
          flip = SDL_FLIP_HORIZONTAL;
          }
      }

      else if(NiveauActuelle.player[joueur_id].ySpeed > 0){
        sprite_image = sprite_image_orange[7];
      }
      
      else if (NiveauActuelle.player[joueur_id].ySpeed < 0) {
        sprite_image = sprite_image_orange[8];
      }
    

      sprite_avatar = SDL_CreateTextureFromSurface(renderer, sprite_image);
      //SDL_RenderCopy(renderer, sprite_avatar, NULL, &Joueur);
      SDL_RenderCopyEx(renderer, sprite_avatar, NULL, &Joueur, angle, NULL, flip);
      SDL_DestroyTexture(sprite_avatar);
      }

  
}



