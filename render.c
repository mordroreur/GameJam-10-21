#include "render.h"
#include "RenderUtilities.h"
#include "Terrain.h"
#include "listeEntite.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#define TAILLE_X 22
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

SDL_Surface *separation_image = NULL;
SDL_Texture *separation_avatar;

SDL_Surface *background_image = NULL;
SDL_Texture *background_avatar;

SDL_Surface *sprite_image = NULL;

SDL_Surface *semisolid_image = NULL;

SDL_Surface *sprite_image_Player[2][9];



SDL_Surface *sprite_image_Star[3];
SDL_Surface *sprite_image_Fusee[2];
SDL_Surface *sprite_image_PowerUp[4];

SDL_Surface *sprite_image_Starshit;

SDL_Texture *sprite_avatar;

SDL_Event event;

int ToucheAppuiPlayer[2][4];

int tickCount = 0;

niveau NiveauActuelle;



int cycle_animation = 0;

SDL_AudioSpec *wavSpec;
Uint32 *wavLength;
Uint8 **wavBuffer;


int BouclePrincipaleDuJeu(){

  long int LastFrame;
  long int TimeCount;
  long int NowTime;
  long int timeForNewFrame = 1000000 / FPS_TO_GET;

  //Debogage
  int fpsCount = 0;
  int LastFpsCount = 0;
  int LastTickCount = 0;

  ToucheAppuiPlayer[0][0] = SDLK_z;
  ToucheAppuiPlayer[0][1] = SDLK_q;
  ToucheAppuiPlayer[0][2] = SDLK_d;
  ToucheAppuiPlayer[0][3] = SDLK_s;

  ToucheAppuiPlayer[1][0] = SDLK_UP;
  ToucheAppuiPlayer[1][1] = SDLK_LEFT;
  ToucheAppuiPlayer[1][2] = SDLK_RIGHT;
  ToucheAppuiPlayer[1][3] = SDLK_DOWN;

  create_Win();

  image=IMG_Load("roche.png");
  if(!image) {
    printf("IMG_Load: %s\n", IMG_GetError());
  }
  background_image = IMG_Load("Res/background/sky.png");

  semisolid_image = IMG_Load("Res/semisolid.png");

  separation_image = IMG_Load("Res/split.png");

  sprite_image_Starshit = IMG_Load("Res/background/star/starsheet.png");

  sprite_image_PowerUp[0] = IMG_Load("Res/powerup/jetpack.png");
  sprite_image_PowerUp[1] = IMG_Load("Res/powerup/cristal_anti_gravite.png");
  sprite_image_PowerUp[2] = IMG_Load("Res/powerup/richesse.png");
  sprite_image_PowerUp[3] = IMG_Load("Res/powerup/rock.png");
  
  sprite_image_Player[0][0] = IMG_Load("Res/player/orange/player_walk0.png");
  sprite_image_Player[0][1] = IMG_Load("Res/player/orange/player_walk1.png");
  sprite_image_Player[0][2] = IMG_Load("Res/player/orange/player_walk2.png");
  sprite_image_Player[0][3] = IMG_Load("Res/player/orange/player_walk3.png");

  sprite_image_Player[0][4] = IMG_Load("Res/player/orange/player_base0.png");
  sprite_image_Player[0][5] = IMG_Load("Res/player/orange/player_base1.png");

  sprite_image_Player[0][6] = IMG_Load("Res/player/orange/player_face.png");

  sprite_image_Player[0][7] = IMG_Load("Res/player/orange/player_fall.png");
  sprite_image_Player[0][8] = IMG_Load("Res/player/orange/player_jump.png");

  sprite_image_Player[1][0] = IMG_Load("Res/player/vert/player_walk0.png");
  sprite_image_Player[1][1] = IMG_Load("Res/player/vert/player_walk1.png");
  sprite_image_Player[1][2] = IMG_Load("Res/player/vert/player_walk2.png");
  sprite_image_Player[1][3] = IMG_Load("Res/player/vert/player_walk3.png");

  sprite_image_Player[1][4] = IMG_Load("Res/player/vert/player_base0.png");
  sprite_image_Player[1][5] = IMG_Load("Res/player/vert/player_base1.png");

  sprite_image_Player[1][6] = IMG_Load("Res/player/vert/player_face.png");

  sprite_image_Player[1][7] = IMG_Load("Res/player/vert/player_fall.png");
  sprite_image_Player[1][8] = IMG_Load("Res/player/vert/player_jump.png");



  sprite_image_Star[0] = IMG_Load("Res/background/star/star0.png");
  sprite_image_Star[1] = IMG_Load("Res/background/star/star1.png");
  sprite_image_Star[2] = IMG_Load("Res/background/star/star2.png");

  sprite_image_Fusee[0] = IMG_Load("Res/background/rocket/open.png");
  sprite_image_Fusee[1] = IMG_Load("Res/background/rocket/close.png");
  
  /************Initialisation des variables de temps**************/
  LastFrame = getTime();
  TimeCount = getTime();
  NowTime = getTime();


  ManetteInit();

  wavSpec = (SDL_AudioSpec*)malloc(sizeof(SDL_AudioSpec)*1);
   wavLength = (Uint32 *)malloc(sizeof(Uint32)*1);
   wavBuffer = (Uint8 **)malloc(sizeof(Uint8*)*1);

 
  SDL_LoadWAV("Res/Sound/AMOGUS.wav", &wavSpec[0], &wavBuffer[0], &wavLength[0]);

  SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec[0], NULL, 0);
  SDL_QueueAudio(deviceId, wavBuffer[0], wavLength[0]);
  SDL_PauseAudioDevice(deviceId, 0);

  SDL_Delay(500);

  deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec[0], NULL, 0);
  SDL_QueueAudio(deviceId, wavBuffer[0], wavLength[0]);
  SDL_PauseAudioDevice(deviceId, 0);
 
  //SDL_CloseAudioDevice(deviceId);
  //SDL_FreeWAV(wavBuffer);
 
  
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
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) != 0)
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

