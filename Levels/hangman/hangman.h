//
//  hangman.hpp
//  hangman game
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#ifndef hangman_h
#define hangman_h

#include <vector>
#include <iostream>
#include "../../sharedClasses/texture.h"
using namespace std;

class Hangman {
    
public:
    Hangman( SDL_Window*, SDL_Renderer* ); //constructor
    ~Hangman();
    int playPuzzle(); //check for user input and see if input is correct - returns the amount of points that should be added to player's total
    void displayOpening(); //displays opening
    int determineEnding(); //determing the results of the game
    
private:
    int points; //depending on how many tries it took player to get right answer, points value changes
    string word;
    string display;
    vector <string> guessedLetters;
   
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
    
    bool loadMedia(); //loads media
    void completed( int tryNumber ); //determine ending depending on tryNumber
    string userInput(); //take in user input
    bool validate( string letter ); //check user input against correct answer 
    bool continueText( SDL_Event & e ); ////allows user to press 'enter' to progress through text
    
};


#endif
