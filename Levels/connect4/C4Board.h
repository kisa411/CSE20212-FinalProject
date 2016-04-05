#ifndef C4BOARD_H
#define C4BOARD_H

#include <iostream>
#include <stdbool.h> //for bool
#include "C4Col.h"
using namespace std;

class C4Board {
	public:
		C4Board();	//default constructor
		~C4Board();	//default deconstructor
		void setnumCol( int number );
		void display();	//displays the current board in simple text
		void play();	//allows two players to play a game, input is the number turn it is
		

	private:
		int numCol;	//number of columns
		C4Col *Board;	//pointer; array of C4Col objects to represent the Connect 4 Board, creates 7 objects of Class C4Col with currentdiscs as 0 and maxdiscs as 6 (connect the four board is empty and there's six rows) - this creates 7 columns 
		bool winner();
};

#endif