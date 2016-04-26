#include<iostream>
#include<cstdlib>
#include<SDL2/SDL_ttf.h>
#include<string>
#include"../../sharedClasses/sdl_win_wrap.h"
#include"../../sharedClasses/texture.h"
#include"Rivercrossing.h"

using namespace std;

#define wolf 1
#define goat 2
#define cabbage 4

Rivercrossing::Rivercrossing(SDL_Window* ngWindow, SDL_Renderer* ngRenderer): 
   gBackgroundTexture(ngWindow, ngRenderer), \
   gSheep(ngWindow, ngRenderer), \
   gWolf(ngWindow, ngRenderer), \
   gCabbage(ngWindow, ngRenderer), \
   gBoat(ngWindow, ngRenderer), \
   gText(ngWindow, ngRenderer), \
   gInputText (ngWindow, ngRenderer), \
   gWindow(ngWindow), \
   gRenderer(ngRenderer)

{

   //window dimensions
   SDL_GetWindowSize(ngWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);

   end=0;
   start=7;
   onboat=0;
   //1=start position, -1=end position
   position=1;
   numtries=1;

   loadMedia();

}

Rivercrossing::~Rivercrossing() {

   gBackgroundTexture.free();
   gSheep.free();
   gWolf.free();
   gCabbage.free();
   gBoat.free();
   gText.free();

}

void Rivercrossing::reset() {   //reset all values to replay

   end=0;
   start=7;
   onboat=0;
   //1=start position, -1=end position
   position=1;

}

int Rivercrossing::play() {

   SDL_Event e;
   bool change;
   bool changeboat;
   int points;
   string choice;
   bool exit = false;
   int xpos, ypos;
   string disp=" ";

   xpos = 40;
   ypos = 40;

   //initial display
   SDL_RenderClear(gRenderer);
   display();
   //display instructions 
   displayText(xpos, ypos, "As you continue your journey, you run into a farmer who is trying to cross a river. However his boat only holds 1 object besides himself. He wants to take a wolf, sheep, and cabbage accross.\nPress enter to continue\n");

   //click enter to cont
   while (userInput()!=" ") {
      continue;
   }
   //display other intructions
   SDL_RenderClear(gRenderer);
   display();
   displayText(xpos, ypos, "If you leave the wolf and the sheep alone, the wolf will eat the sheep. If you leave the sheep and cabbage alone, the sheep will eat the cabbage. Can you take all three objects across the river successfully?");
  
   //not game over or success
   int game=finished();
   while (game==1 && exit == false) {

      change=false;
      changeboat=false;
      //change is true when position of one of 3 items is changed
      manageEvents(e, change, changeboat, exit);
      if(exit == true) {
      	break;
      }
      //if something changed position, render images again and display
      if (change || changeboat) {
         /*SDL_RenderClear(gRenderer);
 	 display();
	 displayText(xpos, ypos, "If you leave the wolf and the sheep alone, the wolf will eat the sheep. If you leave the sheep and cabbage alone, the sheep will eat the cabbage. Can you take all three objects across the river successfully?");

      }
      //if boat changed, check if game over
      if(changeboat) {*/
	 SDL_RenderClear(gRenderer);
	 display();
	 displayText(xpos, ypos, "If you leave the wolf and the sheep alone, the wolf will eat the sheep. If you leave the sheep and cabbage alone, the sheep will eat the cabbage. Can you take all three objects across the river successfully?");

	 switch (finished()) {
	    case 2:
               SDL_RenderClear(gRenderer);
	       display();
	       displayText(xpos, ypos, "The wolf ate the sheep! Would you like to try again? If you don't help this farmer, you get 0 points! Press y to continue or n to quit, then press enter");
	       //wolf ate goat, game over! ask to try again(click y)
	       choice=userInput();
	       while (choice!=" y" && choice!=" n") {
	   	  choice=userInput();
		  //cout << choice << endl;
	       }

               if (choice==" y") {
		  reset();
		  SDL_RenderClear(gRenderer);
		  display();
	 	  displayText(xpos, ypos, "If you leave the wolf and the sheep alone, the wolf will eat the sheep. If you leave the sheep and cabbage alone, the sheep will eat the cabbage. Can you take all three objects across the river successfully?");
		  numtries++;
		  game=1;
	       }
	       else if (choice==" n") {
		  //convert numtries to string
                  SDL_RenderClear(gRenderer);
		  display();
		  disp="You tried " + to_string(numtries) + " times but couldn't help the farmer! You get no points. Sorry!\nPress enter to continue\n";
		  displayText(xpos, ypos, disp);
		  while (userInput()!=" ") {
		     continue;
		  }

		  game=0;
	       }
	       break;
	    case 3:
               SDL_RenderClear(gRenderer);
	       display();
	       //goat ate cabbage, game over! ask to try again(click y)
	       displayText(xpos, ypos, "The sheep ate the cabbage! Would you like to try again? If you don't help this farmer, you get 0 points! Press y to continue or n to quit, then press enter");
	       //wolf ate goat, game over! ask to try again(click y)
	       choice=userInput();
	       while (choice!=" y" && choice!=" n") {
	   	  choice=userInput();
	       }

               if (choice==" y") {
		  reset();
		  SDL_RenderClear(gRenderer);
		  display();
	 	  displayText(xpos, ypos, "If you leave the wolf and the sheep alone, the wolf will eat the sheep. If you leave the sheep and cabbage alone, the sheep will eat the cabbage. Can you take all three objects across the river successfully?");
		  numtries++;
		  game=1;
	       }
	       else if (choice==" n") {
                  SDL_RenderClear(gRenderer);
		  display();
		  disp="You tried " + to_string(numtries) + " times but couldn't help the farmer! You get no points. Sorry!\nPress enter to continue\n";
		  displayText(xpos, ypos, disp);
		  while (userInput()!=" ") {
		     continue;
		  }

		  game=0;
	       }
	       break;
	    case 0:
               SDL_RenderClear(gRenderer);
	       display();
	       //success!
	       points=100/numtries;
	       disp="The farmer is so thankful for your help! You finished in " + to_string(numtries) + "try/tries, so you get " + to_string(points) + " points!\nPress enter to continue\n";
	       displayText(xpos, ypos, disp);

	       //click enter to cont
	       while (userInput()!=" ") {
		  continue;
	       }

	       if (points<=40) {
		  SDL_RenderClear(gRenderer);
		  display();
		  displayText(xpos, ypos, "The farmer thanks you with his cabbage!\nPress enter to continue\n");

		  //click enter to cont
		  while (userInput()!=" ") {
		     continue;
		  }

	       }
	       else if (points>40 && points <=60) {
		  SDL_RenderClear(gRenderer);
		  display();
		  displayText(xpos, ypos, "The farmer thanks you with some expensive cheese from his goats on the farm!\nPress enter to continue\n");

		  //click enter to cont
		  while (userInput()!=" ") {
		     continue;
		  }

	       }
	       else if (points<=100 && points>61) {
		  SDL_RenderClear(gRenderer);
		  display();
		  displayText(xpos, ypos, "The farmer thanks you with his cabbage, some really nice goat cheese, and a cute wool scarf made from real sheep wool!\nPress enter to continue\n");

		  //click enter to cont
		  while (userInput()!=" ") {
		     continue;
		  }

	       }
	       game=0;
	       break;
	    default:
	       break;
	 }

      }

   }

   return points;

}

