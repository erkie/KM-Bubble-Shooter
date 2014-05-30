/*
 *  points.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-20.
 *  Copyright (c) 2010 Erik Andersson
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
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
	_rect.x = _game->size()->w - _rect.w - 40;
	_rect.y = _game->size()->h - _rect.h - 10;
}

void Points::tick()
{
	if ( _game->isPaused() )
		return;

	long points = _game->points();
	if ( _last_points != points )
	{
		renderPoints(points);
	}
}

void Points::draw()
{
	if ( _game->isPaused() )
		return;

	SDL_BlitSurface(_image, NULL, _game->buffer(), &_rect);
}
