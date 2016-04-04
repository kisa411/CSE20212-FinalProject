#include "puzzle.h"

int main(void)
{
	SDL_Win_Wrap window_instance;
	Puzzle tPuzzle("medium.txt", window_instance.getWindow(), window_instance.getRenderer(), \
		window_instance.getScreenWidth(), window_instance.getScreenHeight());
	
	tPuzzle.interactive();
}
