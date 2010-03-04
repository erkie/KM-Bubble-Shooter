/*
 *  background.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-20.
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

#include "background.h"
#include "game.h"

Background::Background(Game *game): Sprite(game)
{
	_color = SDL_MapRGBA(_game->buffer()->format, 92, 110, 114, SDL_ALPHA_OPAQUE);
}

void Background::draw()
{
	if ( _game->isPaused() )
		return;
	
	/*SDL_Surface *buffer = _game->buffer();
	
	rect_list rects = _game->getDirtyRects();
	for ( rect_list::iterator iter = rects.begin(); iter != rects.end(); iter++ )
		SDL_FillRect(buffer, &(*iter), _color);*/
	SDL_FillRect(_game->buffer(), NULL, _color);
}
