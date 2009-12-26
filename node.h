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
	int _xpos, _ypos;
	int _w, _h;
	
	Screen *_screen;
public:
	Node(Screen *screen): _screen(screen), _image(NULL) {};
	
	// Draw myself onto surface
	virtual void draw(SDL_Surface *surface);
	
	bool collidesWith(int x, int y) { return x > _xpos && y > _ypos && x < _xpos + _w && y < _ypos + _h; };
	
	// Events
	virtual void onclick() {};
	virtual void onhover() {};
	virtual void ontype(Uint16 key, SDLKey k) {};
	virtual void onshow() {};
	virtual void ondrag(int relx, int rely) {};
	virtual void onscroll(bool up) {};
};

#endif
