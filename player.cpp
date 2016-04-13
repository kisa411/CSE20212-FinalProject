/* Emily Koh
FCII Final Project
Spring 2016
Player Class
*/
#include <iostream>
#include "player.h"
using namespace std;

Player::Player() { //default constructor
	points = 0; //set initial amount of points to 0
}

void Player::changePoints( int change ) { //change must be negative for subtraction, positive for addition
	points+=change;
}
 
int Player::getPoints() { //accessor method for player's points
	return points;
}

void Player::setGender( string g ) {
	gender = g;
}