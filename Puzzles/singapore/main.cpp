//
//  main.cpp
//  singaporePuzzle
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "singaporePuzzle.h"
#include "sdl_win_wrap.h"
#include "texture.h"
using namespace std;

int main(int argc, const char * argv[]) {
   
    SDL_Win_Wrap window_instance; //SDL window object
    
    SingaporeanPuzzle puzzle( window_instance.getWindow(), window_instance.getRenderer() ); //Singaporean Puzzle object
    puzzle.displayPuzzle();
    puzzle.playPuzzle();
}
