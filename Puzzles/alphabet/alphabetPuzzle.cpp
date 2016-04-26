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
#include "../../sharedClasses/sdl_win_wrap.h"
#include "../../sharedClasses/texture.h"

using namespace std;


AlphabetPuzzle::AlphabetPuzzle( SDL_Window* ngWindow, SDL_Renderer* ngRenderer ) : gTextTexture(ngWindow, ngRenderer), gBackgroundTexture(ngWindow, ngRenderer), gPuzzleTexture(ngWindow, ngRenderer), gInputTextTexture(ngWindow, ngRenderer), gPromptTextTexture(ngWindow, ngRenderer), gMathTexture(ngWindow, ngRenderer), gWindow(ngWindow), gRenderer(ngRenderer) { //default constructor - member initialization syntax to initialize LTexture
    points = 0; //set initial value of points to be 0
    complete = false;
    // questionAnswered = false;
    loadMedia();
    SDL_GetWindowSize(gWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT); //store the window dimensions
}

AlphabetPuzzle::~AlphabetPuzzle() { //free up all the allocated memory for the textures
    gBackgroundTexture.free();
    gMathTexture.free(); 
    gTextTexture.free();
    gInputTextTexture.free();
    gPromptTextTexture.free();
}


bool AlphabetPuzzle::continueText(SDL_Event & e) {
    bool quit = false;
    bool enter = false;

    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
        else if ( e.type == SDL_KEYDOWN ) {
            //User presses a key
            if( e.key.keysym.sym == SDLK_RETURN )
            {
                enter = true;
            }
        }
    }

    return enter;
}

void AlphabetPuzzle::displayTown() {
    
    int textXpos = SCREEN_WIDTH/5;
    int textYpos = (8*SCREEN_HEIGHT)/11;

    bool success = true;
    bool next = false;

    SDL_Event e;

    //Open the font
    //Free global font
    TTF_CloseFont( gFont );
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 16 );
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        gMathTexture.setFont(gFont);
        if( !gMathTexture.loadFromRenderedTextWrapped( "Hey! I'm the gate-keeper of Math Town and in order to leave you need to solve this puzzle. The exit tax amount will depend on how long it takes you to solve it! You only get three tries, so good luck!\n", textColor, 400 ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }

    }

    SDL_RenderClear( gRenderer );
    while (!next) {
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gMathTexture.render( textXpos, textYpos );
        //Update screen
        SDL_RenderPresent( gRenderer );
        next=continueText(e);
    }
    next = false;
 
}


int AlphabetPuzzle::playPuzzle() {

    int endPoints = 100;

 
    while (complete==false) {
        // displayPuzzle();
        endPoints = determineEnding(); //display the main background
        if ( endPoints <= 0 ) {
            complete = true;
        }
        // displayPuzzle();
    }

    return endPoints;


}

int AlphabetPuzzle::determineEnding() {
    string answer;
    SDL_Event e;
    bool correct = false;
    int tryNumber=0;
    int textXpos = (2*SCREEN_WIDTH)/9;
    int textYpos = (3*SCREEN_HEIGHT)/4;

    //Loading success flag
    bool success = true;
    bool next = false;

    SDL_Color textColor = { 0, 0, 0 };

    TTF_CloseFont( gFont );
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 16 );
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    gTextTexture.setFont(gFont);

    while (correct==false) {
        // displayPuzzle();
        tryNumber++;
        // cout << "Question Answered? " << questionAnswered << endl;

        answer = userInput(); //returns user's input
        correct = validate(answer); //returns whether or not the input is right
        if (correct==true) {
            // questionAnswered=true;
            if( !gTextTexture.loadFromRenderedTextWrapped( "Congratulations! You got it correct!\n  ", textColor, 350 ) ) {
                printf( "Failed to render text texture!\n" );
            }
            SDL_RenderClear( gRenderer );

            while (!next) {
                gPuzzleTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
                gTextTexture.render( textXpos, textYpos );
                //Update screen
                SDL_RenderPresent( gRenderer );
                next=continueText(e);
            }
            next = false;
            if ( tryNumber == 1 ) { //got the answer on the first try
                completed( tryNumber );
                return points;
            } else if ( tryNumber == 2 ) { //got the answer on the second try
                completed( tryNumber );
                points-=30;
                return points;
            } else if ( tryNumber == 3 ) { //got the answer on the third try
                completed( tryNumber );
                points-=60;
                return points;
            } else { //if player is unable to solve the puzzle in 3 tries
                completed( tryNumber );
                points-=100;
                return points;
            }

        } else {
            if( !gTextTexture.loadFromRenderedTextWrapped( "That's wrong, Try again.\n  ", textColor, 350 ) ) {
                printf( "Failed to render text texture!\n" );
            }
            // questionAnswered=false;
            SDL_RenderClear( gRenderer );
            while (!next) {
                gPuzzleTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
                gTextTexture.render( textXpos, textYpos );
                //Update screen
                SDL_RenderPresent( gRenderer );
                next=continueText(e);
            }
            next = false;
        }

    }
}

