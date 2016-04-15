#ifndef BOAT_H
#define BOAT_H

#include<iostream>
#include"texture.h"
#include"sdl_win_wrap.h"
#include"stdio.h"
#include"Rivercrossing.h"

class Boat{

   public:
      //dimensions of boat
      static const int BOAT_WIDTH = 60;
      static const int BOAT_HEGHT = 40;

      //max axis velocity of dot
      static const int BOAT_VEL =10;

      //initialize boat constructor
      Boat();

      //takes key presses and andjusts the dot's velocity
      void handleEvent(SDL_Event& e);

      //move boat
      void move();

      //show boat on screen
      void render();

      //get and set functions
      void setmVelX(int);
      int getmVelX();
      int getBOAT_VEL();

   private:
      //x and y offsets of dot
      int mPosX, mPosY;

      //velocity of dot
      int mVelX, mVelY;

};

#endif
