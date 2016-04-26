/*
 * Created by: Borah Chong
 * This class is meant to implement a graphical game of the river crossing puzzle
 */

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
      Rivercrossing(SDL_Window*, SDL_Renderer*); //constructor
      ~Rivercrossing(); //deconstructor
      int play();  //play main game
      void pickup(char); //pick up an object
      void drop();  //drop and object
      void display();  //display images and background
      void displayText(int, int, string); //used to display text onto screen
      string userInput(); //takes in user input

   private: 
      int start;
      int end;
      int onboat;
      int position;
      int numtries;  //number of tries till finish or gameover
      int mousepos(int, int); //takes in mouse position as inputs and returns a number indicating where the user clicked
      int finished(); //checks if game is successfully completed
      void reset();  //resets game if user loses and wants to try again

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


