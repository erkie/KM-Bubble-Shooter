/*
 *  menu.cpp
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

#include "SDL.h"
#include "SDL_image.h"

#include "mysdl.h"
#include "homescreen.h"
#include "highscorescreen.h"
#include "settingscreen.h"
#include "highscoremanager.h"

#include "game.h"
#include "screen.h"
#include "menu.h"

Menu::Menu(Game *game): Sprite(game), _current_screen(NULL)
{
	// Initialize overlay
	_overlay = IMG_Load("menu.png");

	// Add screens
	_screens[Home]     = new HomeScreen(this);
	_screens[Submit]   = new HighscoreScreen(this);
	_screens[Settings] = new SettingsScreen(this);

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

	_game->markForRedraw();

	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if ( event.button.button != SDL_BUTTON_WHEELDOWN && event.button.button != SDL_BUTTON_WHEELUP )
				_current_screen->fireEvent(Screen::Down, event);
			else
				_current_screen->fireEvent(Screen::Scroll, event);

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
	if ( menu == Submit )
	{
		if ( ! manager.isHighscore(_game->lastPoints()) )
			menu = Home;
	}

	_current_screen = _screens[menu];
	_current_screen->fireEvent(Screen::Show);

	if ( menu == Submit )
	{
		((HighscoreScreen*)_current_screen)->renderPointsText();
	}

	_game->markForRedraw();
}
