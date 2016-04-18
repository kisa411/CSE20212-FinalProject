#include "ending.h"
//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "sdl_win_wrap.h"
#include "texture.h"
using namespace std;

int main () {
	SDL_Win_Wrap window_instance; //SDL window object
    Ending end( window_instance.getWindow(), window_instance.getRenderer() );



	return 0;
}