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

#include "sprite.h"
#include "vector.h"
#include "ball.h"

const int ARROW_QUEUE_SIZE = 5;
const Uint8 ARROW_BALL_OPACITY = 0x99;

class Arrow: public Sprite
{
	static const double MAX_ANGLE = 170;
	static const double MIN_ANGLE = 10;
	
	typedef std::list<Ball*> ball_queue;
	ball_queue _queue;
	
	Ball *_current_ball;
	
	SDL_Surface *_origin;
	SDL_Rect _pos;
	Vector _mouse_pos;
	double _angle;
	
	bool _is_ready;
public:
	Arrow(Game *game);
	~Arrow();
	
	void prepareQueue();
	
	void tick();
	void draw();
	void handleEvent(const SDL_Event &event);
	
	void rotateToMouse();
	
	void checkQueueColors();
	void setCurrent(bool is_in_game = false);
	void release();
	
	Ball* createBall();
	
	bool isReady() const { return _is_ready; };
	void setReady(bool ready) { _is_ready = ready; };
};

#endif
