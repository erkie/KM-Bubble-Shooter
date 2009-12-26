/*
 *  highscorescreen.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __HIGHSCORESCREEN_H__
#define __HIGHSCORESCREEN_H__

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "menu.h"
#include "screen.h"

class HighscoreScreen: public Screen
{
private:
	SDL_Surface *_image, *_text, *_points;
	SDL_Rect _controls, _text_rect, _points_rect;
	
	SDL_Color _fg;
	TTF_Font *_font;
	
	Uint16 _name[40];
public:
	HighscoreScreen(Menu *menu);
	
	void name(Uint16 name[40])
	{
		for ( int i = 0; i < 40; i++ )
			_name[i] = name[i];
	};
	
	void draw(SDL_Surface *surface);
	void renderPointsText();
	
	void submit();
};

#endif
