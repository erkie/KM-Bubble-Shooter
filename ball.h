/*
 *  ball.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-07.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __BALL_H__
#define __BALL_H__

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
	
	void setColor(Colors color);
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
