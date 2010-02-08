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
	bool _is_dirty;
	bool _is_visible;
	
	SDL_Surface *_image;
	SDL_Rect _rect;
	SDL_Rect _old_rect;
public:
	Sprite() {};
	Sprite(Game *game): _game(game), _is_dirty(true), _is_visible(true), _image(NULL) {};
	
	virtual void handleEvent(const SDL_Event &event) {};
	virtual void tick() = 0;
	virtual void draw() = 0;
	void dirtyDraw();
	
	void preTick();
	void postTick();
	
	inline void dirty(bool is) { _is_dirty = is; };
	inline bool dirty() const { return _is_dirty; };
	
	inline void visible(bool is) { _is_visible = is; };
	inline bool visible() { return _is_visible; };
	
	Game *game() { return _game; };
};

#endif
