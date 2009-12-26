/*
 *  scorescrollnode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-26.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>
#include <algorithm>

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "screen.h"
#include "mysdl.h"

#include "menu.h"
#include "scorescrollnode.h"

ScoreScrollNode::ScoreScrollNode(Screen *screen): Node(screen)
{	
	_image = NULL;
	
	_xpos = 175;
	_ypos = 30;
	_w = 140;
	_h = 135;
	
	_name_color.r = _name_color.g = _name_color.b = 0xFF;
	_score_color.r = 0xF1;
	_score_color.g = 0x72;
	_score_color.b = 0xB7;
	
	_font = load_font(16);
	
	_scroll_rect.x = 0;
	_scroll_rect.y = 0;
	_scroll_rect.w = _w;
	_scroll_rect.h = _h;
	
	_bg_color.r = _bg_color.b = 0;
	_bg_color.g = 0;
}

void ScoreScrollNode::draw(SDL_Surface *surface)
{
	SDL_Rect rect = _screen->makeRect(_xpos, _ypos);
	SDL_BlitSurface(_image, &_scroll_rect, surface, &rect);
}

void ScoreScrollNode::renderText()
{
	// Init variables
	SDL_Surface *name, *points, *place, *surface;
	surface = _screen->game()->buffer();
	
	Highscore *hs;
	std::stringstream str, str_place;
	
	// The texts position on text
	SDL_Rect position;
	position.x = 0;
	
	// Get scores
	highscore_list &scores = _screen->menu()->manager.get();
	
	// Create surface on which to draw stuff
	int num_scores = scores.size();
	int height = num_scores * 2 * TTF_FontHeight(_font);
	int width = _w;
	
	_height = height;
	
	// Free old text surface (if it exists) and the create new one
	if ( _image )
		SDL_FreeSurface(_image);
	
	_image = SDL_CreateRGBSurface(surface->flags, width, height, surface->format->BitsPerPixel, 0, 0, 0, 0);
	SDL_SetColorKey(_image, SDL_SRCCOLORKEY, SDL_MapRGB(_image->format, 0, 0, 0));
	
	int i = 0;
	for ( highscore_list::iterator iter = scores.begin(); iter != scores.end(); iter++ )
	{
		hs = *iter;
		str << hs->score << " points";
		str_place << (i + 1) << ". ";
		
		// Render texts
		place = TTF_RenderText_Shaded(_font, str_place.str().c_str(), _name_color, _bg_color);
		name = TTF_RenderUNICODE_Shaded(_font, hs->name, _name_color, _bg_color);
		points = TTF_RenderText_Shaded(_font, str.str().c_str(), _score_color, _bg_color);
		
		// Draw position
		position.y = i * name->clip_rect.h * 2;
		SDL_BlitSurface(place, &_image->clip_rect, _image, &position);
		
		// Draw name
		position.x += place->clip_rect.h;
		SDL_BlitSurface(name, &_image->clip_rect, _image, &position);
		
		// Draw score
		position.x = 0;
		position.y += name->clip_rect.h;
		SDL_BlitSurface(points, &_image->clip_rect, _image, &position);
		
		str.str("");
		str_place.str("");
		i++;
		
		SDL_FreeSurface(name);
		SDL_FreeSurface(points);
		SDL_FreeSurface(place);
	}
}

void ScoreScrollNode::onshow()
{
	renderText();
}

void ScoreScrollNode::ondrag(int relx, int rely)
{
	_scroll_rect.y += -rely;
	
	if ( _scroll_rect.y > _height - _h )
		_scroll_rect.y = _height - _h;
	
	if ( _scroll_rect.y < 0 )
		_scroll_rect.y = 0;
}

void ScoreScrollNode::onscroll(bool up)
{
	ondrag(0, (up ? 10 : -10));
}
