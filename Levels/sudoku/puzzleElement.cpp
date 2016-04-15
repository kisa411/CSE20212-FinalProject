#include "puzzleElement.h"

puzzleElement::puzzleElement()
{
	value = '0';
	isConstant = 0;
}

void puzzleElement::setValue(int c)
{
	value = c;
}

int puzzleElement::getValue()
{
	return value;
}

bool puzzleElement::getIsConstant()
{
	return isConstant;
}

void puzzleElement::setAll(char c, bool nIsConstant)
{
	setValue(c);
	isConstant = nIsConstant;
}
