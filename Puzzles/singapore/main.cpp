/* Emily Koh
FCII Final Project
Spring 2016
Singaporean Math Puzzle class
*/

#include <iostream>
#include "singaporeanMathPuzzle.h"
using namespace std;


int main () {
	SingaporeanPuzzle game; //instantiate new object of Hangman game
	game.displayPuzzle(); //play the game 
	int number = game.playPuzzle(); 
	cout << "The number of points you got: " << number << endl;

}