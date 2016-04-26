/* Put Together by Luis Prieb
 * Some code has been borrowed from LazyFoo to develop this class
 * This class wrapps the SDL library to easily initialize SDL
 */

#ifndef SDL_WIN_WRAP
#define SDL_WIN_WRAP

#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class SDL_Win_Wrap
{
	public:
	SDL_Win_Wrap(int nScreenWidth = 640, int nScreenHeight = 480); // Constructor
	~SDL_Win_Wrap(); // Destructor
	int getScreenWidth(); 
	int getScreenHeight();
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	bool init(); //Starts up SDL and creates window
	void close(); //Frees media and shuts down SDL 
	SDL_Window* getWindow(); // Returns a pointer to the window created by class
	SDL_Renderer* getRenderer(); // Returns a pointer to the Renderer created by the class
	//The window we'll be rendering to
	SDL_Window* gWindow ;

	//The window renderer
	SDL_Renderer* gRenderer;
};

#endif
