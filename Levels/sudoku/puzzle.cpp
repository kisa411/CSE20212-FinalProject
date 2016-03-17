#include <iostream>
#include <fstream> //for file input and output
#include <vector>
#include <string>
#include <cstring>
#include "puzzle.h"

using namespace std;

template <typename T>
Puzzle<T>::Puzzle( string filename ) { //constructor - 1 is sudoku, 2 is wordoku
	//string word;
	int i, j;
	int size = 9; //size = number of rows
	T c; //c is the thing to get from the file

	

	for ( i=0; i<size; i++ ) { //put empty vectors in the rows of the overall vector
		puzzleVector.push_back( vector<T>() ); //puts 9 empty vectors in the overarching vector - () after vector<T> calls on the constructor
		filename >> c; //read in the first character from the file
		while ( c ) {
			for ( i=0; i<size; i++ ) { //for each empty vector row
				for ( j=0; j<9; j++ ) { //read in 9 characters from file and put them in the vector
					puzzleVector[i].push_back(c);
					if ( c != 0 ) { //if the program reads in a number that was originally in the puzzle, then it should store the position so that later the user can't erase that default value
						defaultRow.push_back(i); //store row position
						defaultCol.push_back(j); //store col position
					}
					filename >> c; //read in next character from the file
				}
			}
		}
	}

	
}



template <typename T>
void Puzzle<T>::printPuzzle() { //prints out the puzzle that was read in from the file - need to use iterator
	int j, row = 9;
	vector<int>::const_iterator i; //make an iterator so that program can go through each element of the vector and print it out

	for ( j=0; j<row; j++ ) {
		for( i = puzzleVector[j].begin(); i != puzzleVector[j].end()-1; ++i ) { //print out vector values
			cout << *i << " "; //* is necessary so that it prints out the value that the iterator is pointing to
		}
	}

}

template <typename T>
void Puzzle<T>::playPuzzle() { //start the sudoku puzzle 
	int choice, row, col, loop = 1;
	T value;

	while ( loop == 1 ) {
		cout << "What would you like to do? 1. Place a value.\n 2. Erase a value.\n 3. Print the current board.\n 4. Quit the game.\n" << endl;
		cin >> choice;

		switch (choice) {
			case 1:
				cout << "What is the value that you would like to put in?" << endl;
				cin >> value;
				cout << "What is the row number that you would like to put the value in?" << endl;
				cin >> row;
				cout << "What is the column number that you would like to put the value in?" << endl;
				cin >> col;
				puzzleVector.insertValue( value, row, col );
				if ( puzzleVector.isComplete() == 1 ) {
					cout << "You've successfully completed the puzzle! Congrats :)" << endl;
					puzzleVector.printPuzzle();
					cout << "Now quitting the game.\n" << endl;
					loop = 0;
				}
				break;
			case 2:
				cout << "What is the row number you want to erase a value from?" << endl;
				cin >> row;
				cout << "What is the column number you want to erase a value from?" << endl;
				cin >> col;
				puzzleVector.eraseValue( row, col );
				break;
			case 3:
				puzzleVector.printPuzzle();
				break;
			case 4:
				loop = 0;
				break;
		}
	}
	
}

template <typename T>
bool Puzzle<T>::checkRow( T &value, int row ) { //checks to see if user input is valid in a row
	int i;
	for ( i=0; i<9; i++ ) { 
		if ( puzzleVector[row-1].getValue(i) != value ) { //if the number that the user wants to put in the board is not already in that row, then return true
			return true;
		} 
	}

	cout << "The row already has that value." << endl;
	return false; //did not pass the check, return false
}

template <typename T>
bool Puzzle<T>::checkCol( T &value, int col ) { //checks to see if user input is valid in a column 
	int i;
	for ( i=0; i<9; i++ ) {
		if ( puzzleVector[i].getValue(col-1) != value ) { //if the number that the user wants to put in the board is not already in that column, then return true
			return true;
		} 
	}

	cout << "The column already has that value." << endl;
	return false; //did not pass the check, return false
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
			if ( puzzleVector[i-1].getValue(j-1)!=value ) {
				return true; //value is not in the mini-grid, can be placed
			}
		}
	}
	
	cout << "The grid already has that value." << endl;
	return false; //value is in the mini-grid, cannot be placed
}

template <typename T>
void Puzzle<T>::insertValue( T &value, int row, int col ) { //puts an integer or character at the place user wants to place 
	int i;

	for ( i=0; i<defaultRow.size(); i++ ) { //loop through stored positions of default values and if position corresponds with one of the values then say 'no'
		if ( (row-1) == defaultRow[i] && (col-1) == defaultCol[i] ) {
			cout << "That's a default value - you can't erase that." << endl;
		} else { //otherwise allow the user to insert value 
			if ( checkRow( value, row ) ) { //if row is clear
				if ( checkCol( value, col ) ) { //if column is clear
					if ( checkGrid( value, row, col ) ) { //if grid is clear
						insertValue( value, row, col ); //place value
						cout << "Value was successfully placed at row: " << row << " and column: " << col << endl;
					}
				}
			} else {
				cout << "Sorry, that's not a valid position since the value overlaps with a pre-existing value on the board. Try again!" << endl << endl;
			}
		}
	}

}

template <typename T>
void Puzzle<T>::eraseValue( int row, int col ) { //erases the value at the position 
	
	int i;

	// vector<T>::const_iterator i = col; //make an iterator so that program can go through each element of the vector and print it out

	//if the user tries to erase default cells, then don't let them
	for ( i=0; i<defaultRow.size(); i++ ) { //loop through stored positions of default values and if position corresponds with one of the values then say 'no'
		if ( (row-1) == defaultRow[i] && (col-1) == defaultCol[i] ) {
			cout << "That's a default value - you can't erase that." << endl;
		} else { //otherwise allow the user to erase value
			puzzleVector[row-1].erase(col-1); //erase the value at the given position
			cout << "The value was erased." << endl;
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
			if ( puzzleVector[i].getValue(j)==0 ) {
				cout << "One of the squares is blank. Please make sure you fill out the whole puzzle." << endl;
				return true; //found an empty spot
			}
		}
	}

	return false; //all spots are filled
}





