#include "puzzle.h"

int main(void)
{
	SDL_Win_Wrap window_instance;
	Puzzle tPuzzle(window_instance.getWindow(), window_instance.getRenderer());
	
	tPuzzle.interactive();
}
