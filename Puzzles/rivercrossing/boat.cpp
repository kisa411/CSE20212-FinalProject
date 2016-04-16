#include"boat.h"
#include<iostream>
#include"sdl_win_wrap.h"
#include"texture.h"

Boat::Boat() {

   //boat will only move left and right(along x axis)
   //initialize offsets
   mPosX = 100;
   mPosY = 0;

   //initialize velocity
   mVelX = 0;

}

void Boat::setmVelX(int x) {

   mVelX=x;

}

int Boat::getmVelX() {

   return mVelX;

}

int Boat::getBOAT_VEL() {

   return BOAT_VEL;

}

/*void Boat::handleEvent(SDL_Event& e) {

   //if a key was pressed
   if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
      //change velocity
      switch(e.key.keysym.sym) {
	 case SDLK_LEFT: 
	    mVelX -= BOAT_VEL; 
	    break;
	 case SDLK_RIGHT: 
	    mVelX += BOAT_VEL;
	    break;
      }
   }
   else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
      //change velocity
      switch(e.key.keysym.sym) {
	 case SDLK_LEFT:
	    mVelX += BOAT_VEL;
	    break;
	 case SDLK_RIGHT:
	    mVelX -= BOAT_VEL;
	    break;
      }
   }

}*/

void Boat::move() {

   //move boat left or right
   mPosX += mVelX;

   //if dot went too far left or right
   if ((mPosX<100) || (mposX + BOAT_WIDTH > (SCREEN_WIDTH-100))) {
      //move back
      mPos -=mVelX;
   }

}

void Boat::render() {

   //show boat
   gDotTexture.render(mPosX, mPosY);

}


