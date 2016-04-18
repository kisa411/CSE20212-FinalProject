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
//include cryptography
#include "hangman.h"
//include river crossing
//include sudoku
#include "alphabetPuzzle.h"
//include blackjack
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
	Hangman game( window_instance.getWindow(), window_instance.getRenderer() );
	for ( int i=0; i<1500; i++ ) { //display opening sequence
		game.displayOpening();
	}
	int temp = -100;
	while (temp<0) {
		temp = game.playPuzzle();
	}
	player.changePoints( temp );

	/*-----------river crossing instance*----------*/


	/*-----------sudoku instance*----------*/


	/*-----------alphabet puzzle instance*----------*/
	AlphabetPuzzle game( window_instance.getWindow(), window_instance.getRenderer() );
	for ( int i=0; i<2000; i++ ) { //display opening sequence
		game.displayTown();
	}
	temp = 100;
	while ( temp>0 ) {
		temp = game.playPuzzle();
	}
	player.changePoints( temp );

	/*-----------blackjack instance*----------*/


	/*-----------singapore instance*----------*/
	SingaporeanPuzzle game( window_instance.getWindow(), window_instance.getRenderer() );
	for ( int i=0; i<2000; i++ ) { //display opening sequence
		game.displayRobber();
	}
	temp = 100;
	while ( temp>0 ) {
		temp = game.playPuzzle();
	}
	player.changePoints( temp );


	/*-----------ending instance*----------*/
	Ending end( window_instance.getWindow(), window_instance.getRenderer(), player.getPoints(), player.getGender() );
	end.display();

}



