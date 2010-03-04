/*
 *  highscorescreen.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
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
