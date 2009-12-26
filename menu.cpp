/*
 *  menu.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-21.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include "SDL.h"
#include "SDL_image/SDL_image.h"

#include "mysdl.h"
#include "homescreen.h"
#include "highscorescreen.h"
#include "highscoremanager.h"

#include "game.h"
#include "screen.h"
#include "menu.h"

Menu::Menu(Game *game): Drawable(game), _current_screen(NULL)
{
	// Initialize overlay
	_overlay = IMG_Load("menu.png");
	
	// Add screens
	_screens[Home] = new HomeScreen(this);
	_screens[Submit] = new HighscoreScreen(this);

	_current_screen = _screens[Home];
	
	manager.load();
	highscore_list scores = manager.get();
}

void Menu::tick() {}

void Menu::draw()
{
	if ( ! _game->isPaused() )
		return;
	
	// Draw overlay
	SDL_BlitSurface(_overlay, NULL, _game->buffer(), NULL);
	
	// Draw screens
	if ( _current_screen )
		_current_screen->draw(_game->buffer());
}

void Menu::handleEvent(const SDL_Event &event)
{
	if ( ! _game->isPaused() || ! _current_screen )
		return;
	
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if ( event.button.button != SDL_BUTTON_WHEELDOWN && event.button.button != SDL_BUTTON_WHEELUP )
			{
				_current_screen->fireEvent(Screen::Down, event);
			}
			else
			{
				_current_screen->fireEvent(Screen::Scroll, event);
			}

			break;
		case SDL_MOUSEMOTION:
			_current_screen->fireEvent(Screen::Move, event);
			break;
			
		case SDL_MOUSEBUTTONUP:
			_current_screen->fireEvent(Screen::Click, event);
			break;
		
		case SDL_KEYDOWN:
			_current_screen->fireEvent(Screen::Type, event);
			break;
	}
}

void Menu::showScreen(MenuScreen menu)
{
	_current_screen = _screens[menu];
	_current_screen->fireEvent(Screen::Show);
	if ( menu == Submit )
	{
		((HighscoreScreen*)_current_screen)->renderPointsText();
	}
}
