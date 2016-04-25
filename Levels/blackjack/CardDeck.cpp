#include <iostream>
#include<deque>
#include<cstdlib>
#include<ctime>
#include<algorithm>

#include"CardDeck.h"
using namespace std;

CardDeck::CardDeck(int f) {

   int i;

   for (i=1; i<=f; i++) {
      cards.push_back(i);
   }

}

int CardDeck::getSize() {

   return cards.size();

}

void CardDeck::shuffle() {

   //time_t t;
   //srand(time(&t));
   random_shuffle(cards.begin(), cards.end());

}

int CardDeck::inOrder() {

   //if cards in increasing order, return 1
   //else, return 0

   int i;

   for (i=0; i<cards.size()-1; i++) {
      if (cards[i]>cards[i+1]) {
         return 0;
      }
   }

   return 1;

}

ostream &operator<<(ostream &output, CardDeck &c) {

   deque<int>::const_iterator i;

   for (i=c.cards.begin(); i!=c.cards.end(); ++i) {
      if (i==c.cards.begin()) {
	 output << *i;
      }
      else {
	 output << ", " << *i;
      }
   }
   
   output << endl;

   return output;

}

void CardDeck::printReverse() {

   deque<int>::const_reverse_iterator r;

   for (r=cards.rbegin(); r!=cards.rend(); ++r) {
      if (r==cards.rbegin()) {
	 cout << *r;
      }
      else {
         cout <<", " << *r;
      }
   }
   cout << endl;

}

int CardDeck::monkeyShuffle() {  //counts number of shuffles needed to get deck back in order

   int count=1;

   shuffle();

   while (inOrder()!=1) {
      shuffle();
      count++;
   }

   return count;

}

int CardDeck::draw() {

   int drawn;

   drawn=cards[0];
   cards.pop_front();

   return drawn;

}
