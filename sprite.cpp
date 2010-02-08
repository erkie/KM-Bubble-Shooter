/*
 *  sprite.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-30.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include "mysdl.h"
#include "game.h"
#include "sprite.h"

void Sprite::dirtyDraw()
{
	rect_list dirty_rects = _game->getDirtyRects();
	SDL_Surface *buffer = _game->buffer();
	SDL_Rect intersection, cp;
	
	for ( rect_list::iterator iter = dirty_rects.begin(); iter != dirty_rects.end(); iter++ )
	{
		intersection = get_rect_intersection(_rect, *iter);
		cp = *iter;
		SDL_BlitSurface(_image, &intersection, buffer, &cp);
	}
}

void Sprite::preTick()
{
	_old_rect = _rect;
}

void Sprite::postTick()
{
	if ( _old_rect.x != _rect.x || _old_rect.y != _rect.y || _old_rect.w != _rect.w || _old_rect.h != _rect.h )
	{
		dirty(true);
		
		_game->addDirtyRect(_old_rect);
		_game->addDirtyRect(_rect);
	}
}
