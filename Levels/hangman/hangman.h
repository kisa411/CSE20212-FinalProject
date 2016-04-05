/* Emily Koh
FCII Final Project
Spring 2016
Hangman Class
*/

#ifndef HANGMAN_H
#define HANGMAN_H

#include <iostream>
using namespace std;

class Hangman {
	
public:
	Hangman(); //constructor
	int playPuzzle(); //check for user input and see if input is correct - returns the amount of points that should be added to player's total 

private:
	int points; //depending on how many tries it took player to get right answer, points value changes

};



#endif





