//
//  texture.cpp


#include "texture.h"
#include <iostream>
using namespace std;


LTexture::LTexture(SDL_Window *ngWindow, SDL_Renderer *ngRenderer, TTF_Font* nFont):
    gFont(nFont)
{
    //Initialize
    SDL_GetWindowSize(ngWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    gRenderer = ngRenderer;
    gWindow = ngWindow;
}

bool LTexture::loadFromFile(string path)
{
    bool success;
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    success = (mTexture != NULL);
    return success;
}

bool LTexture::loadFromRenderedText( string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    
    //Return success
    return mTexture != NULL;
}


bool LTexture::loadFromRenderedTextWrapped(string textureText, SDL_Color textColor, int wrapLength)
{
       //Get rid of preexisting texture
    free();
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( gFont, textureText.c_str(), textColor, wrapLength );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    
    //Return success
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
    
}


void LTexture::render( int x, int y, double wprop, double hprop, SDL_Rect* clip ) // Alters image by given proportions
{
    if(mTexture != NULL)
    {
        //Set rendering space and render to screen
        SDL_Rect renderQuad;
        if(clip == NULL)
        {
            renderQuad.x  = x;
            renderQuad.y = y;
            renderQuad.w = mWidth*wprop;
            renderQuad.h = mHeight*hprop;
        }
        else
        {
            renderQuad.x  = x;
            renderQuad.y = y;
            renderQuad.w = (clip->w)*wprop;
            renderQuad.h = (clip->h)*hprop;
        }
        //Render to screen
        SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
    }
}

void LTexture::render( int x, int y, SDL_Rect* clip ) // Renders clip of image in original size
{
    if(mTexture != NULL)
    {
        SDL_Rect renderQuad;
        //Set rendering space and render to screen
        if(clip == NULL)
        {
            renderQuad.x  = x;
            renderQuad.y = y;
            renderQuad.w = mWidth;
            renderQuad.h = mHeight;
        }
        else
        {
            renderQuad.x  = x;
            renderQuad.y = y;
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
    }
}

void LTexture::render( int x, int y, int width, int height, SDL_Rect* clip ) // Renders image in exact given size
{
    if(mTexture != NULL)
    {
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, width, height };

        //Render to screen
        SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
    }
}

void LTexture::setFont(TTF_Font* nFont)
{
    gFont = nFont;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}


int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

