/*
 *  homescreen.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include "SDL.h"
#include "SDL_image/SDL_image.h"

#include "highscoremanager.h"

// Nodes
#include "continuenode.h"
#include "newgamenode.h"
#include "highscorenode.h"

#include "homescreen.h"

HomeScreen::HomeScreen(Menu *menu): Screen(menu)
{
	// No image needed
	_box = NULL;
	
	_pos.w = 308;
	_pos.h = 170;
	_pos.x = _menu->centerX() - _pos.w / 2;
	_pos.y = _menu->centerY() - _pos.h / 2 + 20;
	
	addNode(new ContinueNode(this));
	addNode(new NewGameNode(this));
	addNode(new HighscoreNode(this));
}

void HomeScreen::draw(SDL_Surface *surface)
{
	SDL_BlitSurface(_box, NULL, surface, &_pos);
	drawNodes(surface);
}
