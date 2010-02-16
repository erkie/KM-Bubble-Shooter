/*
 *  node.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include "SDL.h"

class Screen;

class Node
{
protected:
	SDL_Surface *_image;
	SDL_Rect _pos, _scroll;
	
	bool _is_focused;
	
	Screen *_screen;
public:
	Node(Screen *screen);
	
	// Draw myself onto surface
	virtual void draw(SDL_Surface *surface);
	
	void focus(bool is) { _is_focused = is; };
	
	bool collidesWith(int x, int y) { return x > _pos.x && y > _pos.y && x < _pos.x + _pos.w && y < _pos.y + _pos.h; };
	
	// Events
	virtual void onclick() {};
	virtual void onhover() {};
	virtual void ontype(Uint16 key, SDLKey k) {};
	virtual void onshow() {};
	virtual void ondrag(int relx, int rely) {};
	virtual void onscroll(bool up) {};
	virtual void onfocus() {};
	virtual void onblur() {};
};

#endif
