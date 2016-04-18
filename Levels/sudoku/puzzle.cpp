#include "puzzle.h"
#include "sdl_win_wrap.h"
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <string.h>

void Puzzle::setCheck()
{
	for(int i = 0; i < 10; i++)
	{
		check.push_back(i); // convert int to char
	}
}


Puzzle::Puzzle(string fileName, SDL_Window* ngWindow, SDL_Renderer* ngRenderer):
	gSpriteSheetTexture(ngWindow, ngRenderer), 
	gBackgroundTexture(ngWindow, ngRenderer), 
	gSelectorTexture(ngWindow, ngRenderer), 
	messageTextTexture(ngWindow, ngRenderer),
	timeTextTexture(ngWindow, ngRenderer),
	gWindow(ngWindow), gRenderer(ngRenderer)
	
{
	bodyFont = TTF_OpenFont("adam-warren-pro.regular.ttf", 20);
	titleFont = TTF_OpenFont("adam-warren-pro.regular.ttf", 24);
	timeFont = TTF_OpenFont("adam-warren-pro.regular.ttf", 16);
	if(bodyFont == NULL || titleFont == NULL || timeFont == NULL)
	{
		cout << "Could not load font" << endl;
		correctlyInitialized = false;
		return;
	}
	messageTextTexture.setFont(bodyFont);
	timeTextTexture.setFont(timeFont);
	
	fontColor = {0,0,0}; // Black
	
	LTexture* text_buffer;
	
	text_buffer = new LTexture(ngWindow, ngRenderer, titleFont);
	instructions.push_back(text_buffer);
	for(int i = 0; i < 10 ; i++)
	{
		text_buffer = new LTexture(ngWindow, ngRenderer, bodyFont);
		instructions.push_back(text_buffer);
	}
	correctlyInitialized = true;
	
	// Store Window Dimensions
	SDL_GetWindowSize(ngWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	// Open File
	FILE *puzzleFile;
	
	if((puzzleFile = fopen(fileName.c_str(), "r")) == NULL)
	{
		cout << "Error: Could not open file: " << fileName << endl << endl;
		correctlyInitialized = false;
		return;
	}
	
	vector <puzzleElement> buffer;
	puzzleElement singleContainer;
	int c;
	
	setCheck();
	
	// Read in puzzle from file
	for(int row = 0; row< 9; row++)
	{
		buffer.clear();
		c = fgetc(puzzleFile);
		for(int col = 0; c != '\n' && c != EOF; col++)
		{
			if(!checkAllowed(c)) // Check if value is appropriate
			{
				cout << "Wrong value in file" << endl;
				return;
			}
			
			if(c == '0')
			{
				singleContainer.setAll(c - '0', 0); // This makes the value not constant
				buffer.push_back(singleContainer);
			}
			else
			{
				singleContainer.setAll(c - '0', 1); // This makes the value constant
				buffer.push_back(singleContainer);
			}
			c = fgetc(puzzleFile); // Catch space
			if(c == ' ') // Catches any extra space at the end of the line
			{
				c = fgetc(puzzleFile);
			}
		}
		thePuzzle.push_back(buffer);
	}
	if(thePuzzle.size() != 9)
	{
		cout << " File is not formatted correctly" << endl;
		correctlyInitialized = false;
		return;		
	}
	
	// Initialize Other Variables
	selector.x = 0;
	selector.y = 0;
	if(!loadMedia())
	{
		correctlyInitialized = false;
		return;
	}
	
	if(!setInstructions())
	{
		correctlyInitialized = false;
		return;
	}
}


bool Puzzle::setInstructions()
{
	
	if((instructions[0]->loadFromRenderedText("INSTRUCTIONS", fontColor)) &&
		(instructions[1]->loadFromRenderedTextWrapped("Move Selector Using Arrows", fontColor, 192)) &&
		(instructions[2]->loadFromRenderedTextWrapped("Press a number key to set value", fontColor, 192)) &&
		(instructions[3]->loadFromRenderedTextWrapped("Remove entry by pressing 0", fontColor, 192)))
		return true;
	return false;
	
	
	
}

Puzzle::~Puzzle()
{
	gSpriteSheetTexture.free();
	gSelectorTexture.free();
	gBackgroundTexture.free();
	messageTextTexture.free();
	timeTextTexture.free();
	for(auto& x: instructions) delete x;
	
}

bool Puzzle::checkCol(int value, int col)
{
		for(int i = 0; i < 9; i++)
		{
			if(value == thePuzzle[i][col].getValue())
				return false;
		}
		return true;
}

bool Puzzle::checkRow(int value, int row)
{
		for(int i = 0; i < 9; i++)
		{
			if(value == thePuzzle[row][i].getValue())
				return false;
		}
		return true;
}

bool Puzzle::checkSquare(int value, int row, int col)
{
		// Determine Square
		int i, j;
		
		int rowStart = ((row)/3)*3; // Determines what is the first row of the square in 0-8 range
													// Truncates value and then scales it again
		int colStart = ((col)/3)*3;
		
		for(int i = rowStart; i < (rowStart+3); i++)
		{
			for(int j = colStart; j< (colStart+3); j++)
			{
				if(value == thePuzzle[i][j].getValue())
					return false;
			}
		}
		return true;
}

bool Puzzle::checkValue(int value, int row, int col)
{
	if(value == 0)
		return true;
	else if(checkCol(value, col) && checkRow(value, row) && checkSquare(value, row, col))
		return true;
	else
		return false;
}

bool Puzzle::checkSolved()
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j <9; j++)
		{
			if(thePuzzle[i][j].getValue() == 0)
			{
				return false;
			}
		}
	}
	return true;
}

