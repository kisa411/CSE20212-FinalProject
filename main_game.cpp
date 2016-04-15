//
//  main.cpp
//  FinalProject
//
//  Main program for the whole game
//

/*Include all the puzzle files*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "sdl_win_wrap.h"
#include "texture.hpp"

#include "player.h"
#include "opening.h"
#include "alphabetPuzzle.h"
#include "hangman.h"
#include "cardDeck.h"
#include "singaporePuzzle.h"
#include "ending.h"


using namespace std;

int main () {
	SDL_Win_Wrap window_instance; //SDL window object

	/*-----------player instance*----------*/
	Player player;

	/*-----------opening instance*----------*/
	Opening open( window_instance.getWindow(), window_instance.getRenderer() );
	char gender = open.display(); //get the gender of the player
	player.setGender( gender );

	/*-----------cryptography instance*----------*/


	/*-----------hangman instance*----------*/


	/*-----------river crossing instance*----------*/


	/*-----------sudoku instance*----------*/


	/*-----------alphabet puzzle instance*----------*/


	/*-----------blackjack instance*----------*/


	/*-----------singapore instance*----------*/


	/*-----------ending instance*----------*/
	Ending end( window_instance.getWindow(), window_instance.getRenderer(), player.getPoints(), player.getGender() );
	end.display();

}



