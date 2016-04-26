/*
 * Created by: Borah Chong
 * This class is used to implement a graphical game of Blackjack.
 */

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include<iostream>
#include<deque>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include"CardDeck.h"
#include"../../sharedClasses/texture.h"
#include"../../sharedClasses/sdl_win_wrap.h"

using namespace std; 

// This class is used to simulate a game of Blackjack

class Blackjack {

   public:
      Blackjack(SDL_Window*, SDL_Renderer*);  //constructor
      ~Blackjack(); //deconstructor
      void deal();  //deal initial cards to dealer and user
      void display(); //display background
      void menu();  //displays menu and returns choice as int
      int play(); //plays game
      void displaycards(deque<int>);   //displays users cards
      void displaydcards(deque<int>, int);  //displays dealers cards
      void displayWTL(int, int, int);  //displays wins ties losses on screen
      void displaytext(int, int, string); //used to display text on screen
      int sum(deque<int>);    //calculates sum of cards in deck
      string convertToCard(int);   //converts number to card value

   private:
      CardDeck *currDeck;
      deque<int> player;
      deque<int> dealer;
      
      //values for number of wins, losses, and ties
      int wins, losses, ties;

      //load images
      bool loadMedia();

      //manage events
      void manageEvents(SDL_Event &e, bool &drawcard, bool &stop, bool &exit);

      //returns click choice with mouse position
      int mousepos(int, int);

      //gets user input
      string userInput();

      //textures and clips
      LTexture gBackground;
      LTexture gCardDeck;
      SDL_Rect gCards[52];

      LTexture gText;
      LTexture gInputText;
      LTexture gWins;
      LTexture gLosses;
      LTexture gTies;

      
      //font
      TTF_Font *gFont;

      //font color
      SDL_Color color;

      //renderer and window
      SDL_Window* gWindow;
      int SCREEN_WIDTH;
      int SCREEN_HEIGHT;
      SDL_Renderer* gRenderer;


};

#endif

