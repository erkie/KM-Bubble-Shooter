/*
 *  arrow.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-22.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>

#include "SDL_gfx/SDL_rotozoom.h"
#include "SDL_image/SDL_image.h"

#include "arrow.h"
#include "game.h"
#include "ball.h"
#include "vector.h"

Arrow::Arrow(Game *game): Drawable(game)
{
	_image = IMG_Load("arrow.png");
	if ( ! _image )
	{
		std::cerr << "Could not load arrow.png: " << IMG_GetError() << std::endl;
	}
	// Create copy of _rotated
	_rotated = SDL_DisplayFormatAlpha(_image);
	
	_pos = _image->clip_rect;
	
	_pos.x = _game->size()->w / 2 - _pos.w / 2;
	_pos.y = _game->size()->h - BALL_HEIGHT / 2;
	
	primeQueue();
}

void Arrow::tick()
{
	if ( _game->isPaused() )
		return;
	_current_ball->tick();
}

void Arrow::draw()
{
	// Rotatate arrow
	SDL_Rect pos = _pos; // I do know I'm making a copy here, right?
	
	// Adjust position to center
	pos.x -= _rotated->clip_rect.w / 2;
	pos.y -= _rotated->clip_rect.h / 2;
	
	// Draw arrow
	SDL_BlitSurface(_rotated, &_rotated->clip_rect, _game->buffer(), &pos);
	
	// Balls
	//
	Vector ballpos(0, 40);
	ballpos.angle(-(_angle + 90));
	
	_current_ball->xPos(_game->size()->w / 2 - BALL_WIDTH / 2 - _pos.w / 2 + ballpos.x());
	_current_ball->yPos(_game->size()->h - BALL_HEIGHT + ballpos.y());
	
	_current_ball->draw();
	
	// Draw queue
	int i = -1;
	for ( ball_queue::iterator iter = _queue.begin(); iter != _queue.end(); iter++ )
	{
		if ( ++i >= _game->lives() )
			continue;
		Ball *ball = (*iter);
		int w = ball->size()->w;
		ball->xPos((w * ARROW_QUEUE_SIZE + 10) - i * w);
		ball->yPos(_game->size()->h - w - 10);
		ball->draw();
	}
}

void Arrow::handleEvent(const SDL_Event &event)
{
	if ( _game->isPaused() )
		return;
	
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			release();
			break;
			
		case SDL_MOUSEMOTION:
			_mouse_pos.x(event.motion.x);
			_mouse_pos.y(event.motion.y);
			
			rotateToMouse();
			
			break;
	}
}

void Arrow::rotateToMouse()
{
	Vector v(_pos.x, _pos.y);
	
	// Add 90 to the angle so we are working in line with the bottom axis
	double ang = v.angleSeparating(_mouse_pos) + 90;
	
	// Ensure angle is not out of bounds. No max/min-function?
	ang = (ang < MIN_ANGLE) ? MIN_ANGLE : ((ang > MAX_ANGLE) ? MAX_ANGLE : ang);
	
	_current_ball->_vel.angle(-ang);
	
	// Remove the 90 again to rotate correctly
	_angle = ang - 90;
	
	SDL_FreeSurface(_rotated);
	_rotated = rotozoomSurface(_image, _angle, 1, 1);
}

void Arrow::primeQueue()
{
	// Queue balls
	// Create one more than specified, for the current ball
	for ( int i = 0; i <= ARROW_QUEUE_SIZE; i++ )
	{
		Ball* ball = new Ball(_game);
		ball->setOpacity(ARROW_BALL_OPACITY);
		_queue.push_back(ball);
	}
	
	setCurrent();
}

void Arrow::setCurrent()
{
	_current_ball = _queue.front();
	_current_ball->is_pinned = true;
	_current_ball->_vel.angle(-1 * (_angle + 90));
	_current_ball->setOpacity(0xFF);
	_current_ball->active();
	_queue.remove(_current_ball);
	
	// Add to end
	Ball* b = new Ball(_game);
	b->setOpacity(ARROW_BALL_OPACITY);
	_queue.push_back(b);
}

void Arrow::release()
{
	if ( ! isReady() )
		return;
	
	_current_ball->is_pinned = false;
	_game->addDrawable(_current_ball);
	setReady(false);
	
	setCurrent();
}

Arrow::~Arrow() {}
