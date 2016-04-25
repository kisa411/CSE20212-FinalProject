#ifndef CARDDECK_H
#define CARDDECK_H

#include<iostream>
#include<deque>
using namespace std;

//This class is meant to create a deck of cards and contains functions within it 
//to manipulate the deck of cards
class CardDeck {

   friend ostream &operator<<(ostream &, CardDeck &); //overload <<, prints cards in order 

   public:
      CardDeck(int f=52); //constructor, 52 is fallback value
      int getSize();  //returns size of current deck using size() function
      void shuffle();  //shuffles cards using random_shuffle algorithm of STL
      int inOrder();   //returns 1 if elements in non decreasing order, else return 0
      void printReverse();  //prints cards in reverse order
      int monkeyShuffle();  
      int draw();  //draw card from top and remove from cards

   private:
      deque<int> cards;    //whole deck of cards

};

#endif
