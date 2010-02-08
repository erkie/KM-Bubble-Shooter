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

void Node::draw(SDL_Surface *surface)
{	
	SDL_Rect rect = _screen->makeRect(_pos);
	SDL_BlitSurface(_image, NULL, surface, &rect);
}
