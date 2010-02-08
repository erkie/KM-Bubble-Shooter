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

#include "sprite.h"

class Points: public Sprite
{
private:
	TTF_Font *_font;
	SDL_Color _font_color;
	
	long _last_points;
public:
	Points(Game *game);
	~Points();
	void tick();
	void draw();
	
	void renderPoints(long points);
};

#endif