bool AlphabetPuzzle::completed( int tryNumber ) {

    //Loading success flag
    bool success = true;
    bool next = false;
    SDL_Event e;

    int textXpos = (1*SCREEN_WIDTH)/7;
    int textYpos = (8*SCREEN_HEIGHT)/11;

    SDL_Color textColor = { 0, 0, 0, 0xFF };
    gTextTexture.setFont(gFont);

    if (tryNumber==1) { //load text for first try
        if( !gTextTexture.loadFromRenderedTextWrapped( "The gatekeeper says: You got it correct on your first try, so you can leave the town for free!\n  ", textColor, 450 ) ) {
            printf( "Failed to render text texture!\n" );
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gPuzzleTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;
        complete = true;
    } else if (tryNumber==2) { //load text for second try
        if( !gTextTexture.loadFromRenderedTextWrapped( "The gatekeeper says: You got it correct but on your second try, and I got hungry waiting so give me some of your food!\n Oh no! You are forced to share 30 points worth of ingredients from your bag.\n ", textColor, 450 ) ) {
            printf( "Failed to render text texture!\n" );
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gPuzzleTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;
        complete = true;
        return complete;
    } else if (tryNumber==3) { //load text for third try
        if( !gTextTexture.loadFromRenderedTextWrapped( "The gatekeeper says: You got it correct but on your third try, and I got hungry waiting so give me some of your food!\n Oh no! You are forced to share 60 points worth of ingredients from your bag.\n ", textColor, 450 ) ) {
            printf( "Failed to render text texture!\n" );
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gPuzzleTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;
        complete = true;
        return complete;
    } else { //load text for failed attempt
        if( !gTextTexture.loadFromRenderedTextWrapped( "The gatekeeper says: You got it right but it took you too long!\n", textColor, 450 ) ) {
            printf( "Failed to render text texture!\n" );
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gPuzzleTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;
        if( !gTextTexture.loadFromRenderedTextWrapped( "The gate-keeper ate 100 points worth of ingredients from your bag! At least you finally get to exit the Math Town.\n", textColor, 450 ) ) {
            printf( "Failed to render text texture!\n" );
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gPuzzleTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;
        complete = true;
        return complete;
    }

    return complete;
}


string AlphabetPuzzle::userInput() {

    int textXpos = (2*SCREEN_WIDTH)/7;
    int textYpos = (3*SCREEN_HEIGHT)/4;

    //Main loop flag
    bool quit = false;
    bool enter = false;
    bool success = true;

    //Event handler
    SDL_Event e;

    //Set text color as black
    SDL_Color textColor = { 0, 0, 0, 0xFF };

    //Open the font
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 16 );
    if( gFont == NULL )
    {
        printf( "Failed to load adamwarrenpro font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    //render the question 
    gPromptTextTexture.setFont(gFont);
    
    //The current input text.
    string inputText = "Erase and put answer here";
    gInputTextTexture.setFont(gFont);
    gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );

    //Enable text input
    SDL_StartTextInput();


    //While application is running
    while( !enter )
    {
        //The rerender text flag
        bool renderText = false;


        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            // User requests quit
            if( e.type == SDL_QUIT )
            {
                enter = true;
                // complete = true;
                break;
            }
            //Special key input
            else if( e.type == SDL_KEYDOWN )
            {
                //Handle backspace
                if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
                {
                    //lop off character
                    inputText.pop_back();
                    renderText = true;
                } //Handle Return (enter)
                else if ( e.key.keysym.sym == SDLK_RETURN ) 
                {
                    enter = true;
                    break;
                }
            }
            //Special text input event
            else if( e.type == SDL_TEXTINPUT )
            {
                //Not copy or pasting
                if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
                {
                    //Append character
                    inputText += e.text.text;
                    renderText = true;
                }
            }
        }

        //Rerender text if needed
        if( renderText )
        {
            //Text is not empty
            if( inputText != "" )
            {
                //Render new text
                gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
            }
            //Text is empty
            else
            {
                //Render space texture
                gInputTextTexture.loadFromRenderedText( " ", textColor );
            }
        }

       //Clear screen
        // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //Render text textures
        gPuzzleTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gPromptTextTexture.render( textXpos, textYpos );
        gInputTextTexture.render( textXpos, textYpos+gPromptTextTexture.getHeight() );

        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    
    //Disable text input
    SDL_StopTextInput();
    // questionAnswered=true;

    return inputText;


}


bool AlphabetPuzzle::validate( string userInput ) { //determines whether user input is correct or not
    bool correct = false;

    string answer = "6";

    if (userInput==answer) {
        correct = true;
        return correct;
    }
    
    return correct;

}

bool AlphabetPuzzle::loadMedia() {
    
    //Loading success flag
    bool success = true;
    
    //Open the background picture
    if( !gBackgroundTexture.loadFromFile( "Puzzles/alphabet/alphabet.png" ))
    {
        printf( "Failed to load background texture!\n" );
        success = false;
    }

    //Open puzzle picture
    if( !gPuzzleTexture.loadFromFile( "Puzzles/alphabet/alphabetpuzzle.png" ))
    {
        printf( "Failed to load background texture!\n" );
        success = false;
    }
    
    //Open the font
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 16 );
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
        if( !gPromptTextTexture.loadFromRenderedTextWrapped( "What is your answer?", textColor, 350 ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }

        gInputTextTexture.setFont(gFont);
        if( !gInputTextTexture.loadFromRenderedTextWrapped( " ", textColor, 350 ) )
        {
            printf( "Failed to render input text!\n" );
            success = false;
        }
    }
    
    
    return success;
}



