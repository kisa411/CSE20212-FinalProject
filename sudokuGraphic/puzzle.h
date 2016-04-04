#ifndef PUZZLE_H
#define PUZZLE_H


#include <vector>
#include <cstdio>
#include <cctype>
#include <iostream>
#include "puzzleElement.h"
#include "texture.h"
#include "puzzle.h"
#include "stdio.h"
#include "sdl_win_wrap.h"
#include "point.h"

using namespace std;

class Puzzle
{
	public:
	Puzzle(string fileName, SDL_Window*, SDL_Renderer*, int width, int height); // constructor
	~Puzzle(); // Destructor
	void interactive();
	void solve();
	private:
	vector< vector <int> > getIntVector();
	bool checkCol(int, int);
	bool checkRow(int, int);
	bool checkSquare(int, int, int);
	bool checkValue(int, int, int);
	bool checkSolved();
	bool checkAllowed(int);
	void setCheck();
	void display();
	// solver functions
	int singleton();
	int single_possibility();
	void manageEvents(SDL_Event &e, int &value, bool &gameover, bool &changeValue); // Function to manage events
	int size;
	FILE* file;
	point selector;
	vector<int> check;
	vector< vector <puzzleElement> > thePuzzle;
	//Textures and Clips
	SDL_Rect gSpriteClips[10];
	LTexture gSpriteSheetTexture;
	LTexture gBackgroundTexture;
	LTexture gSelectorTexture;
	bool loadMedia();
	
	// Renderer and Window
	//The window we'll be rendering to
	SDL_Window* gWindow;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

	//The window renderer
	SDL_Renderer* gRenderer;
};


#endif
	