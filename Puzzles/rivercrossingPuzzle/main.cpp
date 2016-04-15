#include <iostream>
#include"Rivercrossing.h"
#include"texture.h"
#include"sdl_win_wrap.h"

int main() {

   SDL_Win_Wrap window;
   Rivercrossing game(window.getWindow(), window.getRenderer());
   
   //LTexture texture(window.gWindow, window.gRenderer, window.getScreenWidth(), window.getScreenHeight());

   game.play();

}

