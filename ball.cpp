/*
 *  ball.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-07.
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
#include <cstdlib>

#include "SDL.h"
#include "SDL_gfx/SDL_rotozoom.h"

#include "mysdl.h"
#include "ballmanager.h"
#include "sound.h"

#include "game.h"
#include "background.h"
#include "grid.h"
#include "fx.h"
#include "arrow.h"

#include "ball.h"

Ball* Ball::create(Game *game)
{
	Ball *b = new Ball(game);
	game->addSprite(b);
	return b;
}

Ball::Ball(Game *game): Sprite(game), _was_dangly(false), _state(Queued)
{
	setColor(Random);
	
	_rect = _image->clip_rect;
	
	_vel.x(0);
	_vel.y(_game->size()->h * 2);
	
	_grid_x = _grid_y = -1;
	
	_anim = Fx();
	_anim.mode(Fx::Single);
}

Ball::~Ball()
{
	// The ball can be destructed whilst animating,
	// that is why we have to free the surface
	// created by rotozoomSurface here.
	if ( _image != _sprite )
	{
		SDL_FreeSurface(_image);
	}
}

void Ball::setColor(Colors color)
{
	color = (color == Random) ? BallManager::randomColor() : color;
	_image = _sprite = BallManager::load(color);
	_color = color;
}

void Ball::setRemainingColor()
{
	setColor(BallManager::randomRemainingColor(_game->grid()));
}

void Ball::ensureColorExists()
{
	if ( ! BallManager::colorExists(_color) )
	{
		setRemainingColor();
		active();
	}
}

void Ball::draw()
{
	if ( _game->isPaused() || ! visible() )
		return;
	
	_rect.x = _pos.x();
	_rect.y = _pos.y();
	
	// Make copy because SDL clips the passed rect (or so I think)
	SDL_Rect cp_rect = _rect;
	
	// Center it to its position
	int half = BALL_WIDTH / 2 - _image->clip_rect.w / 2;	
	cp_rect.x += half;
	cp_rect.y += half;
	
	SDL_BlitSurface(_image, NULL, _game->buffer(), &cp_rect);
}

void Ball::tick()
{	
	if ( _game->isPaused() )
		return;
	
	if ( _state == Moving )
	{
		Vector orig_pos(_pos);
		
		Ball *hit;
		// Break movement into smaller pieces and analyze them
		int pieces = 5, i;
		for ( i = 1; i <= pieces; i++ )
		{
			_pos = orig_pos + _vel * (_game->tdelta() / pieces * i);
			hit = _game->grid()->inCollision(*this);
			if ( hit ) break;
		}
		
		xPos(_pos.x());
		yPos(_pos.y());
		
		if ( _pos.y() < 0 || (hit = _game->grid()->inCollision(*this)) )
		{
			_pos = orig_pos + _vel * (_game->tdelta() / pieces * (i - 1));
			
			// Okey, so I've hit something.
			// What do I do next?
			// 1. pin myself. (check)
			// 2. settle on a grid position with my homies
			// 3. add myself to Grid (check)
			
			setState(Pinned);
			
			// Remove myself from the empty movement void
			_game->arrow()->setReady(true);
			_game->removeSprite(this);
			
			// Animate bouncy bounce
			active();
			satisfyGrid();
			
			// Add myself to the warm land of Grid
			_game->grid()->addBall(this);
			
			// I've hit a wall
			if ( ! hit ) 
				_game->decrementLives();
			
			play_ball_thud();
			
			return;
		}
		
		const SDL_Rect *size = _game->size();

		// Collision detection, wee!
		if ( _pos.x() < 0 )
		{
			_vel._x *= -1;
			xPos(0);
			
			play_ball_bounce();
		}
		else if ( _pos.x() + _rect.w > size->w )
		{
			_vel._x *= -1;
			xPos(size->w - _rect.w);
			
			play_ball_bounce();
		}

		if ( _pos.y() + _rect.h > size->h )
		{
			_vel._y *= -1;
			yPos(size->h - _rect.h);

			play_ball_bounce();
		}
		// The end!
	}
	
	if ( _anim.isRunning() )
	{
		SDL_FreeSurface(_image);
		setImage(rotozoomSurface(_sprite, 1, _anim.step(), 1));
		
		// Has the motion stopped
		if ( ! _anim.isRunning() )
		{
			SDL_FreeSurface(_image);
			_image = _sprite;
		}
	}
}

Vector Ball::calculateGrid()
{
	int grid_size = _game->size()->w / BALL_GRID_W;
	
	int center_x = _pos.y() + _rect.h / 2;
	int center_y = _pos.x() + _rect.w / 2;
	
	// These calculated are the idealised (where I really am) x/y-grid positions
	int y = center_x / grid_size;
	int x = (center_y - (y % 2 ? 12 : 0)) / grid_size;
	
	return Vector(x, y);
}

void Ball::satisfyGrid()
{
	Vector grid = calculateGrid();
	int x = grid.x(), y = grid.y();
	
	x = (x >= BALL_GRID_W) ? BALL_GRID_W - 1 : x;
	
	if ( _game->grid()->hasBallOn(x, y) )
	{
		y++;
	}
	
	_grid_x = x;
	_grid_y = y;
	
	gridToPos();
}

void Ball::gridToPos()
{
	int dd = _game->size()->w / BALL_GRID_W;
	
	int pos_x = dd * _grid_x + (_grid_y % 2 ? 12 : 0);
	int pos_y = dd * _grid_y;
	
	xPos(pos_x);
	yPos(pos_y);
}

bool Ball::collidesWith(Ball &ball)
{
	return _pos.distanceBetween(ball.pos()) < BALL_WIDTH - 6;
}

void Ball::initFx()
{
	if ( _anim.isRunning() )
		return;
	
	// Make copy of the ball that we can enlarge
	_image = SDL_DisplayFormatAlpha(_sprite);
}

void Ball::active()
{
	if ( _anim.isRunning() )
		return;
	
	initFx();
	
	// Prepare animation
	_anim.value(1);
	_anim.duration(250);
	_anim.transition(active_transition);
	
	// Active animation
	_anim.start();
}

void Ball::bam()
{
	initFx();
	
	_anim.stop();
	
	_anim.transition(bam_transition);
	_anim.value(1);
	_anim.duration(40);
	_anim.start();
	
	play_ball_die();
}

double active_transition(double x)
{
	return 2 * (x - 0) * (x - 1) + 1;
};

double bam_transition(double x)
{
	return 1 + x;
};
