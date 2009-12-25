/*
 *  ball.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-07.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
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

Ball::Ball(Game *game): Drawable(game), is_pinned(false), _was_dangly(false)
{
	setColor(Random);
	_sprite = _image;
	
	_rect = _image->clip_rect;
	_sprite_rect.w = BALL_WIDTH;
	_sprite_rect.h = BALL_HEIGHT;
	
	_vel.x(0);
	_vel.y(-1 * -1 * (_game->size()->h * 2));
	
	_grid_x = _grid_y = -1;
	
	_anim = Fx();
	_anim.mode(Fx::Single);
}

Ball::Ball() {}

void Ball::setColor(Colors color)
{
	if ( color == Random )
		color = BallManager::randomColor();
	_image = BallManager::load(color);
	_color = color;
}

void Ball::setOpacity(Uint8 opacity)
{
	if ( true || opacity == 0xFF )
	{
		if ( _image != _sprite )
			SDL_FreeSurface(_image);
		_image = _sprite;
	}
	else
	{
		_image = change_opacity_of_surface(_sprite, opacity);
		_opacity = opacity;
	}
}

void Ball::draw()
{
	if ( isInGrid() )
	{
		gridToPos(_grid_x, _grid_y);
	}
	else if ( ! isInGrid() && _game->isPaused() )
		return;
	
	_rect.x = _pos.x();
	_rect.y = _pos.y();
		
	// Make copy because SDL clips the passed rect (or so I think)
	SDL_Rect cp_rect = _rect;
	
	if ( _anim.isRunning())
	{
		// Center it to its position
		int half = BALL_WIDTH / 2 - _image->clip_rect.w / 2;
		
		cp_rect.x += half;
		cp_rect.y += half;
	}
	
	SDL_BlitSurface(_image, NULL, _game->buffer(), &cp_rect);
}

void Ball::tick()
{	
	if ( _game->isPaused() )
		return;
	
	if ( ! is_pinned && ! isInGrid() )
	{
		Vector orig_pos(_pos.x(), _pos.y());
		
		Ball *hit;
		// Break movement into smaller pieces and analyze them
		int pieces = 5, i;
		for ( i = 1; i <= pieces; i++ )
		{
			_pos = orig_pos + _vel * (_game->tdelta() / pieces * i);
			hit = _game->grid()->inCollision(*this);
			if ( hit ) break;
		}
				
		if ( _pos.y() < 0 || (hit = _game->grid()->inCollision(*this)) )
		{
			_pos = orig_pos + _vel * (_game->tdelta() / pieces * (i - 1));
			
			// Okey, so I've hit something.
			// What do I do next?
			// 1. pin myself. (check)
			// 2. settle on a grid position with my homies
			// 3. add myself to Grid (check)
			
			is_pinned = true;
			
			// Remove myself from the void
			_game->arrow()->setReady(true);
			
			_game->removeDrawable(this);
			
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
			_pos.x(0);
			
			play_ball_bounce();
		}
		else if ( _pos.x() + _sprite_rect.w > size->w )
		{
			_vel._x *= -1;
			_pos.x(size->w - _sprite_rect.w);
			
			play_ball_bounce();
		}

		if ( _pos.y() + _sprite_rect.h > size->h )
		{
			_vel._y *= -1;
			_pos.y(size->h - _sprite_rect.h);

			play_ball_bounce();
		}
		// The end!
	}
	
	if ( _anim.isRunning() )
	{
		SDL_FreeSurface(_image);
		_image = rotozoomSurface(_sprite, 1, _anim.step(), 1);
		
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
	
	int center_x = _pos.y() + _sprite_rect.h / 2;
	int center_y = _pos.x() + _sprite_rect.w / 2;
	
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
	
	_grid_x = x;
	_grid_y = y;
	
	if ( _game->grid()->hasBallOn(x, y) )
	{
		y++;
	}
	
	gridToPos(x, y);
}

void Ball::gridToPos(int x, int y)
{	
	int dd = _game->size()->w / BALL_GRID_W;
	
	int pos_x = dd * x + (y % 2 ? 12 : 0);
	int pos_y = dd * y;
	
	_pos.x(pos_x);
	_pos.y(pos_y);	
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
	SDL_Surface *copy = SDL_DisplayFormatAlpha(_sprite);
	_image = copy;
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
	return 1 + x * 0.5;
};
