/*
 *  music.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2010-08-17.
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
 */

#include <iostream>

#include "music.h"

#include "SDL.h"
#include "SDL_image/SDL_image.h"

#include "lib.h"

Music::Music(Game *game): Sprite(game)
{
	_is_playing = Lib::loadImage("sound.png");
	_is_mute = Lib::loadImage("mute.png");
	
	_image = _game->isPlayingMusic() ? _is_playing : _is_mute;
	
	_default_pos.x = _game->size()->w - _is_playing->clip_rect.w - 10;
	_default_pos.y = _game->size()->h - _is_playing->clip_rect.h - 10;
	
	_paused_pos.x = _game->size()->w - _is_playing->clip_rect.w - 10;
	_paused_pos.y = 10;
	
	_rect.x = _default_pos.x;
	_rect.y = _default_pos.y;
}

void Music::tick()
{
	_image = _game->isPlayingMusic() ? _is_playing : _is_mute;
	
	if ( _game->isPaused() )
	{
		_rect.x = _paused_pos.x;
		_rect.y = _paused_pos.y;
	}
	else
	{
		_rect.x = _default_pos.x;
		_rect.y = _default_pos.y;
	}

}

void Music::draw()
{
	SDL_BlitSurface(_image, NULL, _game->buffer(), &_rect);
}

void Music::handleEvent(const SDL_Event &event)
{
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if ( collidesWith(event.button.x, event.button.y) ) {
				_game->toggleMusic();
			}
			break;
	}
}
