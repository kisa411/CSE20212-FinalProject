// Opening Scene

#include "opening.h"


//constructor
Opening::Opening( SDL_Window* ngWindow, SDL_Renderer* ngRenderer ) : gBackgroundTexture(ngWindow, ngRenderer), gInputTextTexture(ngWindow, ngRenderer), gPromptTextTexture(ngWindow, ngRenderer), gTextTexture(ngWindow, ngRenderer), gWindow(ngWindow), gRenderer(ngRenderer)  {
	loadMedia();
}

//destructor
Opening::~Opening() {
	gBackgroundTexture.free();
    gInputTextTexture.free();
    gPromptTextTexture.free();
    gTextTexture.free();
}


void Opening::displayRoom() {

    int textXpos = SCREEN_WIDTH/5;
    int textYpos = (8*SCREEN_HEIGHT)/11;

    bool success = true;

    SDL_RenderClear( gRenderer );
    //SDL code for displaying (rendering) puzzle image
    gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

    //Open the font
    //Free global font
    TTF_CloseFont( gFont );
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 16 );
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        gTextTexture.setFont(gFont);
        if( !gTextTexture.loadFromRenderedTextWrapped( "Welcome to Nom Nom!\n", textColor, 400 ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        gTextTexture.render(textXpos, textYpos);

    }


    // Update Screen
    SDL_RenderPresent( gRenderer );
 
}

string Opening::play() {

	bool complete = false;
    string gender = "N/A";

    while (complete==false) {
        gender = display(); //determine the ending of the puzzle based on tryNumber
        if ( gender.compare("N/A") != 0 ) {
            complete = true;
        }
    }

    return gender;

}

//display storyline
string Opening::display() {
	 //Loading success flag
    bool success = true;

    int textXpos = (1*SCREEN_WIDTH)/7;
    int textYpos = (8*SCREEN_HEIGHT)/11;

    SDL_Color textColor = { 0, 0, 0, 0xFF };
    gTextTexture.setFont(gFont);

	SDL_RenderClear( gRenderer );
	// Render Background


	if( !gTextTexture.loadFromRenderedTextWrapped( "Before the game starts, what is your gender? Male or Female?", textColor, 450 ) ) {
        printf( "Failed to render text texture!\n" );
    }
    SDL_RenderClear( gRenderer );
    for ( int i=0; i<2000; i++ ) {
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gTextTexture.render( textXpos, textYpos );
        //Update screen
        SDL_RenderPresent( gRenderer );
    }

	string gender = userInput(); //get the gender 

	for ( int j=0; j<gender.length(); j++ ) {
        gender[j] = ::toupper(gender[j]); //make the answer lower-case
    }


	if( !gTextTexture.loadFromRenderedTextWrapped( "Good morning! Today's the day for your picnic with your best friend, who also happens to be the ruler of the kingdom! You've been planning this day for a while, when you go check your fridge you don't actually have anything to make food for the picnic with.", textColor, 450 ) ) {
        printf( "Failed to render text texture!\n" );
    }
    SDL_RenderClear( gRenderer );
    for ( int i=0; i<2000; i++ ) {
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gTextTexture.render( textXpos, textYpos );
        //Update screen
        SDL_RenderPresent( gRenderer );
	}

	if( !gTextTexture.loadFromRenderedTextWrapped( "You should try going outside to see if there's any ingredients that you might be able to find along the way to the palace!", textColor, 450 ) ) {
        printf( "Failed to render text texture!\n" );
    }
    SDL_RenderClear( gRenderer );
    for ( int i=0; i<2000; i++ ) {
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gTextTexture.render( textXpos, textYpos );
        //Update screen
        SDL_RenderPresent( gRenderer );
    }

	return gender;
}

string Opening::userInput() {

    int textXpos = (2*SCREEN_WIDTH)/7;
    int textYpos = (3*SCREEN_HEIGHT)/4;

    //Main loop flag
    bool quit = false;
    bool enter = false;
    bool success = true;

    //Event handler
    SDL_Event e;

    //Set text color as black
    SDL_Color textColor = { 0, 0, 0, 0xFF };

    // //Open the font
    gFont = TTF_OpenFont( "adamwarrenpro.ttf", 16 );
    if( gFont == NULL )
    {
        printf( "Failed to load adamwarrenpro font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    //render the question 
    gPromptTextTexture.setFont(gFont);
    
    //The current input text.
    string inputText = "Erase and put answer here";
    gInputTextTexture.setFont(gFont);
    gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );

    //Enable text input
    SDL_StartTextInput();


    //While application is running
    while( !enter )
    {
        //The rerender text flag
        bool renderText = false;


        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            // User requests quit
            if( e.type == SDL_QUIT )
            {
                enter = true;
                // complete = true;
                break;
            }
            //Special key input
            else if( e.type == SDL_KEYDOWN )
            {
                //Handle backspace
                if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
                {
                    //lop off character
                    inputText.pop_back();
                    renderText = true;
                } //Handle Return (enter)
                else if ( e.key.keysym.sym == SDLK_RETURN ) 
                {
                    enter = true;
                    break;
                }
            }
            //Special text input event
            else if( e.type == SDL_TEXTINPUT )
            {
                //Not copy or pasting
                if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
                {
                    //Append character
                    inputText += e.text.text;
                    renderText = true;
                }
            }
        }

        //Rerender text if needed
        if( renderText )
        {
            //Text is not empty
            if( inputText != "" )
            {
                //Render new text
                gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
            }
            //Text is empty
            else
            {
                //Render space texture
                gInputTextTexture.loadFromRenderedText( " ", textColor );
            }
        }

       //Clear screen
        // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //Render text textures
        gBackgroundTexture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        gPromptTextTexture.render( textXpos, textYpos );
        gInputTextTexture.render( textXpos, textYpos+gPromptTextTexture.getHeight() );

        //Update screen
        SDL_RenderPresent( gRenderer );
    }
    
    //Disable text input
    SDL_StopTextInput();
    // questionAnswered=true;

    return inputText;


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
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render the prompt
        SDL_Color textColor = { 0, 0, 0, 0xFF };
        gPromptTextTexture.setFont(gFont);
        if( !gPromptTextTexture.loadFromRenderedTextWrapped( "Male or Female?: ", textColor, 350 ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }
    }

	return success;
}



