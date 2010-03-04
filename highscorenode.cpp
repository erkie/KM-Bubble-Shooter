/*
 *  highscorenode.cpp
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

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "mysdl.h"

#include "screen.h"
#include "node.h"
#include "scorescrollnode.h"
#include "highscorenode.h"

HighscoreNode::HighscoreNode(Screen *screen): Node(screen)
{
	TTF_Font *font = load_font(16);
	SDL_Color color;
	color.r = color.g = color.b = 0xFF;
	_image = TTF_RenderText_Blended(font, "Highscores", color);
	
	_pos = _image->clip_rect;
	_pos.x = 175;
	_pos.y = 10;
	
	_screen->addNode(new ScoreScrollNode(_screen));
}
