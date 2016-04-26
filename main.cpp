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
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "sharedClasses/sdl_win_wrap.h"
#include "sharedClasses/texture.h"
#include "Levels/sudoku/puzzle.h"
#include "player.h"
#include "opening/opening.h"
//include cryptography
#include "Levels/hangman/hangman.h"
//include river crossing
//include sudoku
#include "Puzzles/alphabet/alphabetPuzzle.h"
//include blackjack
#include "Puzzles/singapore/singaporePuzzle.h"
#include "Puzzles/cryptography/cryptography.h"
#include "Puzzles/rivercrossingPuzzle/Rivercrossing.h"
#include "Levels/blackjack/Blackjack.h"
#include "Levels/hangman/hangman.h"
#include "ending/ending.h"


using namespace std;

int main () {
	SDL_Win_Wrap window_instance; //SDL window object
	SDL_Window* gWindow = window_instance.getWindow();
	SDL_Renderer* gRenderer = window_instance.getRenderer();
	bool quit = false;

	/*----------Load music-----------------*/
	Mix_Music *gMusic = NULL;
	gMusic = Mix_LoadMUS("Sweet_Success.wav");
	if (gMusic == NULL) {
		printf("Failed to load music! SDL_mixer error: %s\n", Mix_GetError());

	}

	/*----------Play music---------------*/
	if (Mix_PlayMusic(gMusic, -1) < 0) {
		printf("Failed to play music! SDL_mixer error: %s\n", Mix_GetError());
	}

	/*-----------player instance*----------*/
	Player player;

	/*-----------opening instance*----------*/
	Opening open(gWindow, gRenderer, &quit);
	open.displayRoom();
	string gender = "N/A";
	while ( gender=="N/A" && !quit) {
		gender = open.play();
	}
	player.setGender(gender);
	/*-----------cryptography instance*----------*/
	int temp;
	if(!quit)
	{
		crypto cryptoGame(gWindow, gRenderer, &quit);
		temp = cryptoGame.play();
		player.changePoints( temp );
	}
	/*-----------hangman instance*----------*/
	if(!quit)
	{
		Hangman hangGame( gWindow, gRenderer, &quit );
		hangGame.displayOpening();
		temp = -100;
		while (temp<0 && !quit) {
			temp = hangGame.playPuzzle();
		}
		player.changePoints( temp );
	}
	/*-----------river crossing instance*----------*/
	if(!quit)
	{
		Rivercrossing river(gWindow, gRenderer, &quit);
		temp = river.play();
		player.changePoints(temp);
	}
	/*-----------sudoku instance*----------*/
	if(!quit)
	{
		Puzzle thePuzzle(gWindow, gRenderer, &quit);
		temp = thePuzzle.interactive();
		player.changePoints(temp);
	}	
	/*-----------alphabet puzzle instance*----------*/
	if(!quit)
	{
		AlphabetPuzzle alphaGame( gWindow, gRenderer, &quit );
		alphaGame.displayTown();
		temp = 100;
		while ( temp>0 && !quit) {
			temp = alphaGame.playPuzzle();
		}
		player.changePoints( temp );
	}

	/*-----------blackjack instance*----------*/
	if(!quit)
	{
		Blackjack bgame(gWindow, gRenderer, &quit);
		temp = bgame.play();
		player.changePoints(temp);
	}
	/*-----------singapore instance*----------*/
	if(!quit)
	{
		SingaporeanPuzzle singaGame( gWindow, gRenderer, &quit );
		singaGame.displayRobber();
		temp = 100;
		while ( temp>0 && !quit) {
			temp = singaGame.playPuzzle();
		}
		player.changePoints( temp );
	}
	/*-----------ending instance*----------*/
	if(!quit)
	{
		Ending end( gWindow, gRenderer, player.getPoints(), player.getGender(), &quit );
		bool complete = false;

		while (!complete && !quit) {
			complete = end.display();
		}
	}

    Mix_HaltMusic(); //stop music
    Mix_FreeMusic(gMusic); //free music


}



