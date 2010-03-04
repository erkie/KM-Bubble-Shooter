/*
 *  menu.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-21.
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

#ifndef __MENU_H__
#define __MENU_H__

#include <vector>

#include "SDL.h"

#include "highscoremanager.h"

#include "game.h"
#include "sprite.h"

class Screen;

const int NUM_SCREENS = 3;

class Menu: public Sprite
{
private:
	SDL_Surface *_overlay;
	Screen *_screens[3];
	Screen *_current_screen;
public:
	enum MenuScreen {Home, Submit, Settings};
	
	Menu(Game *game);
	void tick();
	void draw();
	void handleEvent(const SDL_Event &event);
	
	void showScreen(MenuScreen screen);
	
	int centerX() { return _game->size()->w / 2; };
	int centerY() { return _game->size()->h / 2; };
	
	SDL_Surface *overlay() { return _overlay; };
	
	HighscoreManager manager;
};

#endif
