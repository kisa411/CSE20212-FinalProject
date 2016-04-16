//
//  singaporePuzzle.hpp
//  singaporePuzzle
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#ifndef singaporePuzzle_h
#define singaporePuzzle_h

#include "texture.h"
#include <iostream>

using namespace std;

class SingaporeanPuzzle {
    
public:
    SingaporeanPuzzle( SDL_Window*, SDL_Renderer* ); //default constructor
    void displayPuzzle(); //display the puzzle picture
    int playPuzzle(); //check for user input and see if input is correct - returns the amount of points that should be deducted from player's total
    
private:
    int points; //depending on how many tries it took player to get right answer, points value changes
    
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
