#include <iostream>
#include <string>
#include "singaporeanMathPuzzle.h"
#include "player.h"
using namespace std;

SingaporeanPuzzle::SingaporeanPuzzle() { //default constructor
	points = 0; //set initial value of points to be 0
}

void SingaporeanPuzzle::displayPuzzle() {
	//this is the robber speaking
	cout << "Boo! Finally caught you! If you want to escape from me without any conseqences then you need to be able to prove to me that you're smart enough to solve this brainteaser. If not, then I'm going to steal some of your ingredients! Are you ready? Here's the question!" << endl;

	//brainteaser
	cout << "My friends Emily and Borah want to know when Luis' birthday is. Luis gives them a list of 10 possible dates." << endl;
	cout << "May 15, May 16, May 19" << endl;
	cout << "June 17, June 18" << endl;
	cout << "July 14, July 16" << endl;
	cout << "August 14, August 15, August 17" << endl;
	cout << "Luis then tells Emily and Borah separately the month and day of his birthday respectively.\n Borah:    I don't know when Luis' birthday is, but I know that Emily does not know too.\n Emily:    At first I didn't know when Luis' birthday is, but I know now.\n Borah:    Then I also know when Luis' birthday is." << endl;
	cout << "So when is Luis' birthday? (Please input the answer in the format MONTH DD)." << endl;
}

int SingaporeanPuzzle::playPuzzle() { //returns the amount of points player should get
	string correct = "july 16";
	string answer;
	Player player1; //create an instance of Player class
	int tryNumber = 1; 

	for ( tryNumber=1; i<=3; i++ ) {
		cout << "What is your answer?" << endl;
		cout << "Answer :";
		cin >> answer;
		for ( int j=0; j<answer.length(); j++ ) {
			answer = tolower(answer); //make the answer lower-case
		}
		if ( answer.compare(correct)==0 ) { //user's answer matches the correct answer
			cout << "Congratulations! You got it correct!";
			cout << explanation....;
			if ( tryNumber == 1 ) { //got the answer on the first try
				cout << "You got it correct on your first try, so I won't steal anything from you this time!" << endl;
				player1.changePoints(-points);
			} else ( tryNumber == 2 ) { //got the answer on the second try
				cout << "You got it correct but on your second try - for wasting my time I'm going to take some stuff from you!" << endl;
				cout << "Oh no! The robber stole 30 points worth of ingredients from your bag!" << endl;
				points+=30;
				player1.changePoints(-points);
			} else ( tryNumber == 3 ) { //got the answer on the third try
				cout << "You got it correct but on your third try - for wasting my time I'm going to take some stuff from you!" << endl;
				cout << "Oh no! The robber stole 60 points worth of ingredients from your bag!" << endl;
				points+=60;
				player1.changePoints(-points);
			}
		}
	}
	//if player is unable to solve the puzzle in 3 tries, 
	cout << "You're taking too long to come up with the correct answer! For wasting so much of my time I'm going to steal a lot of stuff from you!" << endl;
	cout << "Oh no! The robber stole 100 points worth of ingredients from your bag!" << endl;
	points+=100;
	player1.changePoints(-points);

}






