#include "cryptography.h"
#include "sdl_win_wrap.h"

int main(void)
{	
	SDL_Win_Wrap window_instance;
	crypto game(window_instance.getWindow(), window_instance.getRenderer());
	game.play();
}
