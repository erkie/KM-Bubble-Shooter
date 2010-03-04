/*
 *  inputnode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright (c) 2010 Erik Andersson
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
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