//TailleEcranLong TailleEcranHaut 
// cam: TAILLE_X TAILLE_Y

float camX;
float camY;
int camWindowsPxOffsetX;
int camWindowsPxOffsetY;

void DrawOnScreen(float x, float y, float sizeX, float sizeY, float camX, float camY, int screenXoffset, int screenYoffset, 
SDL_Surface *sprite, SDL_RendererFlip *flip) 
{

    SDL_Rect r;
    r.x = 
    r.y = - (int)(TailleEcranHaut/TAILLE_Y + ((float)NiveauActuelle.player[0].y - (int)NiveauActuelle.player[0].y - 1)*TailleEcranHaut/(TAILLE_Y));
    r.w = TailleEcranLong/(2*TAILLE_X);
    r.h = TailleEcranHaut/TAILLE_Y;

    avatar = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, avatar, NULL, &r);
    SDL_DestroyTexture(avatar);


}



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
      
      switch(EtapeActuelleDuJeu){
      case 42 : gestionInputs();break;
      case 2 : ClickOnMenu();break;
      case 4 : ClickOnParam();break;
      default:printf("Cette etape du jeu n'existe pas...\n");break;
      }

      
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


  

  if (fabs(NiveauActuelle.player[1].x - NiveauActuelle.player[0].x) > TAILLE_X || fabs(NiveauActuelle.player[1].y - NiveauActuelle.player[0].y) > TAILLE_Y/1.3){

   
    DrawCamera(NiveauActuelle.player[0].x, NiveauActuelle.player[0].y, 16, TailleEcranLong/2*0.96, TailleEcranHaut, 0, 0);
    DrawCamera(NiveauActuelle.player[1].x, NiveauActuelle.player[1].y, 16,TailleEcranLong/2, TailleEcranHaut, TailleEcranLong/2*1.04, 0);
    
    SDL_Rect separation;
    separation.h= TailleEcranHaut;
    separation.w= TailleEcranLong /29;
    separation.x= TailleEcranLong/2 - separation.w/2;
    separation.y = 0;
    
    separation_avatar = SDL_CreateTextureFromSurface(renderer, separation_image);
    SDL_SetRenderDrawColor(renderer, 22, 38, 114, 255);
    SDL_RenderFillRect(renderer, &separation);
    separation.h= TailleEcranHaut;
    separation.w= TailleEcranLong /7;
    separation.x= TailleEcranLong/2 - separation.w/2;
    separation.y = 0;
    SDL_RenderCopy(renderer, separation_avatar, NULL, &separation);
    SDL_DestroyTexture(separation_avatar);
  }else{
    DrawCamera((NiveauActuelle.player[0].x + NiveauActuelle.player[1].x)/2, (NiveauActuelle.player[0].y + NiveauActuelle.player[1].y)/2, 16, TailleEcranLong, TailleEcranHaut, 0, 0);
  }
  
  SDL_Rect PowerUp;
  if(NiveauActuelle.player[0].heldPowerup != -1){
    PowerUp.y= 0;
    PowerUp.x= 0;
    PowerUp.h= TailleEcranLong/10 ;
    PowerUp.w = TailleEcranLong/10;
    SDL_Texture *avatarTmp = SDL_CreateTextureFromSurface(renderer, sprite_image_PowerUp[NiveauActuelle.player[0].heldPowerup]);
    SDL_RenderCopy(renderer, avatarTmp, NULL, &PowerUp);
    SDL_DestroyTexture(avatarTmp);
  }

  if(NiveauActuelle.player[1].heldPowerup != -1){
    PowerUp.y= 0;
    PowerUp.x=  TailleEcranLong- (TailleEcranLong /10);
    PowerUp.h= TailleEcranLong/10 ;
    PowerUp.w = TailleEcranLong/10;
    SDL_Texture *avatarTmp = SDL_CreateTextureFromSurface(renderer, sprite_image_PowerUp[NiveauActuelle.player[1].heldPowerup]);
    SDL_RenderCopy(renderer, avatarTmp, NULL, &PowerUp);
    SDL_DestroyTexture(avatarTmp);
  }
}
          

  
float CamX = 0;
float CamY  = 0;
float CamNbBlockX  = 1;
float CamNbBlockY  = 1;
int CamPixelX  = 960;
int CamPixelY  = 540;
int CamPixelOffsetX  = 0;
int CamPixelOffsetY  = 0;

