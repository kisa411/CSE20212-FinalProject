#include<iostream>
#include<deque>
#include"Blackjack.h"
#include"texture.h"
#include"sdl_win_wrap.h"

using namespace std;

int main() {

   SDL_Win_Wrap window;
   Blackjack myGame(52, window.getWindow(), window.getRendere());

   myGame.play();

}

