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

Points::Points(Game *game): Sprite(game), _last_points(0)
{
	_font = load_font(20);
	
	_font_color.r = _font_color.g = _font_color.b = 0xFF;
	
	renderPoints(0);
}

Points::~Points()
{
	SDL_FreeSurface(_image);
}

void Points::renderPoints(long points)
{
	_last_points = points;
	
	std::stringstream pstr;
	pstr << _last_points << " points";
	
	// Clear old image
	if ( _image )
		SDL_FreeSurface(_image);
	
	_image = TTF_RenderText_Blended(_font, pstr.str().c_str(), _font_color);
	
	_rect = _image->clip_rect;
	_rect.x = _game->size()->w - _rect.w - 10;
	_rect.y = _game->size()->h - _rect.h - 10;
}

void Points::tick()
{
	if ( _game->isPaused() )
		return;
	//preTick();
	
	long points = _game->points();
	if ( _last_points != points )
	{
		renderPoints(points);
	}
	
	//postTick();
}

void Points::draw()
{
	if ( _game->isPaused() )
		return;
	//if ( ! dirty() )
	//	return;
	
	SDL_BlitSurface(_image, NULL, _game->buffer(), &_rect);
	//dirtyDraw();
	
	//dirty(false);
}
