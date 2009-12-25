/*
 *  game.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-18.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>
#include <algorithm>

#include "SDL_mixer/SDL_mixer.h"

#include "sound.h"
#include "game.h"
#include "drawable.h"

#include "background.h"
#include "arrow.h"
#include "ball.h"
#include "grid.h"
#include "points.h"
#include "menu.h"

Game::Game()
{
	std::cout << "Game() called" << std::endl;
}

Game::Game(SDL_Surface *screen): _running(true), _screen(screen), _points(0), _last_points(0), _points_quantifier(0), _is_paused(false), _is_dirty(false), _volume(MIX_MAX_VOLUME * 0.6)
{	
	_size = &_screen->clip_rect;
	
	// Create buffer for drawing
	_buffer = SDL_DisplayFormatAlpha(_screen);
	
	// Init FPS capping
	_fps = GAME_FPS;
	_last_ticks = 0;
	
	// Create base drawables
	_arrow = new Arrow(this);
	_background = new Background(this);
	_grid = new Grid(this);
	_points_drawable = new Points(this);
	_menu = new Menu(this);
	
	_drawables.push_back(_background);
	_drawables.push_back(_arrow);
	_drawables.push_back(_grid);
	_drawables.push_back(_points_drawable);
	_drawables.push_back(_menu);
	
	Mix_Volume(-1, _volume);
	
	// Begin game
	reset();
}

void Game::start()
{
	_is_paused = false;
}

void Game::togglePause()
{
	if ( _is_paused )
		start();
	else
		pause();

}

void Game::pause()
{
	_is_paused = true;
}

void Game::addDrawable(Drawable *drawable)
{
	_add_queue.push_back(drawable);
}

void Game::removeDrawable(Drawable *drawable)
{
	_is_dirty = true;
	_rem_queue.push_back(drawable);
}

void Game::clearBuffer()
{
	SDL_FillRect(_buffer, &_buffer->clip_rect, SDL_MapRGB(_buffer->format, 0xFF, 0xFF, 0xFF));
}

void Game::loop()
{
	while ( _running )
	{
		clearBuffer();
		
		draw();
		tick();
		cleanupList();
		
		cap();
	}
}

void Game::cap()
{
	Uint32 curr_ticks = SDL_GetTicks();
	int time_passed = curr_ticks - _last_ticks;
	int delay = 0;
	
	if ( _fps > 0 )
	{
		delay = (1000 / _fps) - time_passed;
		if ( delay > 0 )
		{
			SDL_Delay(delay);
			time_passed += delay;
		}
	}
	
	_last_ticks = curr_ticks;
	
	if ( delay > 0 )
		time_passed -= delay;
	
	_tdelta = double(time_passed) / 1000.0;
}

void Game::cleanupList()
{
	// Remove elements from remove queue
	while ( ! _rem_queue.empty() )
	{
		Drawable *d = _rem_queue.front();
		_drawables.remove(d);
		_rem_queue.pop_front();
	}
	
	// Add new elements
	while ( ! _add_queue.empty() )
	{
		_drawables.push_back(_add_queue.front());
		_add_queue.pop_front();
	}
	
	_is_dirty = false;	
}

void Game::handleEvents()
{
	while ( SDL_PollEvent(&_event) )
	{
		// Handle sprites' events
		for ( list::iterator iter = _drawables.begin(); iter != _drawables.end(); iter++ )
			(**iter).handleEvent(_event);
		
		// Default events
		switch ( _event.type )
		{
			case SDL_KEYDOWN:
				if ( _event.key.keysym.sym == SDLK_p && ! isPaused() )
				{
					_menu->showScreen(Menu::Home);
					togglePause();
				}
				else if ( _event.key.keysym.sym == SDLK_n )
				{
					//Mix_Pause(-1);
				}
				else if ( _event.key.keysym.sym == SDLK_m )
				{
					//Mix_Resume(-1);
				}
				else if ( _event.key.keysym.sym == SDLK_j )
				{
					_volume -= 10;
					Mix_Volume(-1, _volume);
				}
				else if ( _event.key.keysym.sym == SDLK_k )
				{
					_volume += 10;
					Mix_Volume(-1, _volume);
				}

				break;
			case SDL_QUIT:
				_running = false;
				break;

		}
	}
}

void Game::draw()
{
	for ( list::iterator iter = _drawables.begin(); iter != _drawables.end(); iter++ )
		(**iter).draw();

	SDL_BlitSurface(_buffer, &_buffer->clip_rect, _screen, &_screen->clip_rect);
	SDL_Flip(_screen);
}

void Game::tick()
{
	handleEvents();
	
	// Tick each sprite
	for ( list::iterator iter = _drawables.begin(); iter != _drawables.end(); iter++ )
	{
		// The count-call is mostly a sanity check
		if ( ! _is_dirty || (_is_dirty && count(_rem_queue.begin(), _rem_queue.end(), *iter) == 0 ) )
			(*iter)->tick();
	}
}

/* Gameplay-related */

void Game::checkRowCount()
{
	if ( _grid->countRows() >= BALL_GRID_H )
	{
		lost();
	}
}

void Game::decrementLives()
{
	_lives[0]--;
	if ( _lives[0] <= 0 )
	{
		_grid->generateRow(1);
		
		if ( _lives[1] <= 1 )
		{
			_lives[0] = _lives[1] = GAME_LIVES;
		}
		else
		{
			_lives[0] = --_lives[1];
		}
		// checkRowCount();
	}
}

void Game::lost()
{
	play_lose();
	
	_last_points = _points;
	_menu->showScreen(Menu::Home);
	pause();
	reset();
}

void Game::reset()
{
	_grid->emptyRows();
	_grid->generateStartRows();
	_lives[0] = _lives[1] = _lives[2] = GAME_LIVES;
	_points = 0;
	_arrow->setReady(true);
}

void Game::addPointsNormal()
{
	_points += 10 * (int(_points_quantifier / 3) + 1);
	_points_quantifier += 1;
}

void Game::addPointsJumbo()
{
	_points += 100;
}

Game::~Game()
{
	for ( list::iterator iter = _drawables.begin(); iter != _drawables.end(); iter++ )
		delete *iter;
}
