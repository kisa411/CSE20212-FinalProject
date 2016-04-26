// Ending Scene


#include "ending.h"


//constructor
Ending::Ending( SDL_Window* ngWindow, SDL_Renderer* ngRenderer, int points, string g ) : gBackgroundTexture(ngWindow, ngRenderer), gTextTexture(ngWindow, ngRenderer), gPromptTextTexture(ngWindow, ngRenderer), gWindow(ngWindow), gRenderer(ngRenderer) {
	pointTotal = points;
	gender = g;
	loadMedia();
	SDL_GetWindowSize(gWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
}

//destructor
Ending::~Ending() {
	gBackgroundTexture.free();
    gPromptTextTexture.free();
    gTextTexture.free();
}

//display storyline
bool Ending::display() {
	bool complete = false;
    bool success = true;
    bool next = false;

    SDL_Event e;

    int textXpos = ((1*SCREEN_WIDTH)/7)-10;
    int textYpos = ((8*SCREEN_HEIGHT)/11)-8;

    SDL_Color textColor = { 0, 0, 0, 0xFF };
    gTextTexture.setFont(gFont);

	SDL_RenderClear( gRenderer );
    while (!next) {
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gTextTexture.render( textXpos, textYpos );
        //Update screen
        SDL_RenderPresent( gRenderer );
        next=continueText(e);
    }
    next = false;

	
	if ( pointTotal> 500 ) { //good ending
		if ( gender == "FEMALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The prince says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;

			if( !gTextTexture.loadFromRenderedTextWrapped( "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up a five-star worthy course meal, complete with chocolate cake for dessert. Bon appetit!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;
		    	complete = true;
		} else if ( gender == "MALE" ) {

			if( !gTextTexture.loadFromRenderedTextWrapped( "The princess says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;

		    if( !gTextTexture.loadFromRenderedTextWrapped( "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up a five-star worthy course meal, complete with chocolate cake for dessert. Bon appetit!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;
		    	complete = true;
		}
	} else if ( pointTotal > 200 && pointTotal <= 500 ) { //okay ending
		if ( gender == "FEMALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The prince says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;

			if( !gTextTexture.loadFromRenderedTextWrapped( "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up something decently edible. The food wasn't the best, but the picnic was still fun!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;
		    	complete = true;
		} else if ( gender == "MALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The princess says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;

			if( !gTextTexture.loadFromRenderedTextWrapped( "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up something decently edible. The food wasn't the best, but the picnic was still fun!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;
		    	complete = true;
		}
	} else if ( pointTotal <= 200 ) { //bad ending
		if ( gender == "FEMALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The prince says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;

			if( !gTextTexture.loadFromRenderedTextWrapped( "Unfortunately, the only thing you were able to make with the ingredients you had was some pitiful gruel. The prince bursts into tears in disappointment and hunger - you should've done better with the puzzles!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;
		    	complete = true;
		} else if ( gender == "MALE" ) {
			if( !gTextTexture.loadFromRenderedTextWrapped( "The princess says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;
			if( !gTextTexture.loadFromRenderedTextWrapped( "Unfortunately, the only thing you were able to make with the ingredients you had was some pitiful gruel. The princess bursts into tears in disappointment and hunger - you should've done better with the puzzles!", textColor, 450 ) ) {
		        printf( "Failed to render text texture!\n" );
		    }
		    SDL_RenderClear( gRenderer );
		    while (!next) {
		        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		        gTextTexture.render( textXpos, textYpos );
		        //Update screen
		        SDL_RenderPresent( gRenderer );
		        next=continueText(e);
		    }
		    next = false;

		    	complete = true;
		}
	}

	if( !gTextTexture.loadFromRenderedTextWrapped( "Thanks for playing! I hope you had fun :)", textColor, 450 ) ) {
        printf( "Failed to render text texture!\n" );
    }
    SDL_RenderClear( gRenderer );
    while (!next) {
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gTextTexture.render( textXpos, textYpos );
        //Update screen
        SDL_RenderPresent( gRenderer );
        next=continueText(e);
    }
    next = false;

	return complete;
}

//load media
bool Ending::loadMedia() {

	//Loading success flag
	bool success = true;

	//Load background texture
	if ( pointTotal> 500 ) { //good ending
		if ( gender == "FEMALE" ) {
			if( !gBackgroundTexture.loadFromFile( "ending/endscene(boy-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		} else if ( gender == "MALE" ) {
			if( !gBackgroundTexture.loadFromFile( "ending/endscene(girl-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		}
	} else if ( pointTotal > 200 && pointTotal <= 500 ) { //okay ending
		if ( gender == "FEMALE" ) {
			if( !gBackgroundTexture.loadFromFile( "ending/endscene(boy-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		} else if ( gender == "MALE" ) {
			if( !gBackgroundTexture.loadFromFile( "ending/endscene(girl-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		}
	} else if ( pointTotal <= 200 ) { //bad ending
		if ( gender == "FEMALE" ) {
			if( !gBackgroundTexture.loadFromFile( "ending/endscene(boy-bad).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		} else if ( gender == "MALE" ) {
			if( !gBackgroundTexture.loadFromFile( "ending/endscene(girl-bad).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		}
	}
	
	//Open the font
    gFont = TTF_OpenFont( "ending/adamwarrenpro.ttf", 18 );
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
        if( !gTextTexture.loadFromRenderedTextWrapped( "You've finally arrived at the palace! You see your friend has already set out a picnic blanket so you head over with your picnic basket.\n", textColor, 450 ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }
    }

	return success;
}

bool Ending::continueText(SDL_Event & e) {
    bool quit = false;
    bool enter = false;

    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
        else if ( e.type == SDL_KEYDOWN ) {
            //User presses a key
            if( e.key.keysym.sym == SDLK_RETURN )
            {
                enter = true;
            }
        }
    }

    return enter;
}


