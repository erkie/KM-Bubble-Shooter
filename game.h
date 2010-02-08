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
const int PAUSE_FPS = 50;
const int ADJACENT_BALLS = 3;
const int GAME_LIVES = 6;

class Grid;
class Arrow;
class Sprite;
class Background;
class Points;
class Menu;

typedef std::list<SDL_Rect> rect_list;

class Game
{
private:
	typedef std::list<Sprite*> list;
	typedef list queue;
	
	SDL_Surface *_screen;
	SDL_Surface *_buffer;
	SDL_Rect *_size;
	SDL_Event _event;
	
	TTF_Font *_font;
	
	int _width;
	int _height;
	
	list _sprites;
	rect_list _dirty_rects;
	
	int _fps;
	Uint32 _last_ticks;
	double _tdelta;
	
	// Queues are used so they don't interfere when looping through the sprite_list
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
		
	// Play-related
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
	
	// Common sprites
	Grid *grid() const { return _grid; };
	Arrow *arrow() const { return _arrow; };
	Background *background() const { return _background; };
	
	// Sprites
	void addSprite(Sprite*);
	void removeSprite(Sprite*);
	void removeSpriteImmediately(Sprite*);
	void cleanupList();
	
	// Dirty rect animation
	void addDirtyRect(SDL_Rect r) { _dirty_rects.push_back(r); };
	rect_list & getDirtyRects() { return _dirty_rects; };
	
	void cap();
	
	// Screen
	void setWidth(int width) { _width = width; };
	void setHeight(int height) { _height = height; };
	
	// Game
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
	
	// DEBUGGING
	void printSelf()
	{
		std::cout << "\n=== Current state of affairs: ===\n";
		std::cout << "Screen size: " << _width << "x" << _height << '\n';
		std::cout << "Fps is: " << _fps << '\n';
		std::cout << "sprite_list size is at: " << _sprites.size() << '\n';
		std::cout << "Dirty rects is at: " << _dirty_rects.size() << '\n';
		std::cout << "rem_queue is size is " << _rem_queue.size() << " and add_queue is " << _add_queue.size() << '\n';
		std::cout << "lives is " << _lives[0] << " " << _lives[1] << " " << _lives[2] << '\n';
		std::cout << "You have " << _points << " and last_points is " << _last_points << '\n';
		std::cout << "points quantifier is " << _points_quantifier << '\n';
		std::cout << "... and is_paused is " << _is_paused << " and the game volum is " << _volume << std::endl;
	}
};

#endif
