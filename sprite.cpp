/*
 *  sprite.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-30.
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

#include "mysdl.h"
#include "game.h"
#include "sprite.h"

void Sprite::setImage(SDL_Surface *s)
{
	_image = s;
	_is_dirty = true;
}

void Sprite::preTick()
{
	_is_dirty = false;
	_old_rect = _rect;
	_old_image = _image;
}

void Sprite::postTick()
{
	if ( _old_rect.x != _rect.x || _old_rect.y != _rect.y || _old_rect.w != _rect.w || _old_rect.h != _rect.h || _old_image != _image )
	{
		_is_dirty = true;
	}
}
