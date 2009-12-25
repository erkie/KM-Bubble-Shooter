/*
 *  points.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-20.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>

#include "mysdl.h"
#include "game.h"
#include "points.h"

Points::Points(Game *game): Drawable(game), _last_points(0), _image(NULL)
{
	_font = load_font(20);
	
	_font_color.r = _font_color.g = _font_color.b = 0xFF;
	
	renderPoints(0);
}

void Points::renderPoints(long points)
{
	_last_points = points;
	
	std::stringstream pstr;
	pstr << _last_points << " points";
	
	if ( _image )
		SDL_FreeSurface(_image);
	_image = TTF_RenderText_Blended(_font, pstr.str().c_str(), _font_color);
	
	_pos = _image->clip_rect;
	_pos.x = _game->size()->w - _pos.w - 10;
	_pos.y = _game->size()->h - _pos.h - 10;
}

void Points::tick()
{
	long points = _game->points();
	if ( _last_points != points )
	{
		renderPoints(points);
	}
}

void Points::draw()
{
	SDL_BlitSurface(_image, NULL, _game->buffer(), &_pos);
}
