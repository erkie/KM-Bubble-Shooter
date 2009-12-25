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

#include "game.h"
#include "menu.h"
#include "screen.h"
#include "inputnode.h"

InputNode::InputNode(Screen *screen): Node(screen), _curr_index(0)
{
	// Initialize string
	for ( int i = 0; i < 40; i++ ) _str[i] = 0;
	
	const char *namedotdotdot = "Name...";
	for ( const char* c = namedotdotdot; *c != '\0'; c++, _curr_index++ )
		_str[_curr_index] = *c;
	
	// Load font
	_font = load_font(20);
	_foreground.r = _foreground.g = _foreground.b = 0xFF;
	
	// (Input field) Position is everything
	_xpos = 2;
	_ypos = 71;
	_w = 132;
	_h = 31;
	
	renderText();
}

void InputNode::renderText()
{
	_text = TTF_RenderUNICODE_Blended(_font, _str, _foreground);
}

void InputNode::draw(SDL_Surface *surface)
{
	SDL_Rect rect = _screen->makeRect(_xpos, _ypos);
	rect.x += 5;
	rect.y += 2;
	
	// Blit input text
	SDL_BlitSurface(_text, NULL, surface, &rect);
}

void InputNode::onclick()
{
	for ( int i = 0; i < 40; i++ ) _str[i] = 0;
	_curr_index = 0;
	renderText();
}

void InputNode::ontype(Uint16 code)
{
	Uint16 key = code;
	if ( (code & 0xFF80) == 0 ) // I dunno
	{
		if ( code == 127 )
		{
			_curr_index--;
			if ( _curr_index >= 0 ) 
				_str[_curr_index] = 0;
			else
				_curr_index = 0;
		}
		else if ( code == 13 )
		{
			submit();
			return;
		}
		else if ( _curr_index < 40 && key != 0 )
		{
			_str[_curr_index] = key;
			_curr_index++;
		}
		renderText();
	}
}

void InputNode::submit()
{
	Highscore hs;
	for ( int i = 0; i < 40; i++ )
		hs.name[i] = _str[i];
	hs.score = _screen->game()->lastPoints();
	_screen->menu()->manager.add(hs);
	_screen->menu()->manager.save();
}
