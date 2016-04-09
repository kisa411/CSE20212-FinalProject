/* Emily Koh
FCII Final Project
Spring 2016
Alphabet Puzzle class
*/

#include <iostream>
#include "alphabetPuzzle.h"
using namespace std;


int main () {
	AlphabetPuzzle game; //instantiate new object of Hangman game
	game.displayPuzzle(); //play the game 
	int number = game.playPuzzle(); 
	cout << "The number of points you got: " << number << endl;

}