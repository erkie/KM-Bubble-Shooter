/*
	<kattMickisShooter>
	Bubble Shooter clone for kattMickis
 
	By: Erik Andersson
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"
#include "SDL_mixer/SDL_mixer.h"

#include "unicode.h"

#include "game.h"

const int SCREEN_WIDTH = 403;
const int SCREEN_HEIGHT = 405;
const int SCREEN_BPP = 32;

int main(int argc, char *argv[])
{
	/*using namespace std;
	Uint16 text[40];
	for ( int i = 0; i < 40; i++ )
		text[i] = '\0';
	
	cout << "Testing length:\n";
	cout << uni_length(text) << endl;
	
	text[0] = 'h';
	cout << uni_length(text) << endl;
	
	text[1] = 'e';
	cout << uni_length(text) << endl;
	
	text[2] = 'l';
	text[3] = 'l';
	
	cout << "Testing placing characters in arrays\n";
	uni_place(text, 's', 40, 0);
	
	for ( int i = 0; i < 40; i++ )
		cout << (char)i[text];
	cout << endl;
	
	for ( int i = 5; i < 40; i++ )
		text[i] = 'a';
	uni_place(text, 'z', 40, 38);
	
	for ( int i = 0; i < 40; i++ )
		cout << (char)i[text];
	endl(cout);
	
	cout << "<empty string>\n";
	for ( int i = 0; i < 40; i++ )
		text[i] = '\0';
	
	for ( int i = 0; i < 5; i++ )
		uni_place(text, 'a' + i, 40, i);
	
	for ( int i = 0; i < 40; i++ )
		cout << (char)i[text];
	endl(cout);
	
	uni_slice(text, 40, 2);
	for ( int i = 0; i < 40; i++ )
		cout << (char)i[text];
	
	return 0;*/
	
	// Seed random number generator
	srand(time(NULL));
	
	// Init SDL
	Uint32 init_flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
	Uint32 screen_flags = SDL_HWSURFACE;
	
	if ( SDL_Init(init_flags) < 0 )
	{
		std::cout << "Error initializing SDL: " << SDL_GetError();
		return 1;
	}
	
	SDL_EnableUNICODE(1);
	
	if ( TTF_Init() < 0 )
	{
		std::cout << "Error initializing TTF: " << TTF_GetError();
		return 2;
	}
	
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 1024;
	
	if ( Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0 )
	{
		std::cout << "Error initialize audio: " << Mix_GetError();
		return 3;
	}
	
	// Enable key repeat
	SDL_EnableKeyRepeat(250, 100);
	
	SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screen_flags);
	if ( screen == NULL )
	{
		std::cout << "Error creating screen: " << SDL_GetError();
		return 4;
	}
	
	SDL_WM_SetCaption("kattMickis Bubble Shooter", NULL);
	
	Game game = Game(screen);
	game.setWidth(SCREEN_WIDTH);
	game.setHeight(SCREEN_HEIGHT);
	game.loop();
	
	return 0;
}
