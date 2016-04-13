//
//  alphabetPuzzle.hpp
//  alphabetPuzzle
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#ifndef alphabetPuzzle_h
#define alphabetPuzzle_h

#include <iostream>
#include "texture.h"
using namespace std;

class AlphabetPuzzle {
    
public:
    AlphabetPuzzle( SDL_Window*, SDL_Renderer* ); //default constructor
    ~AlphabetPuzzle(); //destructor
    void displayPuzzle(); //display the puzzle picture
    int playPuzzle(); //check for user input and see if input is correct
    
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
    TTF_Font *gFont; //font to use
    
    bool loadMedia();
    
};


#endif
