/*
 *  ballmanager.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-19.
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
		SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 0xFF, 0xFF, 0xFF));
		
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
												 format->Rmask, format->Bmask, format->Gmask, format->Amask);
		//										 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
		//SDL_FillRect(ball, NULL, SDL_MapRGBA(format, 0x00, 0x00, 0x00, 0x00));
		
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
