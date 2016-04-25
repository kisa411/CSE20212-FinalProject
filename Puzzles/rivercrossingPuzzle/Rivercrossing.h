#ifndef RIVERCROSSING_H
#define RIVERCROSSING_H	

#include <iostream>
#include <cstdlib>
#include <string>
#include"../../sharedClasses/texture.h"
#include"../../sharedClasses/sdl_win_wrap.h"

using namespace std;

class Rivercrossing {

   public:
      Rivercrossing(SDL_Window*, SDL_Renderer*);
      ~Rivercrossing();
      int play();
      void pickup(char);
      void drop();
      void display();
      void displayText(int, int, string);
      string userInput();

   private: 
      int start;
      int end;
      int onboat;
      int position;
      int numtries;  //number of tries till finish or gameover
      int mousepos(int, int);
      int finished();
      void reset();

      //load pics
      bool loadMedia();

      //manage events
      void manageEvents(SDL_Event &e, bool &change, bool &changeboat, bool &end);

      //textures and clips
      LTexture gBackgroundTexture;
      LTexture gSheep;
      LTexture gWolf;
      LTexture gCabbage;
      LTexture gBoat;
      LTexture gText;
      LTexture gInputText;

      //font
      TTF_Font *gFont;

      //font color
      SDL_Color color = {0, 0, 0};

      //user input
      string userinput();

      //renderer and window
      //window we are rendering to
      SDL_Window* gWindow;
      int SCREEN_WIDTH;
      int SCREEN_HEIGHT;

      //window renderer
      SDL_Renderer* gRenderer;

};

#endif


