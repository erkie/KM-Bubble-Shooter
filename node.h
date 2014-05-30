/*
 *  node.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
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
