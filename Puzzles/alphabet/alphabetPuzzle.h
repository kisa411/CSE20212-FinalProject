//
//  alphabetPuzzle.hpp
//  alphabetPuzzle class loads alphabet logic game
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#ifndef alphabetPuzzle_h
#define alphabetPuzzle_h

#include <iostream>
#include "../../sharedClasses/texture.h"
using namespace std;

class AlphabetPuzzle {
    
public:
    AlphabetPuzzle( SDL_Window*, SDL_Renderer* ); //default constructor
    ~AlphabetPuzzle(); //destructor
    void displayTown(); //display the town
    int playPuzzle(); //main driver function for alphabet puzzle
    int determineEnding(); //determing the results of the game
    
private:
    int points; //depending on how many tries it took player to get right answer, points value changes
    bool complete; //checks to see if user has solved puzzle or not

    //SDL member variables and helper functions
    LTexture gBackgroundTexture;
    LTexture gPuzzleTexture;
    LTexture gTextTexture;
    LTexture gMathTexture;
    LTexture gInputTextTexture;
    LTexture gPromptTextTexture;
    
    //the window we'll be rendering to
    SDL_Window* gWindow;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    
    SDL_Renderer* gRenderer;
    TTF_Font *gFont; //font to use
    
   
    bool completed( int tryNumber ); //determine ending depending on tryNumber
    bool loadMedia(); //Loads necessary media
    string userInput(); //take in user input
    bool validate( string userInput ); //check user input against correct answer 
    bool continueText( SDL_Event & e ); //allows user to press 'enter' to progress through text

    
};


#endif
