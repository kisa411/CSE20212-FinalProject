/* Emily Koh
FCII Final Project
Spring 2016
Alphabet Puzzle Class
*/
#ifndef ALPHABET_H
#define ALPHABET_H
#include <iostream>
using namespace std;

class AlphabetPuzzle {

public:
	AlphabetPuzzle(); //default constructor
	displayPuzzle(); //display the puzzle picture 
	playPuzzle(); //check for user input and see if input is correct

private:
	int points; //depending on how many tries it took player to get right answer, points value changes

};


#endif