int Puzzle::interactive()
{
	if(!correctlyInitialized)
	{
		cout << "Sudoku was not initialized correctly. Cannot play" << endl;
		return;
	}
	
	int value = 'a'; // dumb value to start loop
	int row;
	int col;
	bool gameover = false;
	SDL_Event e;
	bool changeValue;
	bool giveUp;
	time_t start, current;
	int min;
	int sec;
	int tot_sec;
	
	time(&start);
	
	while(!gameover && !giveup)
	{
		changeValue = false;
		time(&current);
		tot_sec = difftime(current, start);
		min = tot_sec/60; // Truncates
		sec = tot_sec % 60; // Mods
		display(min, sec);
		manageEvents(e, value, gameover, changeValue, giveUp);
		
		if(changeValue)
		{
			if( thePuzzle[selector.y][selector.x].getIsConstant())
			{
				updateMessage("Sorry! You can't change the puzzle!");
			}
			else if (checkValue(value, selector.y, selector.x))
			{
				thePuzzle[selector.y][selector.x].setValue(value);
			}
			else
			{
				updateMessage("Value cannot be placed there");
			}
			if(checkSolved())
			{
				gameover = true;
				updateMessage("Congratulations! You solved the puzzle!");
			}
		}
	}
	
	if(giveUp)
	    clear();
	    solve();
	    displayGiveUpEnding();
	else
	    displayRegularEnding();
	if(min < 11 && !giveUp)
	    return(100 - min*10);
	else
	    return 0;
}


void Puzzle::display(int min, int sec)
{
	int num;
	int corner_x = 12;
	int corner_y = 9;
	double box_w =39.8;
	double box_h = 39.334;
	SDL_RenderClear( gRenderer );
	// Render Background
	gBackgroundTexture.render(0,0, NULL);
	
	// Render Text
	displayInstructions();
	displayMessage();
	displayTime(min, sec);
	
	// Render Numbers on Screen
	for(int row = 0; row < 9; row++)
	{
		for(int col = 0; col < 9; col++)
		{
			num = thePuzzle[row][col].getValue();
			if(num != 0)
			{
			    if(thePuzzle[row][col].getIsConstant())
			    {
				    gSpriteSheetTexture.render((int)(corner_x + (box_w+5.0)*col + 2), 
				        (int)(corner_y+(box_h+6.0)*row + 1), (int)box_w, (int)box_h, &gSpriteClipsRed[num]);
				}
				else
				{
				    gSpriteSheetTexture.render((int)(corner_x + (box_w+5.0)*col + 2), 
				        (int)(corner_y+(box_h+6.0)*row + 1), (int)box_w, (int)box_h, &gSpriteClipsBlue[num]);
				}
			}
			//cout << (int)(corner_y+(box_h+6.0)*row) <<":"<<row<<":"<<col<<endl;
			
		}
	}
	// Render Selector
	gSelectorTexture.render((int)(corner_x + (box_w+5.0)*selector.x), (int)(corner_y + (box_h+6.0)*selector.y), 42, 43, NULL);
	
	// Update Screen
	SDL_RenderPresent( gRenderer );
}

