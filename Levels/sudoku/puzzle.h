#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

template <typename T> //using templates to make the program generic - make it work for numbers and characters
class Puzzle {

public:
	Puzzle( string filename ); //constructor - read in values from file and put them in a 2D vector
	T getValue( int row, int col ); //return the value of the element at the specified position
	void printPuzzle(); //print out the sudoku puzzle
	void playPuzzle(); //starts the game, interactive portion
	bool checkRow( T &value, int row ); //check user input validity in row
	bool checkCol( T &value, int col ); //check user input validity in column
	bool checkGrid( T &value, int row, int col ); //check user input validity in mini-grid
	void insertValue( T &value, int row, int col ); //put int or char where user wants
	bool isComplete(); //check to see if the puzzle was completed correctly
	bool isEmpty(); //check to see if all spots are filled

private:
	//vector< vector<T> > puzzleVector(9, vector<T>(9)); //2D vector to store values of type T
	vector< vector<T> > puzzleVector;
	vector<int> defaultRow; //store the row position of default values
	vector<int> defaultCol; // store the col position of default values
};


//FOR TEMPLATED CLASSES INCLUDE IMPLEMENTATION IN HEADER (INTERFACE) FILE

template <typename T>
Puzzle<T>::Puzzle( string filename ) { 
	int i, j;
	int size = 9; //size = number of rows
	T c; //c is the thing to get from the file

	ifstream datafile(filename.c_str()); //open datafile


	for ( i=0; i<size; i++ ) { //put empty vectors in the rows of the overall vector
		puzzleVector.push_back( vector<T>() ); //puts 9 empty vectors in the overarching vector - () after vector<T> calls on the constructor
	}
	
	if ( datafile.is_open() ) {	
		while ( datafile.good() ) { //while the file is good
			//cout << "here two" << endl;
			for ( i=0; i<size; i++ ) { //for each empty vector row
				for ( j=0; j<size; j++ ) { //read in 9 characters from file and put them in the vector
					
					datafile >> c; //read in character from file
					//cout << "i is: " << i << " j is: " << j << " c is: " << c << endl;
					puzzleVector[i].push_back(c);
					

					int b = c; //for wordoku, need to convert '0' char to int 0
					if ( c != 0 && c != '0' ) { //if the program reads in a number that was originally in the puzzle, then it should store the position so that later the user can't erase that default value
						defaultRow.push_back(i); //store row position
						//cout << "added value to row" << endl;
						defaultCol.push_back(j); //store col position
						//cout << "added value to column" << endl;
					}
				}
			} break;
		}
	}
	
	datafile.close(); //close file after done reading from it 	
}

template <typename T>
T Puzzle<T>::getValue( int row, int col ) { //returns the value of the element at the position
	
	return puzzleVector[row][col]; 

}

template <typename T>
void Puzzle<T>::printPuzzle() { //prints out the puzzle that was read in from the file - need to use iterator
	int j, row = 9;
	typename vector<T>::const_iterator i; //make an iterator so that program can go through each element of the vector and print it out

	for ( j=0; j<row; j++ ) {
		for( i = puzzleVector[j].begin(); i != puzzleVector[j].end(); ++i ) { //print out vector values
			cout << *i << " "; //* is necessary so that it prints out the value that the iterator is pointing to
		} cout << endl;
	}

}


template <typename T>
bool Puzzle<T>::checkRow( T &value, int row ) { //checks to see if user input is valid in a row
	int i;
	for ( i=0; i<9; i++ ) { 
		if ( puzzleVector[row-1][i] == value ) { //did not pass check, return false
			cout << "The row already has that value." << endl;
			return false;
		} 
	}

	
	return true; //passed check, return true
}

template <typename T>
bool Puzzle<T>::checkCol( T &value, int col ) { //checks to see if user input is valid in a column 
	int i;
	for ( i=0; i<9; i++ ) {
		if ( puzzleVector[i][col-1] == value ) { //did not pass check, return false
			cout << "The column already has that value." << endl;
			return false;
		} 
	}

	
	return true; //passed check, return true
}

