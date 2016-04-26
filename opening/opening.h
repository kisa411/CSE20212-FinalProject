//Opening - loads opening sequence
//Emily Koh

#ifndef OPENING_H
#define OPENING_H

#include <iostream>
#include "../sharedClasses/texture.h"
using namespace std;

class Opening {

public:
	Opening( SDL_Window*, SDL_Renderer* ); //constructor
    ~Opening(); //destructor
    string display(); //display, update player gender
    void displayRoom(); //display opening scene
    string play(); //driver function

private:
	//SDL member variables and helper functions
    LTexture gBackgroundTexture;
    LTexture gInputTextTexture;
    LTexture gPromptTextTexture;
    LTexture gTextTexture;
    
    //the window we'll be rendering to
    SDL_Window* gWindow;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    
    SDL_Renderer* gRenderer;
    TTF_Font *gFont; //font to use
    
    bool loadMedia(); //loads media
    string userInput(); //checks for user input
    bool continueText(SDL_Event & e); //continues text

};



#endif
