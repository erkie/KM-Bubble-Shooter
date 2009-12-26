/*
 *  scorescrollnode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-26.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __SCORESCROLLNODE_H__
#define __SCORESCROLLNODE_H__

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "highscoremanager.h"

#include "node.h"

class Screen;

class ScoreScrollNode: public Node
{
private:
	TTF_Font *_font;
	SDL_Color _name_color;
	SDL_Color _score_color;
	SDL_Color _bg_color;
	
	int _height;
	
	SDL_Rect _scroll_rect;
public:
	ScoreScrollNode(Screen *);
	void draw(SDL_Surface *);
	void renderText();
	
	void onshow();
	void ondrag(int relx, int rely);
	void onscroll(bool up);
};

#endif
