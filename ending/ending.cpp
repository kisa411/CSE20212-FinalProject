// Ending Scene

#include "ending.h"


//constructor
Ending::Ending( SDL_Window* ngWindow, SDL_Renderer* ngRenderer, int points, string g ) : gBackgroundTexture(ngWindow, ngRenderer), gTextTexture(ngWindow, ngRenderer), gWindow(ngWindow), gRenderer(ngRenderer) {
	pointTotal = points;
	gender = g;
	loadMedia();
	SDL_GetWindowSize(gWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
}

//destructor
Ending::~Ending() {
	gBackgroundTexture.free();
    gInputTextTexture.free();
    gPromptTextTexture.free();
    gTextTexture.free();
}

//display storyline
void Ending::display() {

    bool success = true;

    int textXpos = ((1*SCREEN_WIDTH)/7)-10;
    int textYpos = ((8*SCREEN_HEIGHT)/11)-8;

    SDL_Color textColor = { 0, 0, 0, 0xFF };
    gTextTexture.setFont(gFont);

	for ( int i=0; i<600; i++ ) {
		SDL_RenderClear( gRenderer );
		// Render Background
		gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		gTextTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		//Update screen
    	SDL_RenderPresent( gRenderer );
	}

	
	if ( pointTotal> ... ) { //good ending
		if ( gender == "FEMALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The prince says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }

			if( !gTextTexture.loadFromRenderedTextWrapped( "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up a five-star worthy course meal, complete with chocolate cake for dessert. Bon appetit!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }
		} else if ( gender == "MALE" ) {

			if( !gTextTexture.loadFromRenderedTextWrapped( "The princess says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }

		    if( !gTextTexture.loadFromRenderedTextWrapped( "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up a five-star worthy course meal, complete with chocolate cake for dessert. Bon appetit!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }
		}
	} else if ( pointTotal > ... && pointTotal < ... ) { //okay ending
		if ( gender == "FEMALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The prince says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }

			if( !gTextTexture.loadFromRenderedTextWrapped( "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up something decently edible. The food wasn't the best, but the picnic was still fun!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }
		} else if ( gender == "MALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The princess says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }

			if( !gTextTexture.loadFromRenderedTextWrapped( "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up something decently edible. The food wasn't the best, but the picnic was still fun!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }
		}
	} else { //bad ending
		if ( gender == "FEMALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The prince says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }

			if( !gTextTexture.loadFromRenderedTextWrapped( "Unfortunately, the only thing you were able to make with the ingredients you had was some pitiful gruel. The prince bursts into tears in disappointment and hunger - you should've done better with the puzzles!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }
		} else if ( gender == "MALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The princess says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }

			if( !gTextTexture.loadFromRenderedTextWrapped( "Unfortunately, the only thing you were able to make with the ingredients you had was some pitiful gruel. The princess bursts into tears in disappointment and hunger - you should've done better with the puzzles!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    for ( int i=0; i<500; i++ ) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos+30, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		    }
		}
	}
}

//load media
bool Ending::loadMedia() {

	//Loading success flag
	bool success = true;

	//Load background texture
	if ( pointTotal> ... ) { //good ending
		if ( gender == "FEMALE" ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(boy-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		} else if ( gender == "MALE" ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(girl-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		}
	} else if ( pointTotal > ... && pointTotal < ... ) { //okay ending
		if ( gender == "FEMALE" ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(boy-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		} else if ( gender == "MALE" ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(girl-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		}
	} else { //bad ending
		if ( gender == "FEMALE" ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(boy-bad).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		} else if ( gender == "MALE" ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(girl-bad).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		}
	}
	
	//Open the font
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 18 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render the prompt
        SDL_Color textColor = { 0, 0, 0, 0xFF };
        gTextTexture.setFont(gFont);
        if( !gTextTexture.loadFromRenderedTextWrapped( "You've finally arrived at the palace! You see your friend has already set out a picnic blanket so you head over with your picnic basket.\n", textColor, 350 ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }
    }

	return success;
}



