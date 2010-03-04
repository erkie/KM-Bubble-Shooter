/*
 *  grid.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-11.
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

typedef std::list<Ball*> ball_list;

class Grid: public Sprite
{
private:
	typedef std::list<GridPos*> grid_list;
	
	ball_list _balls;
	ball_list _remove_list;
	
	Ball *_remove_top;
	
public:
	Grid(Game *game);
	void tick();
	void draw();
	
	// Row handling
	void removeBall(Ball *ball);
	void addBall(Ball *ball);
	void removeBalls(ball_list &balls);
	void generateRow(int rows) { generateRow(rows, false); };
	void generateRow(int rows, bool is_startrow);
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
	void handleDanglies();
	bool doSearch(Ball &ball, ball_list &found, grid_list &searched, bool recursive, bool use_color);
	
	ball_list& balls() { return _balls; };
};

#endif
