//
//  main.cpp
//  singaporePuzzle
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
#include "singaporePuzzle.h"
#include "sdl_win_wrap.h"
#include "texture.h"
using namespace std;

int main(int argc, const char * argv[]) {
	
	int points = 100;
    SDL_Win_Wrap window_instance; //SDL window object
   
    SingaporeanPuzzle puzzle( window_instance.getWindow(), window_instance.getRenderer() ); //Singaporean Puzzle object

    for ( int i=0; i<2500; i++ ) {
    	puzzle.displayRobber();
    }
    
    while (points>0) {
	    points = puzzle.playPuzzle();
	    cout << "Player's points: " << points << endl;
	}

}