string Rivercrossing::userInput() {

   bool enter=false;
   int xpos=40;
   int ypos=40;


   //sdl event handler
   SDL_Event e;

   //set font
   gInputText.setFont(gFont);

   //current input text
   string inputText=" ";
   gInputText.loadFromRenderedText(inputText.c_str(), color);

   //start text input
   SDL_StartTextInput();

   while (!enter) {
      //renderer text flag
      bool renderText = false;

      while (SDL_PollEvent(&e)!=0) {
         if (e.type == SDL_KEYDOWN) {
	    //delete input
	    if(e.key.keysym.sym==SDLK_BACKSPACE && inputText.length()>0) {
	       inputText.pop_back();
	       renderText=true;
	    }
	    //submit input
	    else if (e.key.keysym.sym == SDLK_RETURN) {
	       enter = true;
	       break;
	    }
	 }
	 //read text input
	 else if (e.type == SDL_TEXTINPUT) {
	    //not copy or pasting
	    if (!((e.text.text[0]=='c' || e.text.text[0]=='C') && (e.text.text[0]=='v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
	       inputText += e.text.text;
	       renderText=true;
	    }
	 }
      }

      //if input has been changed and needs to be rendered
      if(renderText) {
	 //if text is not empty then render
	 if (inputText!="") {
	    gInputText.loadFromRenderedText(inputText.c_str(), color);
	 }
	 else {
	    gInputText.loadFromRenderedText(" ", color);
	 }
      }

      gInputText.render(xpos, ypos+gText.getHeight());

      SDL_RenderPresent(gRenderer);
   }

   //stop reading input
   SDL_StopTextInput();

   //return user input
   return inputText;

}


void Rivercrossing::displayText(int x, int y, string message) {

   if (!gText.loadFromRenderedTextWrapped(message.c_str(), color, 500)) {
      printf("Failed to render text!\n");
   }
   gText.render(x, y);
   SDL_RenderPresent(gRenderer);
   
}

int Rivercrossing::finished() {

   //return 0 means finished successfully
   //return 1 means not yet finished but not game over
   //return 2 means wolf ate goat and game over
   //return 3 means goat ate cabbage and game over
   if (end==goat+cabbage+wolf) {
      return 0;
   }
   else if (position==1) {
      if (end==wolf+goat) {
	 return 2;
      }
      else if (end==goat+cabbage) {
	 return 3;
      }
   }
   else if (position==-1) {
      if (start==wolf+goat) {
	 return 2;	 
      }
      else if (start==goat+cabbage) {
	 return 3;
      }
   }


   return 1;

}

void Rivercrossing::display() {
   SDL_RenderClear(gRenderer);

   //Render background
   gBackgroundTexture.render(0, 0, 640, 480, NULL);

   //render boat
   if (position==1) {
      gBoat.render(190, 330, 80, 94, NULL);
      if (onboat==cabbage) {
	 gCabbage.render(15+190, 40+330, 50, 42, NULL);
      }
      else if (onboat==wolf) {
	 gWolf.render(10+190, 20+330, 65, 67, NULL);
      }
      else if (onboat==goat) {
	 gSheep.render(15+190, 40+330, 60, 41, NULL);
      }
   }
   else if (position==-1) {
      gBoat.render(285, 330, 80, 94, NULL);
      if (onboat==cabbage) {
	 gCabbage.render(15+285, 40+330, 50, 42, NULL);
      }
      else if (onboat==wolf) {
	 gWolf.render(10+285, 20+330, 65, 67, NULL);
      }
      else if (onboat==goat) {
	 gSheep.render(15+285, 40+330, 60, 41, NULL);
      }
   }
 
   //render items
   //at start
   if (start == goat + cabbage + wolf) {
      gSheep.render(110, 335, 60, 41, NULL);
      gWolf.render(85, 390, 65, 67, NULL);
      gCabbage.render(20, 345, 50, 42, NULL);
   }
   else if (start == goat + cabbage) {
      gCabbage.render(20, 345, 50, 42, NULL);
      gSheep.render(110, 335, 60, 41, NULL);
   }
   else if (start == goat + wolf) {
      gSheep.render(110, 335, 60, 41, NULL);
      gWolf.render(85, 390, 65, 67, NULL);
   }
   else if (start == wolf+cabbage) {
      gWolf.render(85, 390, 65, 67, NULL);
      gCabbage.render(20, 345, 50, 42, NULL);
   }
   else if (start == goat) {
      gSheep.render(110, 335, 60, 41, NULL);
   }
   else if (start == cabbage) {
      gCabbage.render(20, 345, 50, 42, NULL);
   }
   else if (start == wolf) {
      gWolf.render(85, 390, 65, 67, NULL);
   }

   //at end
   if (end == goat + cabbage + wolf) {
      gSheep.render(450, 340, 60, 41, NULL);
      gWolf.render(410, 385, 65, 67, NULL);
      gCabbage.render(380, 340, 50, 42, NULL);
   }
   else if (end == goat + cabbage) {
      gCabbage.render(380, 340, 50, 42, NULL);
      gSheep.render(450, 340, 60, 41, NULL);
   }
   else if (end == goat + wolf) {
      gSheep.render(450, 340, 60, 41, NULL);
      gWolf.render(410, 385, 65, 67, NULL);
   }
   else if (end == wolf+cabbage) {
      gWolf.render(410, 385, 65, 67, NULL);
      gCabbage.render(380, 340, 50, 42, NULL);     
   }
   else if (end == goat) {
       gSheep.render(450, 340, 60, 41, NULL);     
   }
   else if (end == cabbage) {
       gCabbage.render(380, 340, 50, 42, NULL);  
   }
   else if (end == wolf) {
      gWolf.render(410, 385, 65, 67, NULL);
   }

   //update screen
   SDL_RenderPresent(gRenderer);

}

void Rivercrossing::manageEvents(SDL_Event &e, bool &change, bool &changeboat, bool &exit) {

   int pos;

   while(SDL_PollEvent(&e)) {

	 if(e.type == SDL_QUIT) {
	 	exit = true;
	 }

	 //boat movement with arrow keys
	 //click down once, it will move to opp side
	 else if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
	    switch(e.key.keysym.sym) {
	       case SDLK_RIGHT:
		  //only switch position if at start
		  if (position==1) {
		     position=position*(-1);
		  }
		  changeboat=true;
		  break;
	       case SDLK_LEFT:
		  //only switch position if at end
		  if (position==-1) {
		     position=position*(-1);
		  }
		  changeboat=true;
		  break;
	    }
	 }
	 else if(e.type == SDL_MOUSEBUTTONDOWN) {
            //get mouse position
	    int x, y;
	    SDL_GetMouseState(&x, &y);
	    
	    //check where mouse is
	    pos=mousepos(x, y);

	    switch (pos) {
	       case wolf: //move wolf to boat and move out whatever was in boat if there was anythong
		  drop();
		  pickup('w');
		  change=true;
		  display();
		  break;
	       case goat: //move goat to boat and move out whatever was in boat if there was anything
		  drop();
		  pickup('g');
		  display();
		  change=true;
		  break;
	       case cabbage: //move cabbage to boat and move out whatever was in boat if there was anything
		  drop();
		  pickup('c');
		  display();
		  change=true;
		  break;
	       case 3: //boat, if boat empty, dont to anything, if not empty move whatever is on boat back to land
		  drop();
		  change=true;
		  display();
		  break;
	       case 0:  //default case, dont do anything
		  change=false;
		  break;
	    }
	 }
  }

}
         

int Rivercrossing::mousepos(int x, int y) {

   int b=3;

   if (position==1) { //if at start, only need to check for clicks on start side
      //start side, return positive val
      if ((x>=20 && x<=70) && (y>=345 && y<=387)) {
	 return cabbage;
      }
      else if ((x>=85 && x<=150) && (y>=390 && y<=457)) {
	 return wolf;
      }
      else if ((x>=110 && x<=170) && (y>=335 && y<=376)) {
	 return goat;
      }
      else if ((x>=190 && x<=270) && (y>=330 && y<=424)) {
	 return b;
      }
   }
   else if (position==-1) {
      //end side
      if ((x>=380 && x<=430) && (y>=340 && y<=382)) {
	 return cabbage;
      }
      else if ((x>=410 && x<=475) && (y>=385 && y<=452)) {
	 return wolf;
      }
      else if ((x>=450 && x<=510) && (y>=340 && y<=381)) {
	 return goat;
      }
      else if ((x>=285 && x<=365) && (y>=330 && y<=424)) {
	 return b;
      }
   }

   //all other clicks return 0
   return 0;

}

void Rivercrossing::drop() {

   char choice;

   if (position==1) {
      start=start+onboat;
      onboat=0;
   }
   else if (position==-1) {
      end=end+onboat;
      onboat=0;
   }
  
}

void Rivercrossing::pickup(char choice) {

   switch (choice) {
      case 'w':
	 //check if wolf on that side
	 if (position==1) {
	    if (start==wolf+goat || start==wolf+cabbage || start==wolf+goat+cabbage || start==wolf) {
	       onboat=wolf;
	       start=start-wolf;
	    }
	 }
	 else if (position==-1) {
	    if (end==wolf+goat || end==wolf+cabbage || end==wolf) {
	       onboat=wolf;
	       end=end-wolf;
	    }
	 }
	 break;
      case 'g':
	 //check if goat on that side
	 if (position==1) {
	    if (start==wolf+goat || start==goat+cabbage || start==wolf+goat+cabbage || start==goat) {
	       onboat=goat;
	       start=start-goat;
	    }
	 }
	 else if (position==-1) {
	    if (end==wolf+goat || end==goat+cabbage || end==goat) {
	       onboat=goat;
	       end=end-goat;
	    }
	 }
	 break;
      case 'c':
	 //check if cabbage on that side
	 if (position==1) {
	    if (start==cabbage+goat || start==cabbage+wolf || start==wolf+goat+cabbage || start==cabbage) {
	       onboat=cabbage;
	       start=start-cabbage;
	    }
	 }
	 else if (position==-1) {
	    if (end==cabbage+goat || end==cabbage+wolf || end==cabbage) {
	       onboat=cabbage;
	       end=end-cabbage;
	    }
	 }
	 break;
   }
   
}

bool Rivercrossing::loadMedia() {

   bool success = true;

   //load images
   if (!gBackgroundTexture.loadFromFile("Puzzles/rivercrossingPuzzle/images/river.png")) {
      printf("failed to load background texture\n");
      success=false;
   }
   if (!gSheep.loadFromFile("Puzzles/rivercrossingPuzzle/images/sheep.png")) {
      printf("failed to load sheep texture\n");
      success=false;
   }
   if (!gWolf.loadFromFile("Puzzles/rivercrossingPuzzle/images/wolf.png")) {
      printf("failed to load wolf texture\n");
      success=false;
   }
   if (!gCabbage.loadFromFile("Puzzles/rivercrossingPuzzle/images/cabbage.png")) {
      printf("failed to load cabbage texture\n");
      success=false;
   }
   if (!gBoat.loadFromFile("Puzzles/rivercrossingPuzzle/images/farmerandboat1.png")) {
      printf("failed to load boat texture\n");
      success=false;
   }

   //load text/font
   gFont = TTF_OpenFont("adamwarrenpro.ttf", 18);
   if (gFont == NULL) {
      printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
      success=false;
   }
   else {
      gText.setFont(gFont);
   }

   return success;

}