bool Puzzle::checkAllowed( int c ) // test if value is in the string of possible chars
{
	bool isThere = 0;
	int size =check.size();
	c = c - '0';
	
	for(int i = 0; i < size; i++)
	{
		if (check[i] == c)
		{
			isThere = 1;
		}
	}
	return isThere;
}

int Puzzle::singleton() // Checks whether a value is only possible in one of the boxes in a row, col, or square
{
	int row, col, inserts, test_num, count;
	int sqrow, sqcol;
	int rightRow, rightCol;
	
	
	inserts=0;
	
	// Check in Rows
	for(row = 0; row < 9; row++)
	{
		for(test_num = 1; test_num < 10; test_num++)
		{
			count = 0;
			for(col = 0; col < 9; col++)
			{
				if(thePuzzle[row][col].getValue() == '0') // Check that location is empty
				{
					if(checkValue(test_num + '0', row, col))
					{
						count++;
						// If there is only one, the following will contain the right position
						rightRow=row;
						rightCol=col;
					}
				}
			}
			if(count == 1) // If only one square can contain the tested number, place is there.
			{
				thePuzzle[rightRow][rightCol].setValue(test_num + '0');
				inserts++;
			}
		}
	}
	
	// Check in Columns
	for(col = 0; col < 9; col++)
	{
		for(test_num = 1; test_num < 10; test_num++)
		{
			count = 0;
			for(row = 0; row < 9; row++)
			{
				if(thePuzzle[row][col].getValue() == '0') // Check that location is empty
				{
					if(checkValue(test_num + '0', row, col))
					{
						count++;
						// If there is only one, the following will contain the right position
						rightRow = row;
						rightCol = col;
					}
				}
			}
			if(count == 1)
			{
				thePuzzle[rightRow][rightCol].setValue(test_num + '0');
				inserts++;
			}
		}
	}
	int rowmax, rowmin;
	int colmax, colmin;
	
	// Check in Square
	for(sqrow=0; sqrow < 3; sqrow++)
	{
		for(sqcol=0; sqcol < 3; sqcol++)
		{
			rowmin = 3*sqrow;
			rowmax = rowmin + 3;
			colmin = 3*sqcol;
			colmax = colmin + 3;
			for(test_num = 1; test_num < 10; test_num++)
			{
				count = 0;
				for(row=rowmin; row < rowmax; row++)
				{
					for(col=colmin; col < colmax; col++)
					{
						if(thePuzzle[row][col].getValue() == '0')
						{
							if(checkValue(test_num + '0', row, col))
							{
								count++;
								// If there is only one, the following will contain the right position
								rightRow=row;
								rightCol=col;
							}
						}
					}
				}
				if(count == 1)
				{
					thePuzzle[rightRow][rightCol].setValue(test_num + '0');
					inserts++;
				}
			}
		}
	}
	
	return inserts;
	
}


int Puzzle::single_possibility() // Checks 
{
	int row, col, test_num, count, inserts;
	int rightNum;
	inserts=0;
	
	for(row = 0; row < 9; row++)
	{
		for(col = 0; col < 9; col++)
		{
			count = 0;
			if(thePuzzle[row][col].getValue() == '0')
			{
				for(test_num = 1; test_num < 10; test_num++)
				{
					if(checkValue(test_num + '0', row, col))
					{
						count++;
						// If there is only one number that can be placed, the following will contain the right number after the loop
						rightNum=test_num;
					}
				}
				if(count == 1)
				{
					thePuzzle[row][col].setValue(rightNum + '0');
					inserts++;
				}
			}
		}
	}
	return inserts;
}


void Puzzle::solve()
{
	int inserts;
	do // Do loop until no more insertions are made by any of the algorithms
	{
		inserts = 0;
		inserts += singleton();
		inserts += single_possibility();

	} while (inserts > 0);
	
	if(checkSolved())
	{
		cout << "Here is the solution!" << endl;
	}
	else
	{
		cout << "A solution could not be found" << endl;
		cout << "This is what we got" << endl;
	}
}

vector< vector <int> > Puzzle::getIntVector()
{
	vector< vector <int> > intVector;
	vector<int> buffer;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			buffer.push_back(thePuzzle[i][j].getValue());
		}
		intVector.push_back(buffer);
	}
	return intVector;
}

