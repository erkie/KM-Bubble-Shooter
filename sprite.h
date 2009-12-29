/*
 *  sprite.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-18.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <iostream>
#include "SDL.h"

class Game;

class Sprite
{
protected:
	Game *_game;
public:
	Sprite() {};
	Sprite(Game *game): _game(game) {};
	
	virtual void handleEvent(const SDL_Event &event) {};
	virtual void tick() = 0;
	virtual void draw() = 0;
	
	Game *game() { return _game; };
};

#endif
