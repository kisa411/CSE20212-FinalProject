#ifndef ENDING_H
#define ENDING_H

#include <iostream>
#include "texture.h"
using namespace std;

class Ending {
	
public:
	Ending( SDL_Window*, SDL_Renderer* ); //default constructor
    ~Ending(); //destructor
    void display(); //display 

private:
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