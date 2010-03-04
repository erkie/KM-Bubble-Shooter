/*
 *  ballmanager.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-19.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __BALLMANAGER_H__
#define __BALLMANAGER_H__

#include <vector>

#include "ball.h"
#include "grid.h"

const int BALLMANAGER_COLORS = 6;

class BallManager
{
private:
	static SDL_Surface* _image;
	static std::vector<Ball::Colors> _available;
	static SDL_Surface* _balls[BALLMANAGER_COLORS];
public:
	static SDL_Surface *load(Ball::Colors);
	static Ball::Colors randomColor();
	static void prepRemList(Grid *grid);
	static Ball::Colors randomRemainingColor(Grid *grid);
	static bool colorExists(Ball::Colors check);
};

#endif
