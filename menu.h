/*
 *  menu.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-21.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
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

class Menu: public Sprite
{
private:
	SDL_Surface *_overlay;
	Screen *_screens[2];
	Screen *_current_screen;
public:
	enum MenuScreen {Home, Submit};
	
	Menu(Game *game);
	void tick();
	void draw();
	void handleEvent(const SDL_Event &event);
	
	void showScreen(MenuScreen screen);
	
	int centerX() { return _game->size()->w / 2; };
	int centerY() { return _game->size()->h / 2; };
	
	SDL_Surface * overlay() { return _overlay; };
	
	HighscoreManager manager;
};

#endif
