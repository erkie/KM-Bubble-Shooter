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

#include <vector>

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "highscoremanager.h"

#include "node.h"

class Screen;

class ScoreScrollNode: public Node
{
private:
	typedef std::vector<SDL_Surface**> score_triplet_list;
	
	score_triplet_list _scores;
	
	TTF_Font *_font;
	SDL_Color _name_color;
	SDL_Color _score_color;
	SDL_Color _bg_color;
	
	int _font_height, _height;
	
	SDL_Surface *_image;
	SDL_Rect _scroll_rect, _rect;
public:
	ScoreScrollNode(Screen *);
	void draw(SDL_Surface *);
	void renderText();
	
	void onshow();
	void ondrag(int relx, int rely);
	void onscroll(bool up);
};

#endif
