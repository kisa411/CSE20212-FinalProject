/* Emily Koh
FCII Final Project
Spring 2016
Singaporean Math Puzzle class
*/
#ifndef SINGAPOREAN_H
#define SINGAPOREAN_H
using namespace std;

class SingaporeanPuzzle {

public:
	SingaporeanPuzzle(); //default constructor
	void displayPuzzle(); //display the puzzle picture 
	int playPuzzle(); //check for user input and see if input is correct - returns the amount of points that should be deducted from player's total 

private:
	int points; //depending on how many tries it took player to get right answer, points value changes

};


#endif