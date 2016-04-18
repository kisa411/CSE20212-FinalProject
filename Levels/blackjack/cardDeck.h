//
//  blackjack.hpp
//  blackjack
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#ifndef carddeck_h
#define carddeck_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "texture.hpp"
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm> //for shuffle() function
#include <ctime> //for time() function
#include <cstdlib> //for srand() function

using namespace std;


class CardDeck {
    
    friend ostream &operator<<( ostream &output, CardDeck &deck ); //overload << operator so that cout << board can actually display the board - parameters: what array to use to store the output, what class to act on (goes before public or private categories)
    
public:
    CardDeck( SDL_Window*, SDL_Renderer*, int n=52 ); //constructor
    int getSize(); //returns the size of the current deck of cards
    void shuffle(); //shuffles the cards using random_shuffle algorithm of STL
    int player(); //deal function for blackjack (for player)
    int dealer(); //deal function for blackjack (for dealer)
    
private:
    deque<int> cardDeque;
    int size;
    vector<CardDeck* > cardDecks; //make a vector of CardDeck classes
    
    //SDL member variables and helper functions
    LTexture gBackgroundTexture;
    LTexture gTextTexture;
    LTexture gInputTextTexture;
    LTexture gPromptTextTexture;
    
    //the window we'll be rendering to
    SDL_Window* gWindow;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    
    SDL_Renderer* gRenderer;
    
    TTF_Font *gFont = NULL; //font to use
    
    bool loadMedia();
    
    
};



#endif
