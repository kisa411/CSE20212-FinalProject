//
//  singaporePuzzle.hpp
//  singaporePuzzle loads singaporean logic game
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#ifndef singaporePuzzle_h
#define singaporePuzzle_h

#include "../../sharedClasses/texture.h"
#include <iostream>

using namespace std;

class SingaporeanPuzzle {
    
public:
    SingaporeanPuzzle( SDL_Window*, SDL_Renderer* ); //constructor
    ~SingaporeanPuzzle(); //destructor
    void displayRobber(); //display the puzzle picture
    int playPuzzle(); //check for user input and see if input is correct - returns the amount of points that should be deducted from player's total
    int determineEnding(); //determing the results of the game
    
private:
    int points; //depending on how many tries it took player to get right answer, points value changes
    bool complete; //checks to see if user has solved puzzle or not
    
    //SDL member variables and helper functions
    LTexture gBackgroundTexture;
    LTexture gTextTexture;
    LTexture gInputTextTexture;
    LTexture gPromptTextTexture;
    LTexture gPuzzleTexture;
    
    //the window we'll be rendering to
    SDL_Window* gWindow;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    
    SDL_Renderer* gRenderer;
    
    TTF_Font *gFont; //font to use
    
    bool loadMedia(); //loads media
    bool completed( int tryNumber ); //determine ending depending on tryNumber
    string userInput(); //take in user input
    bool validate( string userInput ); //check user input against correct answer 
    bool continueText( SDL_Event & e ); //continues text

    
    
};


#endif 
