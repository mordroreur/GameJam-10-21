#include "RenderUtilities.h"

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
  Text = SDL_CreateTextureFromSurface(renderer, sprite_image_Fusee[isSouris]);
  SDL_RenderCopy(renderer, Text, NULL, &Rect);
  SDL_DestroyTexture(Text);

  DrawString("Play", 25, 75, 8, 'c', 255*isSouris, 255*isSouris, 255*isSouris);
  

  
}

