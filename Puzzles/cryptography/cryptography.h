/* Luis Prieb
 * This class runs the cryptography games. It performs three types of cryptographic
 * encoding of a message and chooses a message from the list of messages.
 */

#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <cctype>
#include <algorithm>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <iterator>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../sharedClasses/texture.h"

using namespace std;

class crypto
{
public:
	crypto(SDL_Window* ngWindow, SDL_Renderer* ngRender );
	~crypto();
	int play();
	
	private:
	// Helper Functions
	string caesar(int rot, string message);
	string ascii(string message);
	string permutation(string message);
	bool loadMedia();
	void displayPrescreen(bool &quit);
	void prepareGame();
	void display(int attempts);
	void manageEvents(string& answer, bool& quit, bool& enter);
	void displayEnding(bool &quit);
	
	// Data Members
	vector<string> list_of_messages;
	string hint;
	string encrypted_mes;
	string answer;
	int mes_num;
	
	// Textures
	LTexture background1Texture;
	LTexture background2Texture;
	LTexture background3Texture;
	LTexture instructionsTextTexture;
	LTexture promptTextTexture;
	LTexture hintTextTexture;
	LTexture inputTextTexture;
	LTexture wrongTextTexture;
	LTexture attemptsTextTexture;
	
	TTF_Font* font;
	int fontSize;
	SDL_Color textColor;
	
	// SDL
	SDL_Renderer* gRenderer;
	SDL_Window* gWindow;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

};

#endif

