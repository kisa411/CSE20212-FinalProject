#include "opening.h"
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
    Opening open( window_instance.getWindow(), window_instance.getRenderer() ); //AlphabetPuzzle object
    
    char gender;

	for (int i=0; i<1000; i++) {
		gender = open.display();
	}
	cout << "Player's gender will be: " << endl;

	return 0;
}