/*
 *  homescreen.cpp
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

#include "SDL.h"
#include "SDL_image/SDL_image.h"

#include "highscoremanager.h"

// Nodes
#include "continuenode.h"
#include "newgamenode.h"
#include "settingsnode.h"
#include "highscorenode.h"

#include "homescreen.h"

HomeScreen::HomeScreen(Menu *menu): Screen(menu)
{
	_pos.w = 308;
	_pos.h = 170;
	_pos.x = _menu->centerX() - _pos.w / 2;
	_pos.y = _menu->centerY() - _pos.h / 2 + 20;
	
	addNode(new ContinueNode(this));
	addNode(new NewGameNode(this));
	//addNode(new SettingsNode(this));
	addNode(new HighscoreNode(this));
}

void HomeScreen::draw(SDL_Surface *surface)
{
	drawNodes(surface);
}
