#ifndef OPENING_H
#define OPENING_H

#include <iostream>
#include "texture.h"
using namespace std;

class Opening {

public:
	Opening( SDL_Window*, SDL_Renderer* ); //constructor
    ~Opening(); //destructor
    char display(); //display, update player gender

private:
	//SDL member variables and helper functions
    LTexture gBackgroundTexture;
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