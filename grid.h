/*
 *  grid.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-11.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __GRID_H__
#define __GRID_H__

#include <list>

#include "ball.h"
#include "sprite.h"

// This class will be used by the search-part of Grid
class GridPos
{
public:
	GridPos(int gx, int gy): x(gx), y(gy) {}; 
	int x, y;
};

class Grid: public Sprite
{
private:
	typedef std::list<Ball*> ball_list;
	typedef std::list<GridPos*> grid_list;
	
	ball_list _balls;
	ball_list _remove_list;
	
	Ball *_remove_top;
	
public:
	Grid(Game *game);
	void tick() {};
	void draw();
	
	// Row handling
	void removeBall(Ball *ball);
	void addBall(Ball *ball);
	void removeBalls(ball_list &balls);
	void generateRow(int rows);
	void generateStartRows();
	int countRows();
	void emptyRows();
	
	// Ball detection
	Ball *inCollision(Ball &);
	bool hasBallOn(int x, int y);
	Ball *getBallOn(int x, int y);
	Ball *getBallWithColor(int x, int y, Ball::Colors color);
	
	// Group handling
	void locateGroups(Ball &relativeTo);
	bool gridListHas(grid_list &, int, int);
	void search(Ball &ball, ball_list &found);
	void searchNear(Ball &ball, ball_list &found);
	void handleDanglies();
	bool doSearch(Ball &ball, ball_list &found, grid_list &searched, bool recursive, bool use_color);
};

#endif
