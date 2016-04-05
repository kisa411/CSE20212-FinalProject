#include <iostream>
#include <stdbool.h> //for bool
#include "C4Col.h"
using namespace std;

C4Col::C4Col() {	//default constructor
	discs = new char[6]; //discs is a pointer to a character array with 6 elements - doesn't take up more memory than necessary - 6 is the max size - only allocates the amount of memory that you need (dynamic only scales as much as you need it to)
	currentDiscs = 0;
	maxDiscs = 6; //maximum number of rows (6)
	setdiscArray(' ');
}


C4Col::~C4Col() {	//default deconstructor
	delete[] discs; //delete the pointer to the character array
	//cout << "Something was deleted." << endl;
}


int C4Col::isFull() {	//determines if the column is full (i.e., numDiscs == maxDiscs)
	if (maxDiscs == currentDiscs) {
		return 1;	//full, therefore true
	}
	return 0;
}

char C4Col::getDisc( int position ) {	//returns the request element of the private character array (i.e., getDisc(0) will return Discs[0])
	if ( position < 0 || position > 7 ) {	//invalid position since it's not within the allowed columns
		cout << "That position is invalid. Please enter a position from 1~6." << endl;
	} else {
		return discs[position];	//return position-1 since arrays start from 0.
	}
}

int C4Col::getMaxDiscs() {	//returns the maximum number of discs (i.e., number of rows)
	return maxDiscs;
}
	
void C4Col::addDisc( char piece ) {	//adds the character representing a disc to the next open slot in the Disc array (i.e.,Discs[numDiscs++] = newDisc)
	if ( currentDiscs == maxDiscs ) {	//column is full
		// cout << "The current number of discs is " << currentDiscs << endl;
		// cout << "The max number of discs is " << maxDiscs << endl;
		cout << "The column/row is full, you cannot place a piece there." << endl;
	} else {
		discs[currentDiscs] = piece;
		currentDiscs++;	//increment the number of current discs by 1
		//cout << "The current number of discs is " << currentDiscs << endl;
	}
}

void C4Col::setcurrentDiscs( int number ) {	//set function
	currentDiscs = number;
}

void C4Col::setmaxDiscs( int number ) {	//set function
	maxDiscs = number;
}

void C4Col::setdiscArray( char piece ) {	//set function
	int i;

	for ( i=0; i<=maxDiscs; i++ ) {	//initialize all the elements of the array to empty space
		discs[i] = ' ';
	}
}
	

