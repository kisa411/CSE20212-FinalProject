/* Emily Koh
FCII Final Project
Spring 2016
Hangman Class
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <ctype.h>
#include "hangman.h"
using namespace std;

Hangman::Hangman() { //constructor
	points = 300; //set default point value as 300, and for each category of guesses the player takes to solve the puzzle deduct 50 points - player gets 12 guesses for letters to get the word right
}
 
int Hangman::playPuzzle() { //play the puzzle

	cout << "On the side of the road, you see a cat hanging for dear life on a tree! You can help the cat come down the tree only if you're able to solve this hangman puzzle in twelve guesses. Hurry!" << endl;

	int guess=0, loop=1, tries=12;
	string letter;
	string word = ("PUFFERFISH"); //answer to hangman puzzle
	string display = "_ _ _ _ _ _ _ _ _ _"; //if user gets a letter right, then the letter will show; if not then it remains an "_"

	//word to solve is: pufferfish
	while ( tries>=0 ) {
		cout << "You have " << tries << " guess(es) left!" << endl;
		guess++; //increment the number of guesses the player takes to solve the puzzle
		tries--; //decrement the number of tries the player has to solve the puzzle

		cout << "Here's the word before your guess: " << display << endl;
		cout << "What letter would you like to try? Please only use capital letters." << endl;
		cin >> letter;
		letter = ::toupper( letter ); //standardize user input to capital letters

		while ( word.find(letter) != word.end() ) { //look for the letter in the word
			int letterPosition = word.find(letter);
			word[letterPosition] == "."; //change the letter to . so that it won't be found again
			display[letterPosition] = letter; //display the letter in the hangman game
			word.find(letter);
		}


		cout << "Here's the word after your guess: " << display << endl << endl;

		if ( display.find("_")==display.end() ) { //underscores no longer exist in the display string, the word was completed, hangman puzzle was solved
			cout << "You solved the puzzle! Congrats! Now let's go save that cat!" << endl;
		} else if ( tries==0 ) { //player has run out of tries
			cout << "This was your last chance to guess a letter but you weren't able to solve the hangman puzzle! :(" << endl;
		}

	}

	if ( guess>=1 || guess<9 ) { //player receives quality sushi (1~8)
		cout << "Wow! You got the word right in less than 9 guesses! You were able to quickly save the cat and the cat was so impressed with you he gave you some A-grade quality sushi for your recipe!" << endl;

		//no deduction in points
		points = 300;

		//display picture
		//TODO

	} else if ( guess>=9 || guess<11 ) { //player receives raw fish (9~10)
		cout << "Wow! You were able to solve the puzzle in less than 11 guesses! You were able to save the cat and the cat was pretty happy with you so he gave you a raw fish for your recipe!" << endl;

		//50 point deduction in points
		points = 250;

		//display picture
		//TODO

	} else if ( guess>=11 || guess <=12 ) { //player receives fish bones (11~12)
		cout << "Hm...well you were able to solve the puzzle in less than 13 guesses and were able to save the cat before he fell off the tree. The cat gave you some of his leftover fish bones partly because he was grateful but mostly out of relief that he hadn't fallen completely out of the tree." << endl;

		//100 point deduction in points
		points = 200;

		//display picture
		//TODO

	} else {
		cout << "You took so long in solving the puzzle the cat fell off the tree and was too angry to give you anything cool except for some scratches on your face. Sorry! :( " << endl;
	}

	return points; //this is the amount of points to add to the player's total points

}







