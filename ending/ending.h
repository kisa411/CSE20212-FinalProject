//ENDING
//Emily Koh
//loads ending scene

#ifndef ENDING_H
#define ENDING_H

#include <iostream>
#include "../sharedClasses/texture.h"
using namespace std;

class Ending {
	
public:
	Ending( SDL_Window*, SDL_Renderer* , int points, string g ); //default constructor
    ~Ending(); //destructor
    bool display(); //display 

private:
	//SDL member variables and helper functions
    LTexture gBackgroundTexture;
    LTexture gPromptTextTexture;
    LTexture gTextTexture;
    
    //the window we'll be rendering to
    SDL_Window* gWindow;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    
    SDL_Renderer* gRenderer;
    TTF_Font *gFont; //font to use
    
    bool loadMedia(); //loads media
    bool continueText(SDL_Event & e); //continues text

    int pointTotal;
    string gender;


};



#endif
