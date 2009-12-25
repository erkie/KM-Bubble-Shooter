/*
 *  arrow.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-22.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __ARROW_H__
#define __ARROW_H__

#include <list>

#include "SDL.h"

#include "drawable.h"
#include "vector.h"
#include "ball.h"

const int ARROW_QUEUE_SIZE = 5;
const Uint8 ARROW_BALL_OPACITY = 0x99;

class Arrow: public Drawable
{
	static const double MAX_ANGLE = 170;
	static const double MIN_ANGLE = 10;
	
	typedef std::list<Ball*> ball_queue;
	ball_queue _queue;
	
	Ball *_current_ball;
	
	SDL_Surface *_image;
	SDL_Surface *_rotated;
	SDL_Rect _pos;
	Vector _mouse_pos;
	double _angle;
	
	bool _is_ready;
public:
	Arrow(Game *game);
	~Arrow();
	
	void tick();
	void draw();
	void handleEvent(const SDL_Event &event);
	
	void rotateToMouse();
	
	void primeQueue();
	void setCurrent();
	void release();
	
	bool isReady() const { return _is_ready; };
	void setReady(bool ready) { _is_ready = ready; };
};

#endif
