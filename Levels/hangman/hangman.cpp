//
//  hangman.cpp
//  hangman
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#include "hangman.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <string.h>
#include <ctype.h>
#include <vector>
using namespace std;

Hangman::Hangman(SDL_Window* ngWindow, SDL_Renderer* ngRenderer ) : gTextTexture(ngWindow, ngRenderer), gBackgroundTexture(ngWindow, ngRenderer), gInputTextTexture(ngWindow, ngRenderer), gPromptTextTexture(ngWindow, ngRenderer), gWindow(ngWindow), gRenderer(ngRenderer) { //constructor
    points = 0; //set default point value as 0
    loadMedia();
    SDL_GetWindowSize(gWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT); //store the window dimensions
    word = "PUFFERFISH"; //answer to hangman puzzle
    display = ".........."; //if user gets a letter right, then the letter will show; if not then it remains an "_"
}

Hangman::~Hangman() {
    gBackgroundTexture.free();
    gTextTexture.free();
    gInputTextTexture.free();
    gPromptTextTexture.free();
}

void Hangman::displayOpening() {
    bool success = true;
    bool next = false;

    SDL_Event e;

    int textXpos = SCREEN_WIDTH/5;
    int textYpos = (8*SCREEN_HEIGHT)/11;
    SDL_Color textColor = { 0, 0, 0 };


    //Open the font
    //Free global font
    TTF_CloseFont( gFont );
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 18 );
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
        if( !gTextTexture.loadFromRenderedTextWrapped( "On the side of the road, you see a cat hanging for dear life on a tree! You can help the cat come down the tree only if you're able to solve this hangman problem. Hurry!", textColor, 400 ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }

    }
    SDL_RenderClear( gRenderer );
    while (!next) {
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gTextTexture.render( textXpos, textYpos );
        //Update screen
        SDL_RenderPresent( gRenderer );
        next=continueText(e);
    }
    next = false;
}

int Hangman::playPuzzle() {

    int endPoints = -100;
    bool complete = false;


    while (complete==false) {
        endPoints = determineEnding(); //determine the ending of the puzzle based on tryNumber
        if ( endPoints >= 0 ) {
            complete = true;
        }
    }

    return endPoints;

}


