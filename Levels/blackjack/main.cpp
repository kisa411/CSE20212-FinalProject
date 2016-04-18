//
//  main.cpp
//  blackjack
//
//  Created by Emily Koh on 4/9/16.
//  Copyright © 2016 Emily Koh. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "cardDeck.h"
#include "sdl_win_wrap.h"
#include "texture.h"
using namespace std;

int playBlackJack() {
    int points=0;
    
    SDL_Win_Wrap window_instance; //SDL window object
    
    LTexture gTextTexture(window_instance.getWindow(), window_instance.getRenderer());

    
    //create an object of class CardDeck
    CardDeck blackjack( window_instance.getWindow(), window_instance.getRenderer(), 52 ); //blackjack object
    
    //initialize all the necessary variables
    int playerWins=0, dealerWins=0, playerTotal=0, dealerTotal=0;
    int size = blackjack.getSize(); //store the initial number of cards in the deck(should be 52)
    int choice, card, dealerPlay = 1; //0 = no, 1 = yes
    string hitorstand = "hit"; //start with hit
    
    //Render text
    SDL_Color textColor = { 0, 0, 0 };
    if( !gTextTexture.loadFromRenderedText( "Welcome to the casino! Beat the dealer in a game of blackjack to get something awesome!\n", textColor ) ) {
        printf( "Failed to render text texture!\n" );
    }
    
    int choice = 1;
    
    while ( choice == 1 ) {
        blackjack.shuffle(); //shuffle the deck so that they're in random order
        playerTotal = 0; //reset player total
        dealerTotal = 0; //reset dealer total
        while ( size>=15 ) { //while there are 15 or more cards, play the game
            
            if ( hitorstand == "hit" ) { //player's turn - if they say stand then they would no longer be able to get a card
                card = blackjack.player(); //give the player a card
                playerTotal += card; //add the card's value to the player's total
                
                if ( playerTotal > 21 ) {
                    if( !gTextTexture.loadFromRenderedText( "Sorry, your total went over 21. You lose!\n", textColor ) ) {
                        printf( "Failed to render text texture!\n" );
                    }
                    
                    break;
                }
                size--; //decrease the number of cards in the deck by one
            }
            //dealer's turn - automatically gets a card unless value goes up to 17 or greater
            if ( dealerPlay == 1 ) {
                card = blackjack.dealer(); //give the dealer a card
                dealerTotal += card;
                if( !gTextTexture.loadFromRenderedText( "The dealer has received a card.\n", textColor ) ) {
                    printf( "Failed to render text texture!\n" );
                }
                
                size--;
                if (dealerTotal >= 17 ) { //if the dealer's total reaches 17 or higher then they stop
                    dealerPlay = 0;
                }
            }
            if( !gTextTexture.loadFromRenderedText( "Would you like to hit or stand? Please put either 'hit' or 'stand'.\n", textColor ) ) {
                printf( "Failed to render text texture!\n" );
            }
            
            cin >> hitorstand;
            if ( hitorstand == "stand" || hitorstand == "hit" ) {
                if ( dealerPlay == 0 && hitorstand == "stand" ) {
                    break; //if player stands and the dealer is also not taking any more cards, finish the game
                } else if ( dealerPlay == 1 && hitorstand == "stand" ) {
                    continue; //if player stands but the dealer is taking more cards, then continue the game so that the dealer can take a card
                }
                continue; //if the player hits then continue the game
            }
            else {
                if( !gTextTexture.loadFromRenderedText( "Sorry, could not process input. Please put either 'hit' or 'stand'.\n", textColor ) ) {
                    printf( "Failed to render text texture!\n" );
                }
                
                cin >> hitorstand;
            }
        }
        
        
        //announce the results of this round
        if ( playerTotal > dealerTotal ) {
            if ( playerTotal <= 21 ) {
                if( !gTextTexture.loadFromRenderedText( "The player has won this round. Congratulations! You can leave the casino now.\n", textColor ) ) {
                    printf( "Failed to render text texture!\n" );
                }
                
                playerWins++;
            } else {
                if( !gTextTexture.loadFromRenderedText( "Sorry, the dealer won this round.\n", textColor ) ) {
                    printf( "Failed to render text texture!\n" );
                }
                
                dealerWins++;
            }
            choice = 1; //this starts a new game
        } else if ( dealerTotal > playerTotal ) {
            if ( dealerTotal <= 21 ) {
                if( !gTextTexture.loadFromRenderedText( "Sorry, the dealer won this round.\n", textColor ) ) {
                    printf( "Failed to render text texture!\n" );
                }
                
                dealerWins++;
            } else {
                if( !gTextTexture.loadFromRenderedText( "The player has won this round. Congratulations! You can leave the casino now.\n", textColor ) ) {
                    printf( "Failed to render text texture!\n" );
                }

                playerWins++;
            }
            choice = 1; //this starts a new game
        } else if ( playerTotal == dealerTotal ) {
            if( !gTextTexture.loadFromRenderedText( "This round was a tie.\n", textColor ) ) {
                printf( "Failed to render text texture!\n" );
            }
            
            choice = 0; //end current blackjack game
        }
    }
    
    if ( playerWins>dealerWins ) {
        if( !gTextTexture.loadFromRenderedText( "You beat the dealer so you get something really good for your ingredient stash!\nThe dealer says: Come back again soon! :)\n", textColor ) ) {
            printf( "Failed to render text texture!\n" );
        }
        
        points+=100;
        return points;
    } else if ( dealerWins>playerWins ) {
        if( !gTextTexture.loadFromRenderedText( "The dealer beat you so you have to give up something really yummy.\nThe dealer says: Come back again soon! :)\n", textColor ) ) {
            printf( "Failed to render text texture!\n" );
        }
        
        points-=100;
        return points;
    } else if ( playerWins == dealerWins ) {
        if( !gTextTexture.loadFromRenderedText( "Seems like the game ended in a tie. You don't get any penalties or rewards - oh well! Could've been worse!\nThe dealer says: Come back again soon! :)\n", textColor ) ) {
            printf( "Failed to render text texture!\n" );
        }
        
        return points;
    }
    
}

int main () {
    int pointsEarned;
    
    srand( time(0) ); //changes the seed number for the shuffle randomly - using time() allows for really random numbers since now the numbers coming out of the srand() function are based off the time

    
    /*BLACKJACK GAME*/
    pointsEarned = playBlackJack();
    //add points earned to player's total points
    
    return 0;
}

