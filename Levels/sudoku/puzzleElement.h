/* Luis Prieb
 * This class is an element in the vector holding the 2-D puzzle
 * It stores a value and it stores whether the value can be changed or not by the user
 */

#ifndef PUZZLEELEMENT_H
#define PUZZLEELEMENT_H

using namespace std;

class puzzleElement
{
	public:
	puzzleElement();
	void setValue(int); // Sets value in that location
	int getValue(); // Returns value stored in that position
	void setAll(char, bool); // Sets a value and sets whether its constant or not
	bool getIsConstant(); 
	
	private:
	bool isConstant; // stores whether this a number set by the puzzle or modifiable by the user
	int value;
};


#endif

