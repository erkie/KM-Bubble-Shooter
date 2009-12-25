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

#include "ball.h"

const int BALLMANAGER_COLORS = 6;

class BallManager
{
	static SDL_Surface* _balls[BALLMANAGER_COLORS];
	static SDL_Surface* _image;
public:
	static SDL_Surface *load(Ball::Colors);
	static Ball::Colors randomColor();
};

#endif
