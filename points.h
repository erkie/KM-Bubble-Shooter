/*
 *  points.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-20.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __POINTS_H__
#define __POINTS_H__

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "drawable.h"

class Points: public Drawable
{
private:
	SDL_Surface *_image;
	TTF_Font *_font;
	SDL_Color _font_color;
	
	SDL_Rect _pos;
	
	long _last_points;
public:
	Points(Game *game);
	void tick();
	void draw();
	
	void renderPoints(long points);
};

#endif
