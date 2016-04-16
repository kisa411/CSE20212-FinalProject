//
//  main.cpp
//  hangman
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "hangman.h"
#include "sdl_win_wrap.h"
#include "texture.h"

using namespace std;

int main(int argc, const char * argv[]) {
    SDL_Win_Wrap window_instance; //SDL window object

    int points = -100;

    Hangman game(window_instance.getWindow(), window_instance.getRenderer()); //instantiate new object of Hangman game
    
    for ( int i=0; i<2000; i++ ) {
    	game.displayOpening();
    }

    while (points<0) {
	    points = game.playPuzzle();
	    cout << "Player's points: " << points << endl;
	}


    return 0;
}
