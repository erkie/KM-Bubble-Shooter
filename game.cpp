/*
 *  game.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-18.
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

#include <iostream>
#include <algorithm>

#include "SDL_mixer.h"
#include "SDL_image.h"

#include "sound.h"
#include "game.h"
#include "sprite.h"

#include "background.h"
#include "arrow.h"
#include "ball.h"
#include "grid.h"
#include "points.h"
#include "menu.h"
#include "music.h"

const int START_VOLUME = MIX_MAX_VOLUME / 2 / 2; // 10th power of 2
const int MAX_VOLUME = MIX_MAX_VOLUME; // 12th power of 2

Game::Game()
{
	std::cout << "Game() called" << std::endl;
}

Game::Game(SDL_Surface *screen): _running(true), _screen(screen), _points(0), _last_points(0), _points_quantifier(0)
	, _is_paused(false), _is_dirty(false), _volume(START_VOLUME), _is_recording(false), _is_playing(false)
	, _hold_key_events(false), _redraw(true), _rec_slow(0)
{
	_size = &_screen->clip_rect;

	// Create buffer for drawing
	_buffer = SDL_DisplayFormatAlpha(_screen);

	// Init FPS capping
	_fps = GAME_FPS;
	_last_ticks = 0;

	// Create base sprites
	_arrow = new Arrow(this);
	_background = new Background(this);
	_grid = new Grid(this);
	_points_sprite = new Points(this);
	_menu = new Menu(this);
	_music = new Music(this);

	_sprites.push_back(_background);
	_sprites.push_back(_arrow);
	_sprites.push_back(_grid);
	_sprites.push_back(_points_sprite);
	_sprites.push_back(_menu);
	_sprites.push_back(_music);

	setVolume();
	play_music();

	// Begin game
	reset();

	// Recording
	_recording = IMG_Load("recording.png");
	_playing = IMG_Load("playing.png");

	for ( int i = 0; i < GAME_RECORD_FRAMES; i++ )
		_rec_frames[i] = NULL;
}

void Game::start()
{
	_is_paused = false;
	_fps = GAME_FPS;
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
	_fps = PAUSE_FPS;
}

void Game::addSprite(Sprite *sprite)
{
	_add_queue.push_back(sprite);
}

void Game::removeSprite(Sprite *sprite)
{
	_is_dirty = true;
	_rem_queue.push_back(sprite);
}

void Game::loop()
{
	while ( _running )
	{
		if ( _redraw || _is_playing )
		{
			draw();
		}
		_redraw = false;

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
	if ( ! _rem_queue.empty() )
		_redraw = true;

	// Loop through rem queue and find things in add queue that have been removed already
	for ( queue::iterator iter = _rem_queue.begin(); iter != _rem_queue.end(); iter++ )
	{
		for ( queue::iterator aiter = _add_queue.begin(); aiter != _add_queue.end(); aiter++ )
		{
			if ( (*aiter)->ID == (*iter)->ID )
			{
				_add_queue.erase(aiter);
			}
		}
	}

	// Remove elements from remove queue
	while ( ! _rem_queue.empty() )
	{
		Sprite *d = _rem_queue.front();
		_rem_queue.pop_front();

		_sprites.remove(d);
		delete d;
	}

	// Add new elements
	while ( ! _add_queue.empty() )
	{
		_sprites.push_back(_add_queue.front());
		_add_queue.pop_front();
	}

	_is_dirty = false;
}

void Game::handleEvents()
{
	while ( SDL_PollEvent(&_event) )
	{
		// Handle the sprites' events
		for ( list::iterator iter = _sprites.begin(); iter != _sprites.end(); iter++ )
		{
			(*iter)->preTick();
			(*iter)->handleEvent(_event);
			(*iter)->postTick();

			if ( (*iter)->dirty() )
			{
				_redraw = true;
			}
		}

		// Default events
		switch ( _event.type )
		{
			case SDL_KEYDOWN:
				if ( _event.key.keysym.sym == SDLK_q )
				{
					Uint8* keyState = SDL_GetKeyState(NULL);
					if ( keyState[SDLK_LMETA] || keyState[SDLK_RMETA] )
						_running = false;
				}
				if ( _event.key.keysym.sym == SDLK_p && ! _hold_key_events )
				{
					_menu->showScreen(Menu::Home);
					togglePause();
				}
				else if ( _event.key.keysym.sym == SDLK_m && ! _hold_key_events )
				{
					toggleMusic();
				}
				else if ( _event.key.keysym.sym == SDLK_j && ! _hold_key_events )
				{
					volumeDown();
				}
				else if ( _event.key.keysym.sym == SDLK_k && ! _hold_key_events )
				{
					volumeUp();
				}
				else if ( _event.key.keysym.sym == SDLK_r && ! _hold_key_events )
					recStart();
				else if ( _event.key.keysym.sym == SDLK_t && ! _hold_key_events )
					recPlay();
				else if ( _event.key.keysym.sym == SDLK_a )
					_arrow->current()->active();

				break;
			case SDL_QUIT:
				_running = false;
				break;

		}
	}
}

void Game::draw()
{
	if ( _is_playing )
		recFrame();
	else
		for ( list::iterator iter = _sprites.begin(); iter != _sprites.end(); iter++ )
			(**iter).draw();

	rec();

	if ( (_is_recording || _is_playing) && _rec_slow++ % 10 == 0 )
	{
		SDL_Rect place;
		place.x = _buffer->clip_rect.w - 70;
		place.y = _buffer->clip_rect.h - 70;
		if ( _is_recording )
			SDL_BlitSurface(_recording, NULL, _buffer, &place);
		else
			SDL_BlitSurface(_playing, NULL, _buffer, &place);
	}

	SDL_BlitSurface(_buffer, &_buffer->clip_rect, _screen, &_screen->clip_rect);
	SDL_Flip(_screen);
}

void Game::tick()
{
	handleEvents();

	// Tick each sprite
	for ( list::iterator iter = _sprites.begin(); iter != _sprites.end(); iter++ )
	{
		// The count-call is mostly a sanity check
		if ( ! _is_dirty || (_is_dirty && count(_rem_queue.begin(), _rem_queue.end(), *iter) == 0 ) )
		{
			(*iter)->preTick();
			(*iter)->tick();
			(*iter)->postTick();

			if ( (*iter)->dirty() )
			{
				_redraw = true;
			}
		}
	}
}

void Game::setVolume()
{
	Mix_Volume(-1, (float)_volume / (float)MAX_VOLUME * MIX_MAX_VOLUME);
	Mix_VolumeMusic((float)_volume / (float)MAX_VOLUME * MIX_MAX_VOLUME);
}

void Game::volumeUp()
{
	_volume *= 2;
	_volume = _volume > MAX_VOLUME ? MAX_VOLUME : _volume;
	_volume = _volume == 0 ? 2 : _volume;

	setVolume();
}

void Game::volumeDown()
{
	_volume /= 2;
	setVolume();
}

bool Game::toggleMusic()
{
	if ( ! Mix_PausedMusic() ) {
		Mix_PauseMusic();
		SDL_PauseAudio(1);
		return false;
	}
	SDL_PauseAudio(0);
	Mix_ResumeMusic();
	return true;
}

bool Game::isPlayingMusic()
{
	return ! Mix_PausedMusic();
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

	showSubmit();
	pause();

	reset();
}

void Game::win()
{
	play_win();

	_points *= 2;
	showSubmit();
	pause();

	reset();
}

void Game::showSubmit()
{
	_last_points = _points;
	_menu->showScreen(Menu::Submit);
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

void Game::rec()
{
	if ( ! _is_recording )
		return;

	_current_frame++;

	if ( _current_frame >= GAME_RECORD_FRAMES )
		recEnd();
	else
	{
		_rec_frames[_current_frame] = SDL_DisplayFormat(_buffer);
	}
}

void Game::recStart()
{
	std::cout << "Start recording" << std::endl;

	// Clear old recordings
	for ( int i = 0; i < GAME_RECORD_FRAMES; i++ )
	{
		SDL_FreeSurface(_rec_frames[i]);
		_rec_frames[i] = NULL;
	}

	_is_recording = true;
	_current_frame = 0;

	for ( int i = 0; i < GAME_RECORD_FRAMES; i++ )
		_rec_frames[i] = NULL;
}

void Game::recEnd()
{
	std::cout << "End recording" << std::endl;

	_is_recording = false;
}

void Game::recPlay()
{
	std::cout << "Starting playback" << std::endl;

	_is_playing = true;
	_play_frame = 0;
}

void Game::recStop()
{
	std::cout << "Ended playback\n";

	_is_playing = false;
}

void Game::recFrame()
{
	_play_frame++;

	if ( _play_frame >= GAME_RECORD_FRAMES )
		recStop();
	else
	{
		SDL_BlitSurface(_rec_frames[_play_frame], NULL, _buffer, NULL);
	}
}

Game::~Game()
{
	for ( list::iterator iter = _sprites.begin(); iter != _sprites.end(); iter++ )
		delete *iter;
}
