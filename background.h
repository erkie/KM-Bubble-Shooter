/*
 *  background.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-20.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "SDL.h"
#include "drawable.h"

class Background: public Drawable
{
private:
	SDL_Rect _pos;
	Uint32 _color;
public:
	Background(Game *game);
	void draw();
	void tick() {};
	void handleEvent(const SDL_Event &event) {};
	
	Uint32 color() { return _color; };
};

#endif
