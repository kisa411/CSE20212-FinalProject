#ifndef PUZZLEELEMENT_H
#define PUZZLEELEMENT_H

using namespace std;

class puzzleElement
{
	public:
	puzzleElement();
	void setValue(int); // Returns true if position could be placed.
	int getValue();
	void setAll(char, bool);
	bool getIsConstant(); 
	void operator =(char);
	void solve();
	
	private:
	bool isConstant; // Allows you to change or not the value if it is part of the puzzle
	int value;
};


#endif