{
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			gameover = true;
		}
		else if(e.type == SDL_KEYDOWN)
		{
			switch(e.key.keysym.sym)
			{
				case SDLK_UP:
					if(selector.y > 0)
					{
						selector.y--;
					}
					break;
				case SDLK_DOWN:
					if(selector.y < 8)
					{
						selector.y++;
					}
					break;
				case SDLK_LEFT:
					if(selector.x >0)
					{
						selector.x--;
					}
					break;
				case SDLK_RIGHT:
					if(selector.x < 8)
					{
						selector.x++;
					}
					break;
				case SDLK_0:
				case SDLK_KP_0:
					value = 0;
					changeValue = true;
					break;
				case SDLK_1:
				case SDLK_KP_1:
					value = 1;
					changeValue = true;
					break;
				case SDLK_2:
				case SDLK_KP_2:
					value = 2;
					changeValue = true;
					break;
				case SDLK_3:
				case SDLK_KP_3:
					value = 3;
					changeValue = true;
					break;
				case SDLK_4:
				case SDLK_KP_4:
					value = 4;
					changeValue = true;
					break;
				case SDLK_5:
				case SDLK_KP_5:
					value = 5;
					changeValue = true;
					break;
				case SDLK_6:
				case SDLK_KP_6:
					value = 6;
					changeValue = true;
					break;
				case SDLK_7:
				case SDLK_KP_7:
					value = 7;
					changeValue = true;
					break;
				case SDLK_8:
				case SDLK_KP_8:
					value = 8;
					changeValue = true;
					break;
				case SDLK_9:
				case SDLK_KP_9:
					value = 9;
					changeValue = true;
					break;
				case SDLK_q:
					gameover=1;
					changeValue = true;
					break;
				default:
					;
			}
		}
	}
}

bool Puzzle::loadMedia()
{
	int startx = 0;
	int starty = 142;
    int width = 88;
	int height = 104;
	int space = 4;
	//Loading success flag
	bool success = true;

	//Load sprite sheet textures
	if( !gSpriteSheetTexture.loadFromFile( "numbers.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
	{
		//Make Sprite clips from spriteSheet
		for(int i = 0; i < 10; i++)
		{
			gSpriteClipsRed[i].x = startx + width*i + space*i;
			gSpriteClipsRed[i].y = starty;
			gSpriteClipsRed[i].w = width;
			gSpriteClipsRed[i].h = height;
		}
		space = 3;
		starty =336; // Only these Values change. Everything else is the same
		//Make Sprite clips from spriteSheet
		for(int i = 0; i < 10; i++)
		{
			gSpriteClipsBlue[i].x = startx + width*i + space*i;
			gSpriteClipsBlue[i].y = starty;
			gSpriteClipsBlue[i].w = width;
			gSpriteClipsBlue[i].h = height;
		}
	}

	   
	
	if( !gBackgroundTexture.loadFromFile( "sudoku_background.png" ))
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	
	if( !(gSelectorTexture.loadFromFile("selector.png")))
	{
		printf("Failed to load selector\n");
		success = false;
	}

	return success;
}


void Puzzle::displayInstructions()
{
	point text_ref;
	
	text_ref.x = 430;
	text_ref.y = 32;
	
	int current_height = text_ref.y;
	
	instructions[0]->render(text_ref.x, current_height);
	current_height += instructions[0]->getHeight() + 8;
	for(int i = 1; i < 10; i++)
	{
		if(instructions[i] != NULL)
		{
			instructions[i]->render(text_ref.x, current_height);
			current_height += instructions[i]->getHeight() + 4;
		}
	}
}



void Puzzle::displayMessage()
{
	point text_ref;
	text_ref.x = 12;
	text_ref.y = 430;
	
	messageTextTexture.render(text_ref.x, text_ref.y);
}

void Puzzle::updateMessage(string nMessage)
{
	messageTextTexture.free();
	
	messageTextTexture.loadFromRenderedText(nMessage.c_str(), fontColor); 
}

void Puzzle::displayTime(int min, int sec)
{
    char min_str[10];
    char sec_str[10];
    char time_str[10];
    sprintf(min_str, "%i", min);
    if(strlen(min_str) == 1)
    {
        sprintf(min_str, "0%i", min);
    }
    sprintf(sec_str, "%i", sec);
    if(strlen(sec_str) == 1)
    {
        sprintf(sec_str, "0%i", sec);
    }
    sprintf(time_str, "%s:%s", min_str, sec_str);
    timeTextTexture.loadFromRenderedText(time_str, fontColor);
    timeTextTexture.render(430,5);
}

void clear()
{
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            if(!thePuzzle[row][col].getIsConstant())
            {
                thePuzzle[row][col].setValue(0);
            }
        }
    }
}