void DrawCamera(
  float camX, float camY, float nbBlockY,
  int camPixelX, int camPixelY,
  int camPixelOffsetX, int camPixelOffsetY)
{
  CamX = camX;
  CamY = camY;
  CamNbBlockY = nbBlockY;
  CamNbBlockX = CamPixelX/(float)CamPixelY*CamNbBlockY;
  CamPixelX = camPixelX;
  CamPixelY = camPixelY;
  CamPixelOffsetX = camPixelOffsetX;
  CamPixelOffsetY = camPixelOffsetY;
  CamX -= CamNbBlockX/2;
  CamY -= CamNbBlockY/2;

   SDL_Rect Player2_Screen;
   Player2_Screen.x = CamPixelOffsetX;
   Player2_Screen.y = CamPixelOffsetY;
   Player2_Screen.h = CamPixelY;
   Player2_Screen.w = CamPixelX;
   background_avatar = SDL_CreateTextureFromSurface(renderer, background_image);
   SDL_RenderCopy(renderer, background_avatar, NULL, &Player2_Screen);
   SDL_DestroyTexture(background_avatar);

  
  int blockMore = 1;


  for(int x = -blockMore+1+CamX; x < (int)(CamX+CamNbBlockX) + blockMore; x++)
  {
    for(int y = -blockMore+1+CamY; y < (int)(CamY+CamNbBlockY) + blockMore; y++)
    {
      DrawBlockAt(x,y);
    } 
  }

  int salle = (-blockMore+1+CamX)/100;
  int nbEntite = ListLenght(NiveauActuelle.salle[salle].lE);
  Maillon *m =NiveauActuelle.salle[salle].lE.first;
  for(int i = 0; i < nbEntite; i++){
    DrawSprite(m->val.x, m->val.y, m->val.sizeX, m->val.sizeX, sprite_image_PowerUp[m->val.type], SDL_FLIP_NONE, NULL);
    m = m->suiv;
  }
  
  for(int i = 0;i < NiveauActuelle.nbPlayer; i++)
  {
    entite* p = &(NiveauActuelle.player[i]);

    if(p->ySpeed == 0){
      if (p->xSpeed == 0){
	sprite_image = sprite_image_Player[i][4 + (SDL_GetTicks()/500)%2];
      }else{
	sprite_image = sprite_image_Player[i][(SDL_GetTicks()/110)%4];
      }
    } else if(p->ySpeed < 0){
      sprite_image = sprite_image_Player[i][8];
    } else if(p->ySpeed > 0){
      sprite_image = sprite_image_Player[i][7];
    }

    DrawSprite(p->x, p->y, p->sizeX, p->sizeY, sprite_image, (p->direction)?SDL_FLIP_NONE:SDL_FLIP_HORIZONTAL, NULL);
  }

  


  
}

void DrawBlockAt(int x, int y)
{
  int id = getBlockId(x,y);
  SDL_Rect r;
  switch(id)
  {
    case 1:
      DrawBlock(x,y, image, NULL);break;
  case 2:
    DrawBlock(x,y, semisolid_image, NULL);
    break;
  case 3:
    r.x = 16*((SDL_GetTicks()/(120 + (x*3+y*7)%40) + x*3+y*7)%4);
    r.y = 0;
    r.w = 16;
    r.h = 16;
    DrawBlock(x, y, sprite_image_Starshit, &r);
    break;
    case 0:
    default: break;
  } 

}

void DrawBlock(int x, int y, SDL_Surface* sprite, SDL_Rect* source)
{
  DrawSprite(x,y, 1,1, sprite, SDL_FLIP_NONE, source);
}

void DrawSprite(float x, float y, 
    float sizeX, float sizeY,
    SDL_Surface* sprite, int flip, SDL_Rect* source)
{
  //Todo calculer rect destination
    SDL_Rect r;
    r.x = CamPixelOffsetX+(x-CamX)/CamNbBlockX*CamPixelX;
    r.y = CamPixelOffsetY+(y-CamY)/CamNbBlockY*CamPixelY;
    r.w = sizeX/CamNbBlockX*CamPixelX;
    r.h = sizeY/CamNbBlockY*CamPixelY;

    if(x+sizeX < CamX || x > CamX+CamNbBlockX)
    { return; } 

    SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, sprite);
    SDL_RenderCopyEx(renderer, temp, source, &r, 0, NULL, flip);
    SDL_DestroyTexture(temp);
}


