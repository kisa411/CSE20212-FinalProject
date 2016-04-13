// Ending Scene

#include "ending.h"


//constructor
Ending::Ending( SDL_Window* gWindow, SDL_Renderer* gRenderer, int points, char g ) : gBackgroundTexture(gWindow, gRenderer), gTextTexture(gWindow, gRenderer) {
	pointTotal = points;
	gender = g;
	loadMedia();

}

//destructor
Ending::~Ending() {
	gBackgroundTexture.free();
	gTextTexture.free()
}

//display storyline
void Ending::display() {

	SDL_RenderClear( gRenderer );
	// Render Background
	gBackgroundTexture.render(0,0, NULL);
	gTextTexture.render(0, 0, NULL);

	/*
	if ( pointTotal> ... ) { //good ending
		if ( gender == 'F' ) {
			cout << "The prince says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D'" << endl;
			cout << "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up a five-star worthy course meal, complete with chocolate cake for dessert. Bon appetit!" << endl;
		} else if ( gender == 'M' ) {
			cout << "The princess says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D'" << endl;
			cout << "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up a five-star worthy course meal, complete with chocolate cake for dessert. Bon appetit!" << endl;
		}
	} else if ( pointTotal > ... && pointTotal < ... ) { //okay ending
		if ( gender == 'F' ) {
			cout << "The prince says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D'" << endl;
			cout << "Fortunately, you were able to pick enough ingredients along the way you were able to whip up something decently edible. The food wasn't the best, but the picnic was still fun!" << endl;
		} else if ( gender == 'M' ) {
			cout << "The princess says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D'" << endl;
			cout << "Fortunately, you were able to pick up so many good ingredients along the way you were able to whip up something decently edible. The food wasn't the best, but the picnic was still fun!" << endl;
		}
	} else { //bad ending
		if ( gender == 'F' ) {
			cout << "The prince says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D'" << endl;
			cout << "Unfortunately, the only thing you were able to make with the ingredients you had was some pitiful gruel. The prince bursts into tears in disappointment and hunger - you should've done better with the puzzles!" << endl;
		} else if ( gender == 'M' ) {
			cout << "The princess says: 'Hey! I've been waiting forever for you to get here! C'mon, let's eat! :D'" << endl;
			cout << "Unfortunately, the only thing you were able to make with the ingredients you had was some pitiful gruel. The prince bursts into tears in disappointment and hunger - you should've done better with the puzzles!" << endl;
		}
	}
	*/
}

//load media
bool Ending::loadMedia() {

	//Loading success flag
	bool success = true;

	//Load background texture
	if ( pointTotal> ... ) { //good ending
		if ( gender == 'F' ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(boy-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		} else if ( gender == 'M' ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(girl-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		}
	} else if ( pointTotal > ... && pointTotal < ... ) { //okay ending
		if ( gender == 'F' ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(boy-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		} else if ( gender == 'M' ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(girl-good).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		}
	} else { //bad ending
		if ( gender == 'F' ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(boy-bad).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		} else if ( gender == 'M' ) {
			if( !gBackgroundTexture.loadFromFile( "endscene(girl-bad).png" ))
			{
				printf( "Failed to load sprite sheet texture!\n" );
				success = false;
			}
		}
	}
	
	//Open the font
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 24 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render the prompt
        SDL_Color textColor = { 0, 0, 0, 0xFF };
        if( !gTextTexture.loadFromRenderedTextWrapped( "You've finally arrived at the palace! You see your friend has already set out a picnic blanket so you head over with your picnic basket.\n", textColor, 350 ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }
    }

	return success;
}



