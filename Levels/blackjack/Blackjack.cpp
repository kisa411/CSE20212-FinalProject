#include<iostream>
#include<deque>
#include<cstdlib>
#include<string>
#include<cstdio>
#include<thread>
#include<chrono>
#include"Blackjack.h"
#include"CardDeck.h"
#include"texture.h"
#include"sdl_win_wrap.h"

using namespace std;

Blackjack::Blackjack(SDL_Window* ngWindow, SDL_Renderer* ngRenderer):
   gBackground(ngWindow, ngRenderer), \
   gText(ngWindow, ngRenderer), \
   gInputText(ngWindow, ngRenderer), \
   gWins(ngWindow, ngRenderer), \
   gLosses(ngWindow, ngRenderer), \
   gTies(ngWindow, ngRenderer), \
   gWindow(ngWindow), \
   gRenderer(ngRenderer)
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

   //render wins, ties, and losses
   if (!gWins.loadFromRenderedTextWrapped((to_string(wins)).c_str(), color, 20)) {
       printf("Failed to render wins!\n");
   }
   else {
      gWins.render(20, 340);
   }
   if (!gTies.loadFromRenderedTextWrapped((to_string(ties)).c_str(), color, 20)) {
       printf("Failed to render ties!\n");
   }
   else {
      gTies.render(60, 340);
   }
   if (!gLosses.loadFromRenderedTextWrapped((to_string(losses)).c_str(), color, 20)) {
       printf("Failed to render ties!\n");
   }
   else {
      gLosses.render(100, 340);
   }

   SDL_RenderPresent(gRenderer);

}

//display players cards
void Blackjack::displaycards(deque<int> d) {

   //render cards 
   int starty=380;
   int startx=20;
   int space=25;
   int width=49;
   int height=77;
   deque<int>::const_iterator i;
   int j=0;

   //players cards
   for (i=d.begin(); i!=d.end(); ++i) {
      gCardDeck.render(startx+(j*space), starty, width, height, &gCards[*i]);
      j++;
   }

}

//display dealers cards
void Blackjack::displaydcards(deque<int> d, int numcards) {

   //render cards 
   int starty=200;
   int startx=100;
   int space=15;
   int width=32;
   int height=51;
   deque<int>::const_iterator i;
   int j=0;

   //players cards
   if (numcards==1) { //display only one card
       gCardDeck.render(startx, starty, width, height, &gCards[*(d.begin())]);
   }
   else { //display all cards
      for (i=d.begin(); i!=d.end(); ++i) {
	 gCardDeck.render(startx+(j*space), starty, width, height, &gCards[*i]);
	 j++;
      }
   }

}

void Blackjack::displayWTL(int w, int t, int l) { //displays number of wins/ties/losses on image
   
   if (!gWins.loadFromRenderedTextWrapped(to_string(w), color, 250)) {
      printf("Failed to render wins!\n");
   }
   gWins.render(30, 300);

   if (!gTies.loadFromRenderedTextWrapped(to_string(t), color, 250)) {
      printf("Failed to render ties!\n");
   }
   gTies.render(70, 300);
 
   if (!gLosses.loadFromRenderedTextWrapped(to_string(l), color, 250)) {
      printf("Failed to render losses!\n");
   }
   gLosses.render(110, 300);

   SDL_RenderPresent(gRenderer);


}

void Blackjack::displaytext(int x, int y, string message) {

   if (!gText.loadFromRenderedTextWrapped(message.c_str(), color, 250)) {
      printf("Failed to render text!\n");
   }
   gText.render(x, y);
   SDL_RenderPresent(gRenderer);

}

