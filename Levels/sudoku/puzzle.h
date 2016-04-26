/* Luis Prieb
 * This class is the main sudoku class. Its what puts together the same, solves it if the user gives up,
 * and determines the number of points the user earns
 */

#ifndef PUZZLE_H
#define PUZZLE_H


#include <vector>
#include <cstdio>
#include <cctype>
#include <iostream>
#include "puzzleElement.h"
#include "../../sharedClasses/texture.h"
#include "puzzle.h"
#include "stdio.h"
#include "../../sharedClasses/sdl_win_wrap.h"
#include "point.h"

using namespace std;

class Puzzle
{
	public:
	Puzzle(SDL_Window*, SDL_Renderer*); // constructor
	~Puzzle(); // Destructor
	int interactive(); // Returns points to add to player
	private:
	// Sudoku Management
	bool checkCol(int, int); // Checks if a value can be placed in a column
	bool checkRow(int, int); // Checks if a value can be placed in a row
	bool checkSquare(int, int, int); // Checks if a value can be placed in a square
	bool checkValue(int, int, int); // Checks if a value can be placed in a particular position. Calls the three above
	bool checkSolved(); // Checks if the puzzle has been solved
	bool checkAllowed(int); // Checks if a user input is a valid input
	void setCheck(); // Intializes a vector containing valid numbers
	void clear(); // Clear all of the user numbers
	
	// solver functions
	void solve(); // Solves the puzze
	int singleton();
	int single_possibility();
	vector<int> check; // Vector used to store possible integers
	
	//Textures and Clips
	SDL_Rect gSpriteClipsRed[10]; // To be used with puzzle numbers
	SDL_Rect gSpriteClipsBlue[10]; // To be used with user numbers
	LTexture gSpriteSheetTexture;
	LTexture gBackgroundTexture;
	LTexture gSelectorTexture;
	vector <LTexture*> instructions; // pointer to array of textures containing lines
	LTexture messageTextTexture; // Text texture to display messages to user
	LTexture timeTextTexture; // Text to display current time
	LTexture storyTextTexture;
	bool loadMedia();
	
	// Renderer and Window
	//The window we'll be rendering to
	SDL_Window* gWindow;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	//Renderer
	SDL_Renderer* gRenderer;
	
	// SDL Management
	void display(int min, int sec); // Displays main game
	void displayIntro();
	void manageEvents(SDL_Event &e, int &value, bool &gameover, bool &changeValue, bool &giveUp, bool &toClear, bool &enter); // Function to manage SDL events
	bool setInstructions(); // Initalizes Instructions Texture
	void displayInstructions();
	void displayMessage();
	void displayTime(int min, int sec);
	void displayScreen(string text, string background_filename);
	void displayGiveUpEnding(int min, int sec);
	void displayRegularEnding(int min, int sec);
	bool loadBackground(string filename);
	void updateMessage(string); // Updates message displayed to the user
	bool checkEnter(bool &enter, SDL_Event &e); // Checks if the user has pressed enter
	
	// Other Member FunctionFILE* file;
	point selector;
	int size;
	vector< vector <puzzleElement> > thePuzzle; // Stores Data for Puzzle
	bool correctlyInitialized; // Checks if sudoku was correctly initialized
	TTF_Font *bodyFont;
	TTF_Font *titleFont;
	TTF_Font *timeFont;
	TTF_Font *storyFont;
	SDL_Color fontColor;
	bool quit; // Variable to use to quit from game when x is entered
};


#endif
	
