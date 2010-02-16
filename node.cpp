/*
 *  node.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>

#include "screen.h"
#include "node.h"

Node::Node(Screen *screen): _screen(screen), _image(NULL)
{
	_scroll.x = _scroll.y = 0;
	_scroll.w = _scroll.h = -1; // I think this means the entire surface. It works atleast...
}

void Node::draw(SDL_Surface *surface)
{	
	SDL_Rect rect = _screen->makeRect(_pos);
	SDL_BlitSurface(_image, &_scroll, surface, &rect);
}
