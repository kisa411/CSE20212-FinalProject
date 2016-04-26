#include "cryptography.h"
#include <sys/time.h>

crypto::crypto( SDL_Window* ngWindow, SDL_Renderer* ngRenderer):
background1Texture(ngWindow, ngRenderer),
background2Texture(ngWindow, ngRenderer),
background3Texture(ngWindow, ngRenderer),
hintTextTexture(ngWindow, ngRenderer),
promptTextTexture(ngWindow, ngRenderer),
inputTextTexture(ngWindow, ngRenderer),
wrongTextTexture(ngWindow, ngRenderer),
attemptsTextTexture(ngWindow, ngRenderer),
instructionsTextTexture(ngWindow, ngRenderer),
gRenderer(ngRenderer), gWindow(ngWindow)
{
	// Seed random number generator
	srand(time(NULL));
	// Get Screen Width and Height
	SDL_GetWindowSize(ngWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	// Store list of messages
	list_of_messages.push_back("do not walk on the grass");
	list_of_messages.push_back("who let the dogs out");
	list_of_messages.push_back("believe that you can succeed");
	list_of_messages.push_back("this is not a bug");
	
}

crypto::~crypto()
{
	background1Texture.free();
	background2Texture.free();
	promptTextTexture.free();
	hintTextTexture.free();
	inputTextTexture.free();
}

string crypto::caesar(int rot, string message)
{
	for(int i = 0; i < message.size(); i++)
	{
		if(islower(message[i]))
		{
			message[i] = (((message[i] -'a') + rot) %26) + 'a';
		}
		else if(isupper(message[i]))
		{
			message[i] = (((message[i] - 'A') + rot) %26) + 'A';
		}
	}
	return message;
}

string crypto::ascii(string message)
{
	int int_buff;
	char string_buff[10];
	string new_message;
	for(int i = 0; i < message.size(); i++)
	{
		int_buff = message[i];
		if(int_buff != ' ')
		{
			sprintf(string_buff, "%i", int_buff);
			new_message.append(string_buff);
			new_message.append(" ");
		}
		else
		{
			new_message.append("  ");
		}
	}
	return new_message;
}

string crypto::permutation(string message)
{
	string new_message;
	// Tokenize String
	istringstream iss(message);
	vector<string> tokens;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
	
	// Shuffle each word
	for(auto &x: tokens)
	{
		random_shuffle(x.begin(), x.end());
	}
	for(auto &x: tokens)
	{
		new_message.append(x);
		new_message.append(" ");
	}
	return new_message;
}

void crypto::prepareGame()
{
	mes_num = rand() % 4; // data member
	int crypt_method = rand() % 3;
	char buffer[20];
	int rot;
	
	SDL_StartTextInput(); // Enable textinput before game
	switch(crypt_method)
	{
		// Caesar
		case 0:
			rot = rand() % 25 + 1; // Does not allow rot 0
			encrypted_mes = caesar(rot, list_of_messages[mes_num]);
			sprintf(buffer, "%i",rot);
			hint = "Hint: ";
			hint.append(buffer);
			break;
		// Ascii
		case 1:
			encrypted_mes = ascii(list_of_messages[mes_num]);
			hint = "Hint: Ascii";
			break;
		case 2:
			encrypted_mes = permutation(list_of_messages[mes_num]);
			hint = "Hint: Disorder";
			break;
		
	}
	answer = "Delete This and Type Answer";
	// Set Text Textures
	promptTextTexture.loadFromRenderedTextWrapped(encrypted_mes.c_str(), textColor, 250);
	inputTextTexture.loadFromRenderedText(answer.c_str(), textColor);
	wrongTextTexture.loadFromRenderedText("Sorry, wrong answer!", textColor);
	instructionsTextTexture.loadFromRenderedText("Decipher the message!", textColor);
	hintTextTexture.loadFromRenderedText(hint, textColor);
	attemptsTextTexture.loadFromRenderedText("Attempts: 0", textColor);
}

int crypto::play()
{
	bool quit = false;
	if(!loadMedia())
	{
		return -1;
	}
	displayPrescreen(quit);
	
	bool enter = false;
	bool gameover = false;
	int attempts = 0;
	char buffer[20];
	prepareGame();
	// Actual Game
	while(!gameover && !quit)
	{
		enter = false;
		manageEvents(answer, quit, enter);
		display(attempts);
		if(enter)
		{
			attempts++;
			sprintf(buffer, "Attempts: %i", attempts);
			attemptsTextTexture.loadFromRenderedText(buffer, textColor);
			if(answer == list_of_messages[mes_num])
			{
				gameover = true;	
			}
		}	
	}
	SDL_StopTextInput(); // Disable text Input
	displayEnding(quit);
	// Return amount of points Earned
	if(attempts == 1)
		return 100;
	else if(attempts < 4)
		return 80;
	else if(attempts < 6)
		return 50;
	else if(attempts < 9)
		return 20;
	else
		return 0;
}

void crypto::displayPrescreen(bool &quit)
{
	promptTextTexture.loadFromRenderedTextWrapped("Oh no! The road is blocked! You must decipher the password to continue!", textColor, 550);
	instructionsTextTexture.loadFromRenderedText("Press enter to continue", textColor);
	bool enter = false;
	
	int start_width = 40;
	int start_height =345;
	
	SDL_Event e;
	while(!enter && !quit)
	{
			// Manage Events
			while( SDL_PollEvent( &e ) != 0 )
			{
		    	if( e.type == SDL_KEYDOWN )
		    	{
		        	if( e.key.keysym.sym == SDLK_RETURN )
		        		enter = true;
		        }
		         else if( e.type == SDL_QUIT)
       			 {
        			quit = true;
        			break;
        		}
		    }
		    SDL_RenderClear(gRenderer);
		    background1Texture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
		    promptTextTexture.render(start_width, start_height);
		    instructionsTextTexture.render(start_width, start_height + promptTextTexture.getHeight() + 5);
		    SDL_RenderPresent( gRenderer );
		    
	}
	
	
}

void crypto::display(int attempts)
{
	SDL_RenderClear( gRenderer );
	
	int start_height = 30;
	int start_width = 25;
	int space = 15;
	
	background2Texture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
	instructionsTextTexture.render(start_width, start_height);
	promptTextTexture.render(start_width, start_height + fontSize + 5 + space);
	if(attempts > 3)
	{
		hintTextTexture.render(start_width, start_height + promptTextTexture.getHeight()+ fontSize + space*2);
	}
	
	if(attempts > 0)
	{
		wrongTextTexture.render(start_width, start_height + promptTextTexture.getHeight()+ fontSize*2 + space*3);
	}
	inputTextTexture.render(start_width, start_height + promptTextTexture.getHeight() + fontSize*3 + space*4);
	attemptsTextTexture.render(start_width, SCREEN_HEIGHT - 40);
	SDL_RenderPresent( gRenderer );
}
bool crypto::loadMedia()
{
	 //Loading success flag
    bool success = true;
    
    //Open background pictures
    if( !background1Texture.loadFromFile( "Puzzles/cryptography/blockedroad.png"))
    {
        printf( "Failed to load background texture!\n" );
        success = false;
    }
    if( !background2Texture.loadFromFile( "Puzzles/cryptography/cryptography.png"))
    {
        printf( "Failed to load background texture!\n" );
        success = false;
    }
    if( !background3Texture.loadFromFile( "Puzzles/cryptography/unlock.png"))
    {
        printf( "Failed to load background texture!\n" );
        success = false;
    }
   
    //Open the font
    fontSize = 25;
    font = TTF_OpenFont( "adamwarrenpro.ttf", fontSize);
    if( font == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        textColor = { 0, 0, 0, 0xFF };
        promptTextTexture.setFont(font);
        inputTextTexture.setFont(font);
        hintTextTexture.setFont(font);
        wrongTextTexture.setFont(font);
        instructionsTextTexture.setFont(font);
        attemptsTextTexture.setFont(font);
    }
    
    
    return success;
    
}



void crypto::manageEvents(string& answer, bool& quit, bool& enter) 
{

    //Main loop flag
    bool success = true;

    //Event handler
    SDL_Event e;

    //The rerender text flag
    bool renderText = false;

    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //Special key input
        if( e.type == SDL_KEYDOWN )
        {
            //Handle backspace
            if( e.key.keysym.sym == SDLK_BACKSPACE && answer.length() > 0 )
            {
                //lop off character
                answer.pop_back();
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
            //Append character
            if(answer.size() < 31)
            {
              	answer += e.text.text;
               	renderText = true;
            }
            
        }
        else if( e.type == SDL_QUIT)
        {
        	quit = true;
        	break;
        }
    }

    //Rerender text if needed
    if( renderText )
    {
        //Text is not empty
        if( answer != "" )
        {
            //Render new text
            inputTextTexture.loadFromRenderedText( answer.c_str(), textColor );
        }
        //Text is empty
        else
        {
            //Render space texture
            inputTextTexture.loadFromRenderedText( " ", textColor );
        }
    }
}

void crypto::displayEnding(bool &quit)
{
	promptTextTexture.loadFromRenderedTextWrapped("Congratulations! You solved the puzzle!", textColor, 300);
	instructionsTextTexture.loadFromRenderedText("Press enter to continue", textColor);
	bool enter = false;
	
	int start_width = 20;
	int start_height =170;
	
	SDL_Event e;
	while(!enter && !quit)
	{
			// Manage Events
			while( SDL_PollEvent( &e ) != 0 )
			{
		    	if( e.type == SDL_KEYDOWN )
		        {
		        	if( e.key.keysym.sym == SDLK_RETURN )
		        		enter = true;
		        }
		        else if(e.type == SDL_QUIT)
		        {
		        	quit = true;
		        	break;
		        }
		    }
		    SDL_RenderClear(gRenderer);
		    background3Texture.render(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
		    promptTextTexture.render(start_width, start_height);
		    instructionsTextTexture.render(start_width, start_height + promptTextTexture.getHeight() + 20);
		    SDL_RenderPresent( gRenderer );
		    
	}
}

