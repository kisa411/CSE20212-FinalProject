#include<iostream>
#include<deque>
#include<cstdlib>
#include<string>
#include<cstdio>
#include<thread>
#include<chrono>
#include<SDL2/SDL_ttf.h>
#include"Blackjack.h"
#include"CardDeck.h"
#include"../../sharedClasses/texture.h"
#include"../../sharedClasses/sdl_win_wrap.h"

using namespace std;

Blackjack::Blackjack(SDL_Window* ngWindow, SDL_Renderer* ngRenderer):
   gBackground(ngWindow, ngRenderer),
   gText(ngWindow, ngRenderer),
   gInputText(ngWindow, ngRenderer),
   gWins(ngWindow, ngRenderer),
   gLosses(ngWindow, ngRenderer),
   gTies(ngWindow, ngRenderer),
   gCardDeck(ngWindow, ngRenderer),
   gRenderer(ngRenderer),
   gWindow(ngWindow)
{

   currDeck = new CardDeck(52);

   wins=0;
   ties=0;
   losses=0;

   loadMedia();

}

Blackjack::~Blackjack() {

   delete currDeck;
   gText.free();
   gBackground.free();
   gWins.free();
   gLosses.free();
   gTies.free();
   gCardDeck.free();

}

void Blackjack::deal() {

   //deal to dealer
   dealer.push_back(currDeck->draw());
   dealer.push_back(currDeck->draw());
   
   //deal to player
   player.push_back(currDeck->draw());
   player.push_back(currDeck->draw());

}

void Blackjack::display() { 

   SDL_RenderClear(gRenderer);

   //Render background
   gBackground.render(0, 0, 640, 480, NULL);

   SDL_RenderPresent(gRenderer);

}

//display players cards
void Blackjack::displaycards(deque<int> d) {

   //render cards 
   int starty=375;
   int startx=15;
   int space=25;
   int width=49;
   int height=77;
   deque<int>::const_iterator i;
   int j=0;

   //players cards
   for (i=d.begin(); i!=d.end(); ++i) {
      gCardDeck.render(startx+(j*space), starty, width, height, &gCards[*i-1]); 
      j++;
   }

}

//display dealers cards
void Blackjack::displaydcards(deque<int> d, int numcards) {

   //render cards 
   int starty=193;
   int startx=100;
   int space=15;
   int width=40;
   int height=64;
   deque<int>::const_iterator i;
   int j=0;

   //players cards
   if (numcards==1) { //display only one card
       gCardDeck.render(startx, starty, width, height, &gCards[*(d.begin())-1]);
   }
   else { //display all cards
      for (i=d.begin(); i!=d.end(); ++i) {
	 gCardDeck.render(startx+(j*space), starty, width, height, &gCards[*i-1]);
	 j++;
      }
   }

}

void Blackjack::displayWTL(int w, int t, int l) { //displays number of wins/ties/losses on image
   
   if (!gWins.loadFromRenderedTextWrapped(to_string(w), color, 250)) {
      printf("Failed to render wins!\n");
   }
   gWins.render(25, 300);

   if (!gTies.loadFromRenderedTextWrapped(to_string(t), color, 250)) {
      printf("Failed to render ties!\n");
   }
   gTies.render(80, 300);
 
   if (!gLosses.loadFromRenderedTextWrapped(to_string(l), color, 250)) {
      printf("Failed to render losses!\n");
   }
   gLosses.render(135, 300);

   SDL_RenderPresent(gRenderer);


}

void Blackjack::displaytext(int x, int y, string message) {

   if (!gText.loadFromRenderedTextWrapped(message.c_str(), color, 190)) {
      printf("Failed to render text!\n");
   }
   gText.render(x, y);
   SDL_RenderPresent(gRenderer);

}

void Blackjack::menu() {

   displaytext(20, 20, "To play, the sum of your cards should be greater than the dealer's but less than 21. Face cards are worth 10 each and the Ace is worth 11. Click 'Hit' to draw a card, 'Stand' to stop drawing. Good luck!");

}

string Blackjack::convertToCard(int i) {

   string card;
   char c;

   if (i%13==0) { 
      card="K";
   }
   else if (i%13==12) {
      card="Q";
   }
   else if (i%13==11) {
      card="J";
   }
   else if (i%13==1) {
      card="A";
   }
   else {
      if (i%13==10) {
	 card="10";
      }
      else {
         c=(i%13)+48;
	 card=c;
      }
   }

   return card;

}


int Blackjack::sum(deque<int> d) {
   
   int sum=0; 

   deque<int>::const_iterator i;

   for (i=d.begin(); i!=d.end(); ++i) {
      if ((*i)%13==1) { //1=ace
	 sum+=11;
      }
      else if ((*i)%13>10 || (*i)%13==0) {
	 sum+=10;
      }
      else {
         sum+=(*i)%13;
      }
   }

   return sum;

}

