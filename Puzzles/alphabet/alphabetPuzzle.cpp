//
//  alphabetPuzzle.cpp
//  alphabetPuzzle
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#include "alphabetPuzzle.h"

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include "sdl_win_wrap.h"
#include "texture.h"

using namespace std;


AlphabetPuzzle::AlphabetPuzzle( SDL_Window* gWindow, SDL_Renderer* gRenderer ) : gTextTexture(gWindow, gRenderer), gBackgroundTexture(gWindow, gRenderer), gInputTextTexture(gWindow, gRenderer), gPromptTextTexture(gWindow, gRenderer) { //default constructor - member initialization syntax to initialize LTexture
    points = 0; //set initial value of points to be 0
    loadMedia();
    SDL_GetWindowSize(gWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT); //store the window dimensions
}

AlphabetPuzzle::~AlphabetPuzzle() { //free up all the allocated memory for the textures
    gBackgroundTexture.free(); 
    gTextTexture.free();
    gInputTextTexture.free();
    gPromptTextTexture.free();
}

void AlphabetPuzzle::displayPuzzle() {
    SDL_RenderClear( gRenderer );
    //SDL code for displaying (rendering) puzzle image
    gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

    int textXpos = SCREEN_WIDTH/3;
    int textYpos = (2*SCREEN_HEIGHT)/3;

    bool success =  true;
    //Open the font
    //Free global font
    /*TTF_CloseFont( gFont );
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 20 );
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        gTextTexture.setFont(gFont);
        if( !gTextTexture.loadFromRenderedTextWrapped( "Hey! I'm the gate-keeper of Math Town and in order to leave you need to solve this puzzle. You only get three tries, so good luck!\n", textColor, 350 ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        gTextTexture.render(textXpos, textYpos);

    }*/

    // Update Screen
    SDL_RenderPresent( gRenderer );

 
}

int AlphabetPuzzle::playPuzzle() { //returns the amount of points player should get
    int correct = 6;
    int tryNumber = 1;
    int i;
    
    int textXpos = SCREEN_WIDTH/3;
    int textYpos = (2*SCREEN_HEIGHT)/3;

    for ( i=1; i<=3; i++ ) {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        if( !gTextTexture.loadFromRenderedTextWrapped( "What is your answer?\n", textColor, 350 ) ) {
            printf( "Failed to render text texture!\n" );
        }

        gTextTexture.render(textXpos, textYpos);
        
        //Main loop flag
        bool quit = false;
        
        //Event handler
        SDL_Event e;

        //Enable text input
        SDL_StartTextInput();
        
        //The current input text.
        string inputText = "Answer: ";
         if( !gInputTextTexture.loadFromRenderedTextWrapped( inputText.c_str(), textColor, 350 ) ) {
            printf( "Failed to render text texture!\n" );
        }

        gInputTextTexture.render(textXpos, textYpos);

        
        //While application is running
        while( !quit ) {
            //The rerender text flag
            bool renderText = false;
            
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 ) {
                //User requests quit
                if( e.type == SDL_QUIT ) {
                    quit = true;
                }//Special key input
                else if( e.type == SDL_KEYDOWN ){
                    //Handle backspace
                    if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 ){
                        //lop off character
                        inputText.pop_back();
                        renderText = true;
                    }
                }//Special text input event
                else if( e.type == SDL_TEXTINPUT )
                {
                    //Not copy or pasting
                    if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) ){
                        //Append character
                        inputText += e.text.text;
                        renderText = true;
                    }
                }
            }
            
            //Rerender text if needed
            if( renderText ){
                //Text is not empty
                if( inputText != "" ){
                    //Render new text
                    gInputTextTexture.loadFromRenderedTextWrapped( inputText.c_str(), textColor, 350 );
                }
                //Text is empty
                else{
                    //Render space texture
                    gInputTextTexture.loadFromRenderedTextWrapped( " ", textColor, 350 );
                }
            }
            
            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            
            //Render text textures
            gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0 );
            gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, gPromptTextTexture.getHeight() );
            
            //Update screen
            SDL_RenderPresent( gRenderer );
        }
        
        
        //Disable text input
        SDL_StopTextInput();
        
        int number = stoi(inputText);
    
        if ( number == 6) { //user's answer matches the correct answer
            if( !gTextTexture.loadFromRenderedTextWrapped( "Congratulations! You got it correct!\n  ", textColor, 350 ) ) {
                printf( "Failed to render text texture!\n" );
            }
            gTextTexture.render(textXpos, textYpos);
            if ( tryNumber == 1 ) { //got the answer on the first try
                if( !gTextTexture.loadFromRenderedTextWrapped( "The gatekeeper says: You got it correct on your first try, so you can leave the town for free!\n  ", textColor, 350 ) ) {
                    printf( "Failed to render text texture!\n" );
                }
                gTextTexture.render(textXpos, textYpos);
                points+=100;
                return points;
            } else if ( tryNumber == 2 ) { //got the answer on the second try
                if( !gTextTexture.loadFromRenderedTextWrapped( "The gatekeeper says: You got it correct but on your second try, but I got hungry waiting for you to solve it so give me some of your food!\n Oh no! You are forced to share 30 points worth of ingredients from your bag.\n ", textColor, 350 ) ) {
                    printf( "Failed to render text texture!\n" );
                }
                gTextTexture.render(textXpos, textYpos);
                points+=70;
                return points;
            } else if ( tryNumber == 3 ) { //got the answer on the third try
                if( !gTextTexture.loadFromRenderedTextWrapped( "The gatekeeper says: You got it correct but on your third try, but I got hungry waiting for you to solve it so give me some of your food!\n Oh no! You are forced to share 60 points worth of ingredients from your bag.\n ", textColor, 350 ) ) {
                    printf( "Failed to render text texture!\n" );
                }
                gTextTexture.render(textXpos, textYpos);
                points+=40;
                return points;
            }
        }
    }
    
    
    SDL_Color textColor = { 0, 0, 0 };
    //if player is unable to solve the puzzle in 3 tries,
    if( !gTextTexture.loadFromRenderedTextWrapped( "The gatekeeper says: You're taking too long to come up with the correct answer! For wasting so much of my time give me something yummy!\n Oh no! The gate-keeper ate 100 points worth of ingredients from your bag! At least you finally get to exit the Math Town.\n", textColor, 350 ) ) {
        printf( "Failed to render text texture!\n" );
    }
    gTextTexture.render(textXpos, textYpos);
    
    points-=50;
    return points;

    
}


bool AlphabetPuzzle::loadMedia() {
    
    //Loading success flag
    bool success = true;
    
    //Open the background picture
    if( !gBackgroundTexture.loadFromFile( "sudoku_background.png" ))
    {
        printf( "Failed to load background texture!\n" );
        success = false;
    }
    
    //Open the font
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render the prompt
        SDL_Color textColor = { 0, 0, 0, 0xFF };
        gPromptTextTexture.setFont(gFont);
        if( !gPromptTextTexture.loadFromRenderedTextWrapped( "Your answer: ", textColor, 350 ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }
    }
    
    
    return success;
}
