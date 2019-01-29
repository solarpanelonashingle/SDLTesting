#include "SDL/SDL.h"
#include "iostream"
#include "cmath"
#include <string>

// set up screen
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;
//The images
SDL_Surface* message = nullptr;
SDL_Surface* background = nullptr;
SDL_Surface* screen = nullptr;

//#include <string>
SDL_Surface *load_image( std::string filename )
{
	//temporary storage for the image that's loaded
	SDL_Surface* loadedImage = nullptr;
	//the optimized image that will be used
	SDL_Surface* optimizedImage = nullptr;
	loadedImage = SDL_LoadBMP( filename.c_str() );

	if ( loadedImage != NULL ) // check to see if the image loaded properly
	{
		optimizedImage = SDL_DisplayFormat( loadedImage );
		SDL_FreeSurface( loadedImage );
	}
	return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
	//make a temporary rectangly to hold the offsets
	SDL_Rect offset;
	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
	//Blit the surface
	SDL_BlitSurface( source, NULL, destination, &offset );
}


int main( int argc, char* args[] )
{
    //Start SDL
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
    	return 1;
    }
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);  
    if( screen == NULL )
    {
    	return 1;
    }

    SDL_WM_SetCaption( "Hello World", NULL );

    message = load_image( "FLAG_B24.BMP" );
    background = load_image( "LAND2.BMP" );

    //apply the background to the screen
    apply_surface( 0, 0, background, screen );
    /*apply_surface(320, 0, background, screen );
    apply_surface( 320, 240, background, screen );*/

    apply_surface( 180, 140, message, screen );

    int SDL_WM_ToggleFullScreen(SDL_Surface *surface);

    //update screen
    if( SDL_Flip( screen ) == -1 )
    {
    	return 1;
    }

    //pause
    SDL_Delay( 2000 );

    //SDL_FreeSurface
    SDL_FreeSurface( message );
    SDL_FreeSurface( background );

    //Quit SDL
    SDL_Quit();
    return 0;    
}