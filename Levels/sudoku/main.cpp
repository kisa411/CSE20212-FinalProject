#include <iostream>
#include <fstream> //for file input and output
#include <vector>
#include <string>
#include <cstring>
#include "puzzle.h"

using namespace std;

int main ( int argc, char *argv[] ) { //read in the name of the file from command line (argc = number of words in command line, argv[] = stores the actual words used in command line)
	int type, loop = 0, checked = 0;
	string file;
	ifstream filename; //create a file handle

	//set up for reading from the textfile
	while ( loop == 0 ) {
		if ( argc!=2 ) {
			cout << "You forgot to put in the name of the file in the command line." << endl;
			loop = 1;
			break;
		} else {
			//argv[1] is the name of the file to open
			filename.open( argv[1] ); //open the file that was input in command line
			if ( !filename.is_open() ) { //if the file is not opened correctly
				cout << "The file couldn't be opened." << endl;
			} else {
				cout << "Proceeding to read values from file..." << endl;
				file = argv[1]; //store the name of the file in a separate variable so that constructor can use it
				checked = 1; //file was successfully opened, continue
				break;
			}
		}

	}

	cout << "Is the puzzle for a sudoku or a wordoku?\n 1. Sudoku \n 2. Wordoku \n " << endl;
	cin >> type;
	

	if ( checked == 1 ) {
		if ( type == 1 ) {//instantiate puzzle object - sudoku object
			Puzzle<int> sudoku( file );
			sudoku.playPuzzle();
			loop = 0;
		} else if ( type == 2 ) { //instantiate puzzle object - wordoku object
			Puzzle<char> wordoku( file );
			wordoku.playPuzzle();
			loop = 0;
		}
	}


	return 0;
}