int Blackjack::play() {

   int playing=1;
   string choice; 
   int total;   //players total sum
   int dtotal;  //dealers total sum
   int game=1;  //players turn
   int dgame=1; //dealers turn
   string dcard;
   string m;
   SDL_Event e;
   bool change;
   bool drawcard;
   bool stop;
   bool exit=false;
   int points;

   //initial display
   SDL_RenderClear(gRenderer);
   display();
   displaytext(20, 20, "Let's play Blackjack! Press enter to start!");

   //press enter to continue
   while (userInput()!=" ") {
      continue;
   }

   while (playing) {
      //if card deck size becomes less than 15 get a new deck
      if (currDeck->getSize()<=15) {
	 delete currDeck;  //delete current deck
	 CardDeck *currDeck = new CardDeck(52); //make a new deck
      }

      currDeck->shuffle();  //shuffle deck before each game

      deal(); //deal cards

      //show one of dealers cards
      dcard=convertToCard(dealer[0]);
      SDL_RenderClear(gRenderer);
      display(); //display background
      menu(); //display menu text
      displaycards(player); //display current cards
      m="The dealer has a "+dcard;
      displaytext(400, 20, m); //display what dealer has as text
      displaydcards(dealer, 1); //display dealers card as image
      displayWTL(wins, ties, losses); //display number of wins/ties/losses on image

      //players turn
      while (game) {

	 total=sum(player);
	 if (total>21) { //stop turn
	    SDL_RenderClear(gRenderer);
	    display(); //display background
	    menu(); //display menu text
	    displaytext(400, 20, "Your total is over 21! Your turn is over. Press enter to continue.");
	    displaycards(player); //display current cards
	    displaydcards(dealer, 1); //display dealers card as image
	    displayWTL(wins, ties, losses); //display number of wins/ties/losses on image
	    break;
	 }

	 drawcard=false;
	 stop=false;
	 exit=false;

	 manageEvents(e, drawcard, stop, exit);

	 if (drawcard) {  //hit was clicked
	    player.push_back(currDeck->draw());
	    displaycards(player);
	 }
	 else if (stop) { //stand was clicked
	    game=0; //quit players turn

	    SDL_RenderClear(gRenderer);
	    display(); //display background
	    menu(); //display menu text
	    displaytext(400, 20, "Your turn is over! Press enter to continue.");
	    displaycards(player); //display current cards
	    displaydcards(dealer, 1); //display dealers card as image
	    displayWTL(wins, ties, losses); //display number of wins/ties/losses on image

	 }
	 else if (exit) {  //x button clicked
	    game=0;
	    dgame=0;
	    break;
	 }
	 

      }

      //press enter to continue
      while (userInput()!=" ") {
	 continue;
      }

      SDL_RenderClear(gRenderer);
      display(); //display background
      menu(); //display menu text
      displaydcards(dealer, 0); //display current dealers cards
      displaycards(player); //keep players cards displayed
      displaytext(400, 20, "Dealers turn. Press enter to continue.");
      displayWTL(wins, ties, losses); //display number of wins/ties/losses on image

      //press enter to continue
      while (userInput()!=" ") {
	 continue;
      }

      //dealers turn
      while (dgame) {
	 dtotal=sum(dealer);

	 if (dtotal<17) { //if dealer has total sum of less that 17, must draw
	    dealer.push_back(currDeck->draw());
	    SDL_RenderClear(gRenderer);
	    display(); //display background
	    menu(); //display menu text
	    displaydcards(dealer, 0); //display current cards
	    displaycards(player); //keep players cards displayed
	    displaytext(400, 40, "Dealers turn");
	    displayWTL(wins, ties, losses); //display number of wins/ties/losses on image
	    std::this_thread::sleep_for(std::chrono::seconds(1)); //sleep for a second before displaying next card
	 }
	 else {
	    dgame=0;
	 }
      }

      if (!exit) {
	 total=sum(player);
	 dtotal=sum(dealer);
	 if (total<=21 && dtotal<=21) {
	    if (total<dtotal) {
	       m="Dealer wins!";
	       losses++;
	    }
	    else if (total>dtotal) {
	       m="You win!";
	       wins++;
	    }
	    else if (total==dtotal) {
	       m="It's a tie!";
	       ties++;
	    }
	 }
	 else if (total>21 || dtotal<=21) {
	    m="Dealer wins!";
	    losses++;
	 }
	 else if (total<=21 || dtotal>21) {
	    m="You win!";
	    wins++;
	 }
	 else if (total>21 && dtotal>21) {
	    m="Both your and the dealer's sums are over 21, dealer wins!";
	    losses++;
	 }
	 //update losses and ties and wins value
	 SDL_RenderClear(gRenderer);
	 display(); //display background
	 menu(); //display menu text
	 displaydcards(dealer, 0); //display current cards
	 displaycards(player); //keep players cards displayed
	 if (wins+ties+losses>=5) {
	    m+=" You played 5 games! Pres y then enter to continue";
	 }
	 else {
	    m+=" Press y to continue, n to quit, then press enter.";
	 }
	 displaytext(400, 20, m);
	 displayWTL(wins, ties, losses); //display number of wins/ties/losses on image

	 choice=userInput();
	 while (choice!=" y" && choice!=" n") {
	    choice=userInput();
	 }

	 if (choice==" y") {
	    game=1;
	    dgame=1;
	    player.clear();
	    dealer.clear();
	    change=false;
	    drawcard=false;
	    stop=false;
	    exit=false;
	 } 
	 else if (choice==" n") {
	    game=0;
	    dgame=0;
	 }
      }

      if(wins+ties+losses>=5 || choice==" n") { //at end of 5 games or user quits
	 points=20*wins;
	 m="You won "+to_string(wins)+" times, so you get "+to_string(points)+" points! ";
         
	 if (points>=60) {
	    m+="You did so well! Here is a lobster and a king crab for you!";
	 }
	 else if (points>=20 && points<=40) {
	    m+="You did okay I guess. You can have some of this cheap pasta.";
	 }
	 else if (points<=0) {
	    m+="Wow, blackjack is not your strongest game huh... I guess you can take this dessert. It looks great but tastes like soap.";
	 }
	 m+=" Press enter to continue";
	 //display final scene with points and reward message
         SDL_RenderClear(gRenderer);
	 display(); //display background
	 displaydcards(dealer, 0); //display current dealers cards
	 displaycards(player); //keep players cards displayed
	 displaytext(20, 20, m);
	 displayWTL(wins, ties, losses); //display number of wins/ties/losses on image

         //press enter to continue
	 while (userInput()!=" ") {
	    continue;
	 }

	 playing=0; //stop playing
      }
   }

   return points;
}

