/*
 *  ball.h
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

#ifndef __BALL_H__
#define __BALL_H__

#include <iostream>

#include "sprite.h"
#include "vector.h"
#include "fx.h"

const int BALL_GRID_W = 17;
const int BALL_GRID_H = 15;

const int BALL_WIDTH = 23;
const int BALL_HEIGHT = 23;

class Ball: public Sprite
{
private:
	// _sprite is the original ball image, not changed by animations.
	SDL_Surface *_sprite;

	Vector _pos;

	int _grid_x, _grid_y;

	Uint8 _opacity;
	bool _was_dangly;

	void initFx();
public:
	enum BallState {Queued, Moving, Pinned};
	BallState _state;

	static Ball *create(Game *game);

	Ball(Game *game);
	~Ball();

	enum Colors {Random, Red, Green, Yellow, Blue, Teal, Purple};
	Colors _color;
	Colors color() { return _color; };

	static const char* getC(Colors c) {
		switch (c) {
			case Red: return "Red"; break;
			case Green: return "Green"; break;
			case Yellow: return "Yellow"; break;
			case Blue: return "Blue"; break;
			case Teal: return "Teal"; break;
			case Purple: return "Purple"; break;
			case Random: return "Random!"; break;
			default: return "wtf"; break;
		}
	}

	static void printC(Colors c) {
		std::cout << getC(c);
	};

	void setColor(Colors color);
	void setRemainingColor();
	void ensureColorExists();

	void setState(BallState state) { _state = state; };

	void gridX(int x) { _grid_x = x; gridToPos(); };
	void gridY(int y) { _grid_y = y; gridToPos(); };

	int gridX() { return _grid_x; };
	int gridY() { return _grid_y; };

	Vector &pos() { return _pos; };
	void xPos(double x) { _pos.x(x); _rect.x = x; };
	void yPos(double y) { _pos.y(y); _rect.y = y; };

	void wasDangly(bool was) { _was_dangly = was; };
	bool wasDangly() { return _was_dangly; };

	SDL_Rect *size() { return &_rect; };

	void tick();
	void draw();

	Vector calculateGrid();
	void satisfyGrid();
	void gridToPos();

	bool collidesWith(Ball &);

	void active();
	void bam();

	Vector _vel;
	Vector _acc;

	Fx _anim;
};

double active_transition(double x);
double bam_transition(double x);

#endif
