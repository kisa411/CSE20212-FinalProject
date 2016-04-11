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
	Puzzle(string fileName, SDL_Window*, SDL_Renderer*); // constructor
	~Puzzle(); // Destructor
	void interactive();
	void solve();
	private:
	// Sudoku Management
	vector< vector <int> > getIntVector();
	bool checkCol(int, int);
	bool checkRow(int, int);
	bool checkSquare(int, int, int);
	bool checkValue(int, int, int);
	bool checkSolved();
	bool checkAllowed(int);
	void setCheck();
	
	// solver functions
	int singleton();
	int single_possibility();
	vector<int> check;
	
	//Textures and Clips
	SDL_Rect gSpriteClips[10];
	LTexture gSpriteSheetTexture;
	LTexture gBackgroundTexture;
	LTexture gSelectorTexture;
	vector <LTexture*> instructions; // pointer to array of textures containing lines
	LTexture message; // Text texture to display messages to user
	bool loadMedia();
	
	// Renderer and Window
	//The window we'll be rendering to
	SDL_Window* gWindow;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	//Renderer
	SDL_Renderer* gRenderer;
	
	// SDL Management
	void display();
	void manageEvents(SDL_Event &e, int &value, bool &gameover, bool &changeValue); // Function to manage events
	bool setInstructions();
	void displayInstructions();
	void displayMessage();
	void updateMessage(string);
	
	// Other Member FunctionFILE* file;
	point selector;
	int size;
	vector< vector <puzzleElement> > thePuzzle; // Stores Data for Puzzle
	bool correctlyInitialized; // Checks if sudoku was correctly initialized
	TTF_Font *bodyFont;
	TTF_Font *titleFont;
	SDL_Color fontColor;
};


#endif
	