void Blackjack::manageEvents(SDL_Event &e, bool &drawcard, bool &stop, bool &exit) {

   int pos;
   const int hit=1;
   const int stand=2;

   while(SDL_PollEvent(&e)) {

         if(e.type == SDL_QUIT) {
                exit = true;
         }
         else if(e.type == SDL_MOUSEBUTTONDOWN) {
            //get mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);

            //check where mouse is
            pos=mousepos(x, y);

            switch (pos) {
               case hit: 
		  drawcard=true;
                  break;
               case stand: 
		  stop=true;
                  break;
               case 0:  //default case, dont do anything
		  drawcard=false;
		  stop=false;
		  exit=false;
                  break;
            }
         }
  }

}


int Blackjack::mousepos(int x, int y) {

   int b=3;
   //hit button = 1
   //stand button = 2
   //fix positions..
   if ((x>=445 && x<=535) && (y>=290 && y<=330)) {
      return 1;
   }
   else if ((x>=540 && x<= 630) && (y>=290 && y<=330)) {
      return 2;
   }
  
   //all other clicks return 0
   return 0;

}

string Blackjack::userInput() {

   bool enter=false;
   int xpos=400;
   int ypos=20;


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


bool Blackjack::loadMedia() {
   
   int startx=0;
   int starty=0;
   int width=49;
   int height=77;
   int k=0;

   bool success = true;

   //load images
   if (!gBackground.loadFromFile("Levels/blackjack/images/casino.png")) {
      printf("failed to load background texture\n");
      success=false;
   }
   //load deck of cards
   if (!gCardDeck.loadFromFile("Levels/blackjack/images/carddeck.png")) {
      printf("failed to load card deck texture\n");
      success=false;
   }
   else {
      for (int i=0; i<4; i++) {
	 for (int j=0; j<13; j++) {
	    gCards[k].x=startx+(width*j);
	    gCards[k].y=starty+(height*i);
	    gCards[k].w=width;
	    gCards[k].h=height;
	    k++;
	 }
      }
   }

   //load text/font
   gFont = TTF_OpenFont("Levels/blackjack/adamwarrenpro.ttf", 18);

   if (gFont == NULL) {
      printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
      success=false;
   }
   else {
      gText.setFont(TTF_OpenFont("Levels/blackjack/adamwarrenpro.ttf", 14));
      gInputText.setFont(gFont);
      gWins.setFont(gFont);
      gLosses.setFont(gFont);
      gTies.setFont(gFont);
   }


   return success;

}

