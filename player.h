/* Emily Koh
FCII Final Project
Spring 2016
Player Class
*/
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;

class Player {

public:
	Player(); //default constructor
	changePoints( int change ); //change the player's total points 
	int getPoints(); //accessor method for player's points
	void move(); //function that allows the player to move 

private:
	int points; 

};


#endif