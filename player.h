#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;

class Player {

public:
	Player(); //default constructor
	changePoints( int change ); //change the player's total points 
	int getPoints(); //accessor method for player's points

private:
	int points; 

};


#endif