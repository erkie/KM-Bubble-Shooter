/*
 *  game.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-18.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <list>
#include <queue>

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

const int GAME_FPS = 50;
const int ADJACENT_BALLS = 3;
const int GAME_LIVES = 6;

class Grid;
class Arrow;
class Sprite;
class Background;
class Points;
class Menu;

class Game
{
private:
	typedef std::list<Sprite*> list;
	//typedef std::queue<Sprite*> queue;
	typedef list queue;
	
	SDL_Surface *_screen;
	SDL_Surface *_buffer;
	SDL_Rect *_size;
	SDL_Event _event;
	
	TTF_Font *_font;
	
	int _width;
	int _height;
	
	list _sprites;
	
	int _fps;
	Uint32 _last_ticks;
	double _tdelta;
	
	// I use queues so they don't interfere when looping through the list
	queue _rem_queue;
	queue _add_queue;
	
	// This flag will be set to true if anything has been removed from the sprites list
	bool _is_dirty;
	
	Grid *_grid;
	Arrow *_arrow;
	Background *_background;
	Points *_points_sprite;
	Menu *_menu;
	
	bool _running;
	
	void clearBuffer();
	
	// Gameplay-related
	short _lives[3];
	long _points, _last_points;
	int _points_quantifier;
	
	bool _is_paused;
	
	int _volume;
public:
	Game();
	Game(SDL_Surface* screen);
	~Game();
	
	Game &operator=(const Game &);
	
	void start();
	void togglePause();
	void pause();
	bool isPaused() const { return _is_paused; };
	
	SDL_Surface *buffer() { return _buffer;	};
	SDL_Rect *size() { return _size; };
	double tdelta() { return _tdelta; };
	short lives() { return _lives[0]; };
	long points() const { return _points; };
	long lastPoints() const { return _last_points; };
	
	Grid *grid() const { return _grid; };
	Arrow *arrow() const { return _arrow; };
	Background *background() const { return _background; };
	
	void addSprite(Sprite*);
	void removeSprite(Sprite*);
	void removeSpriteImmediately(Sprite*);
	
	void cleanupList();
	void cap();
	
	void setWidth(int width) { _width = width; };
	void setHeight(int height) { _height = height; };
	
	void loop();
	void handleEvents();
	void draw();
	void tick();
	
	// Lives
	void checkRowCount();
	void decrementLives();
	void lost();
	void win();
	void showSubmit();
	void reset();
	
	// Points
	void startPointsAdding() { _points_quantifier = 0; };
	void addPointsNormal();
	void addPointsJumbo();
};

#endif
