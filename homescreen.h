/*
 *  homescreen.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __HOMESCREEN_H__
#define __HOMESCREEN_H__

#include "SDL.h"

#include "menu.h"
#include "screen.h"

class HomeScreen: public Screen
{
private:
	SDL_Surface *_box;
public:
	HomeScreen(Menu *menu);
	void draw(SDL_Surface *);
};

#endif

