/*
 *  inputnode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "mysdl.h"
#include "highscoremanager.h"

#include "highscorescreen.h"

#include "game.h"
#include "menu.h"
#include "screen.h"
#include "inputnode.h"

InputNode::InputNode(Screen *screen): Node(screen), _curr_index(0), _text(NULL)
{
	// Initialize string
	for ( int i = 0; i < 40; i++ ) _str[i] = 0;
	
	const char *namedotdotdot = " Name...";
	for ( const char* c = namedotdotdot; *c != '\0'; c++, _curr_index++ )
		_str[_curr_index] = *c;
	
	// Load font
	_font = load_font(16);
	_foreground.r = 54;
	_foreground.g = 64;
	_foreground.b = 66;
	
	// (Input field) Position is everything
	_pos.x = 2 + 5;
	_pos.y = 71 + 6;
	_pos.w = 132;
	_pos.h = 31;
	
	renderText();
}

void InputNode::renderText()
{
	if ( _text )
		SDL_FreeSurface(_text);
	_text = TTF_RenderUNICODE_Blended(_font, _str, _foreground);
}

void InputNode::draw(SDL_Surface *surface)
{
	SDL_Rect rect = _screen->makeRect(_pos);
	
	// Blit input text
	SDL_BlitSurface(_text, NULL, surface, &rect);
}

void InputNode::onclick()
{
	for ( int i = 0; i < 40; i++ ) _str[i] = 00E4;
	_curr_index = 0;
	renderText();
}

void InputNode::ontype(Uint16 code, SDLKey k)
{
	Uint16 key = code;
	if ( k == SDLK_BACKSPACE )
	{
		_curr_index--;
		if ( _curr_index >= 0 ) 
			_str[_curr_index] = 0;
		else
			_curr_index = 0;
	}
	else if ( k == SDLK_RETURN )
	{
		submit();
		return;
	}
	else if ( _curr_index < 40 && key != 0 )
	{
		_str[_curr_index] = key;
		_curr_index++;
	}
	((HighscoreScreen*)_screen)->name(_str);
	renderText();
}

void InputNode::submit()
{
	((HighscoreScreen*)_screen)->submit();
}
