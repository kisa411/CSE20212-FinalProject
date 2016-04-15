#ifndef RIVERCROSSING_H
#define RIVERCROSSING_H	

#include <iostream>
#include <cstdlib>
#include"texture.h"
#include"sdl_win_wrap.h"
#include"boat.h"

using namespace std;

class Rivercrossing {

   public:
      Rivercrossing(SDL_Window*, SDL_Renderer*);
      ~Rivercrossing();
      void play();
      void currentboat();
      void pickup(char);
      void drop();
      int finished();
      void reset();
      void display();
      int mousepos(int, int);

   private: 
      int start;
      int end;
      int onboat;
      int position;
      int nummoves;  //number of moves it took to finish or gameover
      int numtries;  //number of tries till finish or gameover

      //load pics
      bool loadMedia();

      //manage events
      void manageEvents(SDL_Event &e, bool &change, bool &changeboat);

      //textures and clips
      LTexture gBackgroundTexture;
      LTexture gSheep;
      LTexture gWolf;
      LTexture gCabbage;
      LTexture gBoat;

      //renderer and window
      //window we are rendering to
      SDL_Window* gWindow;
      int SCREEN_WIDTH;
      int SCREEN_HEIGHT;

      //window renderer
      SDL_Renderer* gRenderer;

};

#endif


