/*
 *  sprite.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-18.
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
 *  THE SOFTWARE. *
 */

#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <iostream>
#include "SDL.h"

class Game;

class Sprite
{
protected:
	static int CID;

	Game *_game;
	bool _is_dirty;
	bool _is_visible;

	SDL_Surface *_image, *_old_image;
	SDL_Rect _rect;
	SDL_Rect _old_rect;

	void setImage(SDL_Surface *surface);
public:
	int ID;

	Sprite() {};
	Sprite(Game *game): _game(game), _is_dirty(true), _is_visible(true), _image(NULL)
	{
		ID = CID++;
	};

	virtual void handleEvent(const SDL_Event &event) {};
	virtual void tick() = 0;
	virtual void draw() = 0;

	void preTick();
	void postTick();

	inline void dirty(bool is) { _is_dirty = is; };
	inline bool dirty() const { return _is_dirty; };

	inline void visible(bool is) { _is_visible = is; };
	inline bool visible() { return _is_visible; };

	Game *game() { return _game; };

	bool collidesWith(SDL_Rect r)
	{
		//      right inside left         top inside bottom         left inside right        bottom inside top
		return r.x + r.w > _rect.x && r.y < _rect.y + _rect.h && r.x < _rect.x + _rect.w && r.y + r.h > _rect.y;
	}

	bool collidesWith(int x, int y)
	{
		return x > _rect.x && y > _rect.y && x < _rect.x + _rect.w && y < _rect.y + _rect.h;
	}
};

#endif
