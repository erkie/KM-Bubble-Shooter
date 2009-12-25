/*
 *  background.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-20.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>

#include "background.h"
#include "game.h"

Background::Background(Game *game): Drawable(game)
{
	_color = SDL_MapRGBA(_game->buffer()->format, 92, 110, 114, SDL_ALPHA_OPAQUE);
}

void Background::draw()
{
	SDL_Surface *buffer = _game->buffer();
	SDL_FillRect(buffer, &buffer->clip_rect, _color);
}