template <typename T>
bool Puzzle<T>::checkGrid( T &value, int row, int col ) { //checks to see if user input is valid in the mini-grid
	int i, j;

	//set all the row and column values to start from top row, left square so that you can just go through the mini-grid from the same spot each time
	if ( row%3==1 ) {
		if ( col%3==1 ) { //top row, left square
			i = row; 
			j = col;
		} else if ( col%3==2 ) { //top row, middle square
			i = row;
			j = col-1;
		} else if ( col%3==0 ) { //top row, right square
			i = row;
			j = col-2;
		}
	} else if ( row%3==2 ) {
		if ( col%3==1 ) { //middle row, left square
			i = row-1; 
			j = col;
		} else if ( col%3==2 ) { //middle row, middle square
			i = row-1;
			j = col-1;
		} else if ( col%3==0 ) { //middle row, right square
			i = row-1;
			j = col-2;
		}
	} else if ( row%3==0 ) {
		if ( col%3==1 ) { //bottom row, left square
			i = row-2; 
			j = col;
		} else if ( col%3==2 ) { //bottom row, middle square
			i = row-2;
			j = col-1;
		} else if ( col%3==0 ) { //bottom row, right square
			i = row-2;
			j = col-2;
		}
	}

	
	for ( i=row; i<row+3; i++ ) {
		for ( j=col; j<col+3; j++ ) {
			if ( puzzleVector[i-1][j-1]==value ) {
				cout << "The grid already has that value." << endl;
				return false; //value is in the mini-grid, cannot be placed
			}
		}
	}
	
	
	return true; //value is not in the mini-grid, can be placed
}

template <typename T>
void Puzzle<T>::insertValue( T &value, int row, int col ) { //puts an integer or character at the place user wants to place 
	int i, proceed = 0;

	if ( row >= 10 || row < 1 || col >= 10 || col < 1 ) {
		cout << "The row or column is out of bounds. Please put in a value from 1~9." << endl;
		return;
	}
	for ( i=0; i<defaultRow.size(); i++ ) { //loop through stored positions of default values and if position corresponds with one of the values then say 'no'
		if ( (row-1) == defaultRow[i] && (col-1) == defaultCol[i] ) {
			cout << "That's a default value - you can't erase that." << endl;
			break;
		} else { 
			proceed = 1; //value isn't being placed in a default value position, go ahead
		}
	}


	if ( proceed == 1 ) { //allow the user to insert value 
		if ( checkRow( value, row )==true ) { //if row is clear
			//cout << "checked row" << endl;
			if ( checkCol( value, col )==true ) { //if column is clear
				//cout << "checked col" << endl;
				if ( checkGrid( value, row, col )==true ) { //if grid is clear
					//cout << "checked grid" << endl;
					puzzleVector[row-1][col-1] = value; //place value
					cout << "Value was successfully placed at row: " << row << " and column: " << col << endl;
				}
			}
		} else {
			cout << "Sorry, that's not a valid position since the value overlaps with a pre-existing value on the board. Try again!" << endl << endl;
		}
	}
	

}

template <typename T>
bool Puzzle<T>::isComplete() { //checks if puzzle was completed correctly
	if ( isEmpty()==false ) {//if all spots are filled
		return true; //the puzzle was completed correctly
	}

	return false; //the puzzle is incorrect

}

template <typename T>
bool Puzzle<T>::isEmpty() { //check if there are no empty values (check for 0s)
	int i, j;

	for ( i=0; i<9; i++ ) {
		for ( j=0; j<9; j++ ) {
			if ( puzzleVector[i][j]==0 ) {
				return true; //found an empty spot
			}
		}
	}

	return false; //all spots are filled
}

template <typename T>
void Puzzle<T>::playPuzzle() { //start the sudoku puzzle 
	int choice, row, col, loop = 1;
	T value;

	while ( loop == 1 ) {
		cout << "What would you like to do?\n 1. Place a value.\n 2. Replace a value.\n 3. Print the current board.\n 4. Quit the game.\n" << endl;
		cin >> choice;

		switch (choice) {
			case 1:
				printPuzzle(); //show the original puzzle
				cout << "What is the value that you would like to put in?" << endl;
				cin >> value;
				cout << "In what row do you want to put in the value?" << endl;
				cin >> row;
				cout << "In what column do you want to put in the value?" << endl;
				cin >> col;
				insertValue( value, row, col );
				if ( isComplete() == 1 ) {
					cout << "You've successfully completed the puzzle! Congrats :)" << endl;
					printPuzzle();
					cout << "Now quitting the game.\n" << endl;
					loop = 0;
				} 
				cout << endl;
				break;
			case 2:
				printPuzzle();
				cout << "What is the value that you would like replace with?" << endl;
				cin >> value;
				cout << "In what row do you want to replace the value?" << endl;
				cin >> row;
				cout << "In what column do you want to replace the value?" << endl;
				cin >> col;
				insertValue( value, row, col ); 
				cout << endl;
				break;
			case 3:
				printPuzzle();
				cout << endl;
				break;
			case 4:
				cout << "Thanks for playing!" << endl;
				loop = 0;
				break;
		}
	}
	
}


#endif