#include <iostream>
#include <deque>
#include <vector>
#include <algorithm> //for shuffle() function
#include <ctime> //for time() function
#include <cstdlib> //for srand() function
#include <string>
#include "cardDeck.h"

using namespace std;

void playBlackJack() {
	//create an object of class CardDeck
	CardDeck blackjack(52); //has 52 cards

	//initialize all the necessary variables
	int playerWins=0, dealerWins=0, playerTotal=0, dealerTotal=0;
	int size = blackjack.getSize(); //store the initial number of cards in the deck(should be 52)
	int choice, card, dealerPlay = 1; //0 = no, 1 = yes
	string hitorstand = "hit"; //start with hit

	cout << "Would you like to play a game of blackjack? 1 for yes and 0 for no." << endl;
	cin >> choice;

	while ( choice == 1 ) {
		blackjack.shuffle(); //shuffle the deck so that they're in random order
		playerTotal = 0; //reset player total
		dealerTotal = 0; //reset dealer total
		while ( size>=15 ) { //while there are 15 or more cards, play the game
		
		 	if ( hitorstand == "hit" ) { //player's turn - if they say stand then they would no longer be able to get a card
				card = blackjack.player(); //give the player a card
				playerTotal += card; //add the card's value to the player's total
				cout << "Your total is: " << playerTotal << endl;
				if ( playerTotal > 21 ) {
					cout << "Sorry, your total went over 21. You lose!" << endl;
					break;
				}
				size--; //decrease the number of cards in the deck by one
			} 
			//dealer's turn - automatically gets a card unless value goes up to 17 or greater
			if ( dealerPlay == 1 ) {
				card = blackjack.dealer(); //give the dealer a card
				dealerTotal += card;
				cout << "The dealer total now is " << dealerTotal << endl;
				size--;
				cout << "The dealer has received a card." << endl;
				if (dealerTotal >= 17 ) { //if the dealer's total reaches 17 or higher then they stop
					dealerPlay = 0;
					//cout << "The dealer is no longer taking any cards." << endl;
				} 
			} 
			cout << "Would you like to hit or stand? Please put either \"hit\" or \"stand\" " << endl;
			cin >> hitorstand; 
			if ( hitorstand == "stand" || hitorstand == "hit" ) {
				if ( dealerPlay == 0 && hitorstand == "stand" ) {
					break; //if player stands and the dealer is also not taking any more cards, finish the game
				} else if ( dealerPlay == 1 && hitorstand == "stand" ) {
					continue; //if player stands but the dealer is taking more cards, then continue the game so that the dealer can take a card
				}
				continue; //if the player hits then continue the game
			}
			else {
				cout << "Sorry, could not process input. Please put either \"hit\" or \"stand\" " << endl;
				cin >> hitorstand; 
			}
		}

		if ( (size < 15 && dealerPlay == 1) || (size < 15 && hitorstand == "hit") ) { //if there's less than 15 cards and the dealer is still receiving cards or the player wants to get another card
			cout << "The deck has less than 15 cards now, would you like to continue playing? Put in 1 for yes or 0 for no." << endl;
			cin >> choice;
			//if the deck goes below 15 cards, "open" a new deck
			if ( choice == 1 ) {
				blackjack.reset();
				dealerPlay == 1; 
				hitorstand = "hit";
			} else if ( choice == 0 ) { //player does not want to play with a new deck
				cout << "Another game will not be started." << endl;
			}
		}

		//announce the results of this round
		if ( playerTotal > dealerTotal ) {
			if ( playerTotal <= 21 ) { 
				cout << "The player has won this round. Congratulations!" << endl;
				playerWins++;
			} else { 
				cout << "Sorry, the dealer won this round." << endl; 
				dealerWins++;
			}
			cout << "You had: " << playerTotal << " and the dealer had: " << dealerTotal << endl << endl;
			choice = 1; //this starts a new game 
		} else if ( dealerTotal > playerTotal ) {
			if ( dealerTotal <= 21 ) {
				cout << "The dealer has won this round. The dealer's total was: " << dealerTotal << endl;
				dealerWins++;
			} else {
				cout << "The player has won this round! Congratulations!" << endl;
				playerWins++;
			}
			cout << "You had: " << playerTotal << " and the dealer had: " << dealerTotal << endl << endl;
			choice = 1; //this starts a new game
		} else if ( playerTotal == dealerTotal ) {
			cout << "This round was a tie. The totals for both the player and the dealer were: " << playerTotal << endl;
			cout << "You had: " << playerTotal << " and the dealer had: " << dealerTotal << endl << endl;
			choice = 1; //this starts a new game
		}

		cout << "If you would like to quit playing blackjack, then please put '0'. If you would like to continue playing then please put '1'." << endl;
		hitorstand = "hit";
		dealerPlay = 1;
		cin >> choice; //if 1, then a new game of blackjack will be started. If 0, then the game will end. 
	}

	cout << "The game has ended. The total number of wins for the player was: " << playerWins << " and the total number of wins for the dealer was: " << dealerWins << "." << endl;
	cout << "Thank you for playing! :) " << endl;
}

int main () {
	
	srand( time(0) ); //changes the seed number for the shuffle randomly - using time() allows for really random numbers since now the numbers coming out of the srand() function are based off the time 

	CardDeck deck1(10); //instantiate an object of class cardDeck

	int size = deck1.getSize(); //get the size of the object
	cout << "The size of the deck is: " << size << endl;

	if( deck1.inOrder() == 1 ) { //check to see if deck is in order or not
		cout << "The deck is in non-decreasing order." << endl << endl;
	} else {
		cout << "The deck is not in non-decreasing order." << endl << endl;
	}

	cout << "Here's the deck in reverse: " << endl;
	deck1.printReverse(); //print out the cards in reverse order
	cout << endl;

	cout << "Here's the deck before shuffling: " << deck1 << endl; //print out cards before shuffle

	deck1.shuffle(); //shuffle the deck into a random order

	cout << "Here's the deck after shuffling: " << deck1 << endl; //print out cards after shuffle


	if( deck1.inOrder() == 1 ) { //check to see if deck is in order or not
		cout << "The deck is in non-decreasing order." << endl << endl;
	} else {
		cout << "The deck is not in non-decreasing order." << endl << endl;
	}

	deck1.monkeySort();



	/*BLACKJACK GAME*/
	playBlackJack();

	return 0;
}





