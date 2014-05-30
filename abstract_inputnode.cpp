/*
 *  abstract_inputnode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2010-03-04.
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

#include "SDL.h"
#include "SDL/SDL_ttf.h"

#include "mysdl.h"
#include "unicode.h"
#include "highscoremanager.h"

#include "highscorescreen.h"

#include "game.h"
#include "menu.h"
#include "screen.h"
#include "inputnode.h"

#include "abstract_inputnode.h"

namespace Abstract
{
	InputNode::InputNode(Screen *screen): Node(screen), _curr_index(0)
	{

	}

	// Init must be called after positions are set
	// This totally defeats the purpose of a constructor
	void InputNode::init()
	{
		// Create cursor
		_cursor = SDL_CreateRGBSurface(_screen->game()->buffer()->flags, 1, _pos.h - 11, _screen->game()->buffer()->format->BitsPerPixel, NULL, NULL, NULL, NULL);
		SDL_FillRect(_cursor, NULL, SDL_MapRGBA(_cursor->format, 0x66, 0x66, 0x66, 0xCC));

		_cursor_rect = _cursor->clip_rect;
		_cursor_rect.y = 0;

		// Set scroll positions
		_scroll.w = _pos.w - 10;
		_scroll.h = _pos.h;
	}

	void InputNode::loadFont(int size, Uint16 r, Uint16 g, Uint16 b)
	{
		_font = load_font(size);
		_foreground.r = r;
		_foreground.g = g;
		_foreground.b = b;
	}

	void InputNode::draw(SDL_Surface *screen)
	{
		SDL_Rect rect = _screen->makeRect(_pos);
		SDL_BlitSurface(_image, &_scroll, screen, &rect);

		if ( ! _is_focused )
			return;

		rect.x += _cursor_rect.x;
		rect.y += _cursor_rect.y;
		SDL_BlitSurface(_cursor, NULL, screen, &rect);
	}

	void InputNode::renderText()
	{
		if ( _image != NULL )
			SDL_FreeSurface(_image);

		_image = TTF_RenderUNICODE_Blended(_font, _str, _foreground);

		// Account for input text scroll
		if ( _image != NULL && _image->clip_rect.w > _pos.w - 10 )
			_scroll.x = _image->clip_rect.w - _pos.w + 10;
		else
			_scroll.x = 0;

		// Get width of the text string by placing
		// a null byte character up to the point we
		// want to count, then putting the original
		// back. Nice.
		int w;
		Uint16 t = _str[_curr_index];
		_str[_curr_index] = '\0';
		TTF_SizeUNICODE(_font, _str, &w, NULL);
		_str[_curr_index] = t;

		_cursor_rect.x = w - _scroll.x;

		if ( _cursor_rect.x < 0 )
		{
			_scroll.x += _cursor_rect.x;
			_cursor_rect.x = 0;
		}
	}

	void InputNode::addChar(Uint16 code, SDLKey k)
	{
		Uint16 key = code;
		if ( k == SDLK_BACKSPACE )
		{
			_curr_index--;
			if ( _curr_index >= 0 )
				uni_slice(_str, 40, _curr_index);
			else
				_curr_index = 0;
		}
		else if ( k == SDLK_LEFT || k == SDLK_RIGHT || k == SDLK_UP || k == SDLK_DOWN )
		{
			int len = uni_length(_str);

			if ( k == SDLK_LEFT )
				_curr_index--;
			else if ( k == SDLK_RIGHT )
				_curr_index++;
			else if ( k == SDLK_UP )
				_curr_index = 0;
			else
				_curr_index = len;

			if ( _curr_index < 0 )
				_curr_index = 0;
			if ( _curr_index > len )
				_curr_index = len;
		}
		else if ( k == SDLK_RETURN )
		{
			onblur(); // this shouldn't be here, or is it okey? Should menu handle it?
			submit();
			return;
		}
		else if ( _curr_index < 39 && key != 0 )
		{
			// Insert the char into
			uni_place(_str, key, 40, _curr_index);
			_curr_index++;
		}

		renderText();
	}

	void InputNode::str(const char* s)
	{
		int i = 0;
		while ( *s != '\0' && i < 40 )
		{
			_str[i++] = *s;
			s++;
		}
		_str[i] = '\0';

		renderText();
	}

	void InputNode::empty()
	{
		_curr_index = 0;
		str("");
	}
}
