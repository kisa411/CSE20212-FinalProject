// Opening Scene

#include "opening.h"


//constructor
Opening::Opening( SDL_Window* ngWindow, SDL_Renderer* ngRenderer ) : gBackgroundTexture(ngWindow, ngRenderer), gInputTextTexture(ngWindow, ngRenderer), gPromptTextTexture(ngWindow, ngRenderer), gWindow(ngWindow), gRenderer(ngRenderer)  {
	loadMedia();
}

//destructor
Opening::~Opening() {
	gBackgroundTexture.free();
    gInputTextTexture.free();
    gPromptTextTexture.free();

}

//display storyline
char Opening::display() {

	SDL_RenderClear( gRenderer );
	// Render Background
	gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	gPromptTextTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

	/*
	cout << "Before the game starts, what is your gender? M or F?" << endl;
	char gender;
	cin >> gender;
	gender=toupper(gender); //make capital letter

	if ( gender=='M' ) {
		cout << "Good morning! Today's the day for your picnic with your best friend, who also happens to be the princess of the kingdom! You've been planning this day for a while, when you go check your fridge you don't actually have anything to make food for the picnic with. You should try going outside to see if there's any ingredients that you might be able to find along the way to the palace!" << endl;
	} else if ( gender=='F' ) {
		cout << "Good morning! Today's the day for your picnic with your best friend, who also happens to be the prince of the kingdom! You've been planning this day for a while, when you go check your fridge you don't actually have anything to make food for the picnic with. You should try going outside to see if there's any ingredients that you might be able to find along the way to the palace!" << endl;
	}
	*/

	//Update screen
    SDL_RenderPresent( gRenderer );

	// return gender;
}

//load media
bool Opening::loadMedia() {

	//Loading success flag
	bool success = true;

	//Load background texture	
	if( !gBackgroundTexture.loadFromFile( "opening.png" ))
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
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
        gPromptTextTexture.setFont(gFont);
        if( !gPromptTextTexture.loadFromRenderedTextWrapped( "M or F?: ", textColor, 350 ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }
    }

	return success;
}



