/*
 *  arrow.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-22.
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
	Ball* current() { return _current_ball; };
	
	bool isReady() const { return _is_ready; };
	void setReady(bool ready) { _is_ready = ready; };
};

#endif
