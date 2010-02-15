/*
 *  ballmanager.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-19.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <cstdlib>
#include <iostream>
#include <algorithm>

#include "SDL_image/SDL_image.h"

#include "ball.h"
#include "mysdl.h"

#include "ballmanager.h"

SDL_Surface *BallManager::_image = NULL;
SDL_Surface *BallManager::_balls[BALLMANAGER_COLORS] = {NULL, NULL, NULL, NULL, NULL, NULL};
std::vector<Ball::Colors> BallManager::_available = std::vector<Ball::Colors>();

SDL_Surface *BallManager::load(Ball::Colors color)
{
	// Load first image
	if ( _image == NULL )
	{
		SDL_Surface * image = IMG_Load("ball.png");
		if ( ! image )
		{
			std::cerr << "Could not load image: " << IMG_GetError() << std::endl;
			return NULL;
		}
		
		SDL_Surface *optimized = SDL_DisplayFormatAlpha(image);
		
		if ( optimized != NULL )
		{
			SDL_FreeSurface(image);
			SDL_SetColorKey(optimized, SDL_SRCCOLORKEY, SDL_MapRGB(optimized->format, 0, 0xFF, 0xFF));
			image = optimized;
		}
		_image = image;
	}
	
	// Create single image (if needed)
	int index = color - 1;
	if ( _balls[index] == NULL )
	{
		// Make copy of the ball that we can enlarge
		SDL_PixelFormat *format = _image->format;
		SDL_Surface *ball = SDL_CreateRGBSurface(_image->flags,
												 BALL_WIDTH, BALL_HEIGHT, format->BitsPerPixel,
												 format->Rmask, format->Bmask, format->Gmask, format->Amask);
		//										 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
		//SDL_FillRect(ball, NULL, SDL_MapRGBA(format, 0xFF, 0xFF, 0xFF, 0x00));
		
		SDL_Rect rect;
		rect.y = 0;
		switch ( color )
		{
			case Ball::Red:    rect.x = 0; break;
			case Ball::Green:  rect.x = 23; break;
			case Ball::Yellow: rect.x = 46; break;
			case Ball::Blue:   rect.x = 69; break;
			case Ball::Teal:   rect.x = 92; break;
			case Ball::Purple: rect.x = 115; break;
			default: std::cerr << "Sanity check failed" << std::endl;
		}
		
		draw_transparent_surface_onto_empty_surface(rect, ball, _image);
		
		std::cout << Ball::getC(color) << " " << ball << std::endl;
		
		_balls[index] = ball;
	}
	
	return _balls[index];
}

Ball::Colors BallManager::randomColor()
{
	Ball::Colors color;
	int random = rand() % 6 + 1;
	color = (Ball::Colors)random;
	return color;
}

void BallManager::prepRemList(Grid *grid)
{
	// Clear old availables list
	_available.erase(_available.begin(), _available.end());
	
	ball_list balls = grid->balls();
	for ( ball_list::iterator iter = balls.begin(); iter != balls.end(); iter++ )
		if ( count(_available.begin(), _available.end(), (*iter)->color()) == 0 )
			_available.push_back((*iter)->color());
}

Ball::Colors BallManager::randomRemainingColor(Grid *grid)
{
	prepRemList(grid);
	
	std::random_shuffle(_available.begin(), _available.end());
	return _available.front();
}

bool BallManager::colorExists(Ball::Colors check)
{
	return count(_available.begin(), _available.end(), check);
}
