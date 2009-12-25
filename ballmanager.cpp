/*
 *  ballmanager.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-19.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <cstdlib>

#include "SDL_image/SDL_image.h"

#include "ball.h"
#include "mysdl.h"

#include "ballmanager.h"

SDL_Surface *BallManager::_image = NULL;
SDL_Surface *BallManager::_balls[BALLMANAGER_COLORS] = {NULL, NULL, NULL, NULL, NULL, NULL};

SDL_Surface *BallManager::load(Ball::Colors color)
{
	// Load first image
	if ( ! _image )
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
	if ( ! _balls[index] )
	{
		// Make copy of the ball that we can enlarge
		SDL_PixelFormat *format = _image->format;
		SDL_Surface *ball = SDL_CreateRGBSurface(_image->flags,
												 BALL_WIDTH, BALL_HEIGHT, format->BitsPerPixel,
												 format->Rmask, format->Gmask, format->Bmask, format->Amask);
		
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
		}
		
		draw_transparent_surface_onto_empty_surface(rect, ball, _image);
		
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
