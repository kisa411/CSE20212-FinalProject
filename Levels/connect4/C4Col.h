#ifndef C4COL_H
#define C4COL_H

#include <iostream>
#include <stdbool.h>
using namespace std;

//seven rows, six columns

class C4Col {
	public:
		C4Col();	//default constructor
		~C4Col();	//default deconstructor
		int isFull();	//determines if the column is full (i.e., numDiscs == maxDiscs)
		char getDisc( int position );	//returns the request element of the private character array (i.e., getDisc(0) will return Discs[0])
		int getMaxDiscs();	//returns the maximum number of discs (i.e., number of rows)
		void addDisc( char piece );	//adds the character representing a disc to the next open slot in the Disc array (i.e.,Discs[numDiscs++] = newDisc)
		void setcurrentDiscs( int number );	//sets value for currentDiscs
		void setmaxDiscs( int number );	//sets value for max Discs
		void setdiscArray( char character );	//sets initial values of disc array

	private:
		int currentDiscs, maxDiscs;
		char *discs;	//pointer to the variable discs
};

#endif

