/*
 *  inputnode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "mysdl.h"
#include "unicode.h"
#include "highscoremanager.h"

#include "highscorescreen.h"

#include "game.h"
#include "menu.h"
#include "screen.h"
#include "inputnode.h"

InputNode::InputNode(Screen *screen): Abstract::InputNode(screen)
{
	// Load font
	loadFont(16, 54, 64, 66);
	
	// (Input field) Position is everything
	_pos.x = 2 + 5;
	_pos.y = 71 + 6;
	_pos.w = 132;
	_pos.h = 31;
	
	str("Your name...");
	
	init();
}

void InputNode::onclick()
{
	empty();
}

void InputNode::ontype(Uint16 code, SDLKey k)
{
	addChar(code, k);
	((HighscoreScreen*)_screen)->name(_str);
	
	if ( k == SDLK_RETURN )
	{
		submit();
	}
}

void InputNode::onfocus()
{
	_screen->menu()->game()->holdKeyEvents(true);
}

void InputNode::onblur()
{
	_screen->menu()->game()->holdKeyEvents(false);
}

void InputNode::submit()
{
	((HighscoreScreen*)_screen)->submit();
}