void Blackjack::menu() {

   displaytext(40, 40, "To play, you need the sum of your cards to be greater than the dealers sum and to add up to 21 but no morethan that! Go over, and you lose. Face cards are worth 10 each and the Ace is worth 11. Click 'Hit' to draw a card, 'Stand' to stop drawing. Good luck!");

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

void Blackjack::play() {

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
   displaytext(40, 40, "Let's play Blackjack! Press enter to start!");

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

      //players turn
      while (game) { 
	 //deal a card to dealer and show to user
	 dcard=convertToCard(dealer[0]);

	 SDL_RenderClear(gRenderer);
	 display(); //display background
	 menu(); //display menu text
	 displaycards(player); //display current cards
	 m="The dealer has a "+dcard;
	 displaytext(400, 40, m); //display what dealer has as text
	 displaydcards(dealer, 1); //display dealers card as image
	 displayWTL(wins, ties, losses); //display number of wins/ties/losses on image

	 total=sum(player);
	 if (total>=21) { //stop turn
	    break;
	 }

	 manageEvents(e, change, drawcard, stop, exit);

	 if (change) {
	    if (drawcard) {  //hit was clicked
	       player.push_back(currDeck->draw());
	       displaycards(player);
	    }
	    if (stop) { //stand was clicked
	       game=0; //quit players turn

	       SDL_RenderClear(gRenderer);
	       display(); //display background
	       menu(); //display menu text
	       displaytext(400, 40, "Your turn is over!");
	       displaycards(player); //display current cards
	       displaydcards(dealer, 1); //display dealers card as image
               displayWTL(wins, ties, losses); //display number of wins/ties/losses on image

	    }
	    if (exit) {  //x button clicked
	       game=0;
	       dgame=0;
	       break;
	    }
	 }

      }

      //pause 3 secs before going to dealers turn
      std::this_thread::sleep_for(std::chrono::seconds(3));

      //dealers turn
      while (dgame) {
	 dtotal=sum(dealer);

	 SDL_RenderClear(gRenderer);
	 display(); //display background
	 menu(); //display menu text
	 displaydcards(dealer, 0); //display current dealers cards
	 displaycards(player); //keep players cards displayed
	 displaytext(400, 40, "Your turn is over! Dealers turn.");
         displayWTL(wins, ties, losses); //display number of wins/ties/losses on image

	 if (dtotal<17) { //if dealer has total sum of less that 17, must draw
	    dealer.push_back(currDeck->draw());
	    std::this_thread::sleep_for(std::chrono::seconds(1)); //sleep for a second before displaying next card

	    SDL_RenderClear(gRenderer);
	    display(); //display background
	    menu(); //display menu text
	    displaydcards(dealer, 0); //display current cards
	    displaycards(player); //keep players cards displayed
	    displaytext(400, 40, "Dealers turn");
	    displayWTL(wins, ties, losses); //display number of wins/ties/losses on image
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
	 //TODO: update losses and ties and wins value
	 SDL_RenderClear(gRenderer);
	 display(); //display background
	 menu(); //display menu text
	 displaydcards(dealer, 0); //display current cards
	 displaycards(player); //keep players cards displayed
	 displaytext(400, 40, m);
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
	 displaytext(40, 40, m);
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

void Blackjack::manageEvents(SDL_Event &e, bool &change, bool &drawcard, bool &stop, bool &exit) {

   int pos;
   int hit=1;
   int stand=2;

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
                  change=true;
                  break;
               case stand: 
		  stop=true;
                  change=true;
                  break;
               case 0:  //default case, dont do anything
                  change=false;
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
   if ((x>=540 && x<=580) && (y>=340 && y<=380)) {
      return 1;
   }
   else if ((x>=590 && x<= 630) && (y>=340 && y<=380)) {
      return 2;
   }
  
   //all other clicks return 0
   return 0;

}

string Blackjack::userInput() {

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


bool Blackjack::loadMedia() {
   
   int startx=0;
   int starty=0;
   int width=49;
   int height=77;

   bool success = true;

   //load images
   if (!gBackground.loadFromFile("images/casino.png")) {
      printf("failed to load background texture\n");
      success=false;
   }
   //load deck of cards
   if (!gCardDeck.loadFromFile("images/carddeck.png")) {
      printf("failed to load card deck texture\n");
      success=false;
   }
   else {
      for (int i=0; i<4; i++) {
	 for (int j=0; j<13; j++) {
	    gCards[i].x=startx+(width*j);
	    gCards[i].y=starty+(height*i);
	    gCards[i].w=width;
	    gCards[i].h=height;
	 }
      }
   }
   

   //load text/font
   gFont = TTF_OpenFont("adamwarrenpro.ttf", 18);

   if (gFont == NULL) {
      printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
      success=false;
   }
   else {
      gText.setFont(gFont);
      gWins.setFont(gFont);
      gLosses.setFont(gFont);
      gTies.setFont(gFont);
   }


   return success;

}

