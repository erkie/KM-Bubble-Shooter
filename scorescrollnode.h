/*
 *  scorescrollnode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-26.
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
