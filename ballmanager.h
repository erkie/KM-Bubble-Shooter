/*
 *  ballmanager.h
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
 *  THE SOFTWARE. *
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
