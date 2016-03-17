#ifndef CARDDECK_H
#define CARDDECK_H

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm> //for shuffle() function
#include <ctime> //for time() function
#include <cstdlib> //for srand() function

using namespace std;


class CardDeck {

friend ostream &operator<<( ostream &output, CardDeck &deck ); //overload << operator so that cout << board can actually display the board - parameters: what array to use to store the output, what class to act on (goes before public or private categories)

public:
	CardDeck( int n=52 ); //constructor
	int getSize(); //returns the size of the current deck of cards
	int inOrder(); // returns 1 if the elements are in nondecreasing order (i.e., A[i] <= A[i + 1] for all cards in the deck), 0 otherwise.
	void shuffle(); //shuffles the cards using random_shuffle algorithm of STL
	void printReverse(); //prints out all the cards in reverse order
	void monkeySort(); //do the monkeysort function
	int player(); //deal function for blackjack (for player)
	int dealer(); //deal function for blackjack (for dealer)
	void reset(); //clean up the old deck and then create a new deck

private:
	deque<int> cardDeque;
	int size;
	vector<CardDeck* > cardDecks; //make a vector of CardDeck classes
	
};


#endif