bool Hangman::validate( string letter ) { //play the puzzle
    bool complete = false;
    bool next = false;

    SDL_Event e;
    // bool checked = false;
    int textXpos = (2*SCREEN_WIDTH)/9;
    int textYpos = (3*SCREEN_HEIGHT)/4;
    SDL_Color textColor = { 0, 0, 0 };

    int npos=-1;


    for ( int j=0; j<letter.length(); j++ ) {
        letter[j] = ::toupper(letter[j]); //make the answer uppercase
    }
    // cout << word << endl;
    // cout << display.c_str() << endl;
    
    //add the letter to guessed letters if it was guessed before
    if ( find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end() ) {
        
        if( !gTextTexture.loadFromRenderedTextWrapped( "You already guessed that letter, try another letter.\n", textColor, 350 ) ) {
            printf( "Failed to render text texture!\n" );
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;
        return complete;
    } else {
        guessedLetters.push_back(letter); //add the letter to guessed letters
    }

    letter = letter.c_str();
    
    while ( word.find(letter) != npos ) { //look for the letter in the word
        int letterPosition = word.find(letter);
        word[letterPosition] = '.'; //change the letter to . so that it won't be found again
        display[letterPosition] = letter[0]; //display the letter in the hangman game
        word.find(letter);
    }

    // cout << "Here's the word after your guess: " << display << endl;

    if( !gTextTexture.loadFromRenderedText( "Here's the word after your guess: ", textColor ) ) {
        printf( "Failed to render text texture!\n" );
    }
    
    SDL_RenderClear( gRenderer );
    while (!next) {
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gTextTexture.render( textXpos, textYpos );
        //Update screen
        SDL_RenderPresent( gRenderer );
        next=continueText(e);
    }
    next = false;
    if( !gTextTexture.loadFromRenderedText( display.c_str(), textColor ) ) {
        printf( "Failed to render text texture!\n" );
    }

    SDL_RenderClear( gRenderer );
    while (!next) {
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gTextTexture.render( textXpos, textYpos );
        //Update screen
        SDL_RenderPresent( gRenderer );
        next=continueText(e);
    }
    next = false;
    
    if ( display.find('.') == npos) { //underscores no longer exist in the display string, the word was completed, hangman puzzle was solved
        cout <<"puzzle is complete." << endl;
        complete = true;
    }

    
    return complete; //if hangman puzzle is completed, returns true
    
}

bool Hangman::continueText(SDL_Event & e) {
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

int Hangman::determineEnding() {
    string guess;
    bool correct = false;
    int tryNumber=0;
    int textXpos = (2*SCREEN_WIDTH)/9;
    int textYpos = (3*SCREEN_HEIGHT)/4;
    SDL_Color textColor = { 0, 0, 0 };

    //Loading success flag
    bool success = true;
    bool next = false;


    //Event handler
    SDL_Event e;

    TTF_CloseFont( gFont );
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 18 );
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    gTextTexture.setFont(gFont);

    while (correct==false) {
        tryNumber++;
        guess = userInput(); //returns user's input
        correct = validate(guess); //returns whether or not the input is right
        if (correct==true) {
            // questionAnswered=true;
            if( !gTextTexture.loadFromRenderedTextWrapped( "Congratulations! You got it correct!\n  ", textColor, 350 ) ) {
                printf( "Failed to render text texture!\n" );
            }
            SDL_RenderClear( gRenderer );
            while (!next) {
                gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
                gTextTexture.render( textXpos, textYpos );
                //Update screen
                SDL_RenderPresent( gRenderer );
                next=continueText(e);
            }
            next = false;
            completed( tryNumber );
            return points;
        } else if (correct==false) {
            if( !gTextTexture.loadFromRenderedTextWrapped( "You still have some empty spaces!\n  ", textColor, 350 ) ) {
                printf( "Failed to render text texture!\n" );
            }
            // questionAnswered=false;
            SDL_RenderClear( gRenderer );
            while (!next) {
                gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
                gTextTexture.render( textXpos, textYpos );
                //Update screen
                SDL_RenderPresent( gRenderer );
                next=continueText(e);
            }
            next = false;
        }

    }
}

void Hangman::completed( int guess ) {

    //Loading success flag
    bool success = true;
    bool next = false;

    SDL_Event e;

    int textXpos = ((2*SCREEN_WIDTH)/8)-30;
    int textYpos = (8*SCREEN_HEIGHT)/11;

    SDL_Color textColor = { 0, 0, 0, 0xFF };
    gTextTexture.setFont(gFont);



    if ( guess>=1 && guess<9 ) { //player receives quality sushi (1~8)
        if( !gTextTexture.loadFromRenderedTextWrapped( "Wow! You got the word right in less than 9 guesses! You were able to quickly save the cat and the cat was so impressed with you it gave you some A-grade quality sushi for your recipe!\n", textColor, 420 ) ) {
            printf( "Failed to render text texture!\n" );
            success=false;
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;
        points = 100;
        
    } else if ( guess>=9 && guess<11 ) { //player receives raw fish (9~10)
        if( !gTextTexture.loadFromRenderedTextWrapped( "Wow! You were able to solve the puzzle in less than 11 guesses! You were able to save the cat and the cat was pretty happy with you so he gave you a raw fish for your recipe!\n", textColor, 420 ) ) {
            printf( "Failed to render text texture!\n" );
            success=false;
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;        points = 70;
        
    } else if ( guess>=11 && guess<15 ) { //player receives fish bones (11~)
        if( !gTextTexture.loadFromRenderedTextWrapped( "Hm...well you were able to solve the puzzle in less than 15 guesses and were able to save the cat before he fell off the tree. The cat gave you some of his leftover fish bones partly because he was grateful but mostly out of relief that he hadn't fallen completely out of the tree.\n", textColor, 420 ) ) {
            printf( "Failed to render text texture!\n" );
            success=false;
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;
        points = 40;
        
    } else {
        if( !gTextTexture.loadFromRenderedTextWrapped( "You took so long in solving the puzzle the cat fell off the tree and was too angry to give you anything cool except for some scratches on your face. Sorry! :(\n", textColor, 420 ) ) {
            printf( "Failed to render text texture!\n" );
            success=false;
        }
        SDL_RenderClear( gRenderer );
        while (!next) {
            gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
            gTextTexture.render( textXpos, textYpos );
            //Update screen
            SDL_RenderPresent( gRenderer );
            next=continueText(e);
        }
        next = false;
    }

}

string Hangman::userInput() {

    int textXpos = (2*SCREEN_WIDTH)/9;
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
    string inputText = "Guess Here";
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
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gPromptTextTexture.render( textXpos, textYpos );
        gInputTextTexture.render( textXpos+50, textYpos+gPromptTextTexture.getHeight() );

        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    
    //Disable text input
    SDL_StopTextInput();
    // questionAnswered=true;

    return inputText;


}

bool Hangman::loadMedia() {

     //Loading success flag
    bool success = true;
    
    //Open the background picture
    if( !gBackgroundTexture.loadFromFile( "Levels/hangman/cat.png" ))
    {
        printf( "Failed to load background texture!\n" );
        success = false;
    }

    
    //Open the font
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 18 );
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
        if( !gPromptTextTexture.loadFromRenderedTextWrapped( "Which letter would you like to guess?", textColor, 400 ) )
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





