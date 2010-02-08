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

Arrow::Arrow(Game *game): Sprite(game)
{
	_origin = IMG_Load("arrow.png");
	if ( ! _origin )
	{
		std::cerr << "Could not load arrow.png: " << IMG_GetError() << std::endl;
	}
	// Create copy of _origin
	_image = SDL_DisplayFormatAlpha(_origin);
	
	_pos = _origin->clip_rect;
	_pos.x = _game->size()->w / 2 - _pos.w / 2;
	_pos.y = _game->size()->h - BALL_HEIGHT / 2;
	
	// Queue balls
	// Create one more than specified, for the current ball
	for ( int i = 0; i <= ARROW_QUEUE_SIZE; i++ )
		_queue.push_back(Ball::create(_game));
	
	setCurrent();
}

Arrow::~Arrow()
{
	SDL_FreeSurface(_origin);
	SDL_FreeSurface(_image);
}

void Arrow::tick()
{
	if ( _game->isPaused() )
		return;
	
	int i = 0;
	for ( ball_queue::iterator iter = _queue.begin(); iter != _queue.end(); iter++, i++ )
	{
		if ( i >= _game->lives() )
			(*iter)->visible(false);
		else
			(*iter)->visible(true);
	}
}

void Arrow::draw()
{
	if ( _game->isPaused() )
		return;
	
	SDL_Rect pos = _rect; // Make copy for SDL clipping goodness
	SDL_BlitSurface(_image, NULL, _game->buffer(), &pos);
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
	////
	// Position and rotate arrow
	Vector v(_pos.x, _pos.y);
	
	// Add 90 to the angle so we are working in line with the bottom axis
	double ang = v.angleSeparating(_mouse_pos) + 90;
	
	// Ensure angle is not out of bounds. No max/min-function?
	ang = (ang < MIN_ANGLE) ? MIN_ANGLE : ((ang > MAX_ANGLE) ? MAX_ANGLE : ang);
	
	_current_ball->_vel.angle(-ang);
	
	// Remove the 90 again to rotate correctly
	_angle = ang - 90;
	
	SDL_FreeSurface(_image);
	_image = rotozoomSurface(_origin, _angle, 1, 1);
	
	// Adjust position to center
	_rect = _image->clip_rect;
	_rect.x = _pos.x - _image->clip_rect.w / 2;
	_rect.y = _pos.y - _image->clip_rect.h / 2;
	
	////
	// Position balls
	Vector ballpos(0, 40);
	ballpos.angle(-(_angle + 90));
	
	_current_ball->xPos(_game->size()->w / 2 - BALL_WIDTH / 2 - _pos.w / 2 + ballpos.x());
	_current_ball->yPos(_game->size()->h - BALL_HEIGHT + ballpos.y());
	
	// Queue balls
	int i = 0;
	for ( ball_queue::iterator iter = _queue.begin(); iter != _queue.end(); iter++, i++ )
	{
		Ball *ball = (*iter);
		int w = ball->size()->w;
		ball->xPos((w * ARROW_QUEUE_SIZE + 10) - i * w);
		ball->yPos(_game->size()->h - w - 10);
	}
}

void Arrow::setCurrent()
{
	// Create new ball
	_current_ball = _queue.front();
	_current_ball->setState(Ball::Queued);
	_current_ball->_vel.angle(-1 * (_angle + 90));
	_current_ball->active();
	
	_queue.remove(_current_ball);
	
	// Add to end
	Ball* b = Ball::create(_game);
	_queue.push_back(b);
	
	// Rotate current ball to mouse position angle
	rotateToMouse();
}

void Arrow::release()
{
	if ( ! isReady() )
		return;
	
	_current_ball->setState(Ball::Moving);
	setReady(false);
	
	setCurrent();
}
