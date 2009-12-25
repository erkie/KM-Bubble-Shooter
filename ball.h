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

#include "drawable.h"
#include "vector.h"
#include "fx.h"

const int BALL_GRID_W = 17;
const int BALL_GRID_H = 15;

const int BALL_WIDTH = 23;
const int BALL_HEIGHT = 23;

class Ball: public Drawable
{
private:
	SDL_Rect _temp_rect;
	
	// _image is the image loaded with all the balls
	SDL_Surface *_image;
	
	// _sprite is the image to draw onto the screen
	SDL_Surface *_sprite;
	
	// _rect is the (dst_rect) rect containing the position of the object
	SDL_Rect _rect;
	
	// _sprite_rect is the (src_rect) rect conting the position on the _image
	SDL_Rect _sprite_rect;
	
	Vector _pos;
	
	int _grid_x, _grid_y;
	
	Uint8 _opacity;
	bool _was_dangly;
public:
	Ball();
	Ball(Game *game);
	
	enum Colors {Random, Red, Green, Yellow, Blue, Teal, Purple};
	Colors _color;
	
	void setColor(Colors color);
	
	void gridX(int x) { _grid_x = x; };
	void gridY(int y) { _grid_y = y; };
	
	int gridX() const { return _grid_x; };
	int gridY() const { return _grid_y; };
	
	void setOpacity(Uint8 opacity);
	
	Vector &pos() { return _pos; };
	void xPos(double x) { _pos.x(x); };
	void yPos(double y) { _pos.y(y); };
	
	void wasDangly(bool was) { _was_dangly = was; };
	bool wasDangly() { return _was_dangly; };
	
	SDL_Rect *size() { return &_sprite_rect; };
	
	void tick();
	void draw();
	
	Vector calculateGrid();
	void satisfyGrid();
	void gridToPos(int x, int y);
	
	bool isInGrid() { return _grid_x >= 0 && _grid_y >= 0; };
	bool is_pinned;
	bool collidesWith(Ball &);
	
	void active();
	void bam();
	void initFx();
	
	Vector _vel;
	Vector _acc;
	
	Fx _anim;
};

double active_transition(double x);
double bam_transition(double x);

#endif
